// Building the CSR graph: from_edges() for tests, load() for SNAP files.
// load() only parses and relabels; all cleaning (symmetrise, drop
// self-loops, drop duplicates) happens in from_edges(), so both entry
// points produce graphs with exactly the same guarantees.

#include "graph.h"

#include <algorithm>
#include <climits>
#include <cstdlib>
#include <fstream>
#include <stdexcept>

// Builds CSR in three passes, without ever storing a list of edge pairs
// twice (this matters for the big SNAP graphs):
//   1. count how many entries each vertex gets (both directions),
//   2. prefix-sum the counts into start offsets and scatter the entries,
//   3. sort each vertex's list, drop duplicates and compact in place.
// Every kept input edge inserts u->v and v->u together, and deduplication
// works per list, so the result is always symmetric: v is in u's list
// exactly when u is in v's.
G from_edges(int n, const std::vector<std::pair<int,int>>& e) {
    if (n < 0) throw std::invalid_argument("from_edges: negative n");

    // Pass 1: cnt[v+1] = number of entries v will receive.
    std::vector<long long> cnt(n + 1, 0);
    for (auto [u, v] : e) {
        if (u < 0 || u >= n || v < 0 || v >= n)
            throw std::invalid_argument("from_edges: vertex id out of range");
        if (u == v) continue;                    // self-loops never count towards a core
        cnt[u + 1]++;
        cnt[v + 1]++;
    }

    // Pass 2: after this prefix sum, v's entries go in raw[cnt[v] .. cnt[v+1]).
    for (int v = 0; v < n; v++) cnt[v + 1] += cnt[v];
    std::vector<int> raw(cnt[n]);
    std::vector<long long> next(cnt.begin(), cnt.end() - 1);   // next free slot of each vertex
    for (auto [u, v] : e) {
        if (u == v) continue;
        raw[next[u]++] = v;
        raw[next[v]++] = u;
    }

    // Pass 3: sort and dedupe each list, then slide it left to close the gap
    // the removed duplicates left behind. The write position w never passes
    // the read position cnt[v], so compacting in place is safe.
    G g;
    g.n = n;
    g.off.assign(n + 1, 0);
    long long w = 0;
    for (int v = 0; v < n; v++) {
        auto first = raw.begin() + cnt[v];
        auto last = raw.begin() + cnt[v + 1];
        std::sort(first, last);
        last = std::unique(first, last);         // duplicates are now adjacent; keep one of each
        w = std::copy(first, last, raw.begin() + w) - raw.begin();
        g.off[v + 1] = w;
    }
    raw.resize(w);
    raw.shrink_to_fit();
    g.adj = std::move(raw);
    g.m = w / 2;                                 // each undirected edge is stored twice
    return g;
}

// Reads a SNAP edge list: lines starting with '#' are comments, every other
// non-blank line is "u v" (any whitespace between them). SNAP ids can be
// large and have gaps (web-Google goes up to ~916k), so ids are relabelled
// to 0..n-1, keeping their original order: the smallest id becomes 0.
// A vertex that only appears in a self-loop is kept, as an isolated vertex
// with core 0. Directed files are fine: from_edges() symmetrises them.
G load(const std::string& path) {
    std::ifstream in(path);
    if (!in) throw std::runtime_error("load: cannot open " + path);

    std::vector<std::pair<long long, long long>> raw;
    std::string line;
    long long lineno = 0;
    while (std::getline(in, line)) {
        lineno++;
        size_t start = line.find_first_not_of(" \t\r");
        if (start == std::string::npos || line[start] == '#') continue;

        // strtoll skips leading whitespace and reports where it stopped,
        // so `end == s` means no number was found.
        const char* s = line.c_str() + start;
        char* end;
        long long u = std::strtoll(s, &end, 10);
        bool ok = end != s;
        s = end;
        long long v = std::strtoll(s, &end, 10);
        ok = ok && end != s && u >= 0 && v >= 0;
        if (!ok)
            throw std::runtime_error("load: " + path + " line " + std::to_string(lineno) +
                                     " is not \"u v\" with non-negative ids");
        raw.push_back({u, v});
    }

    // Relabel: sorted distinct ids, and each id's new label is its index.
    std::vector<long long> ids;
    ids.reserve(2 * raw.size());
    for (auto [u, v] : raw) {
        ids.push_back(u);
        ids.push_back(v);
    }
    std::sort(ids.begin(), ids.end());
    ids.erase(std::unique(ids.begin(), ids.end()), ids.end());
    if (ids.size() > (size_t)INT_MAX) throw std::runtime_error("load: too many vertices for int ids");

    auto label = [&](long long x) {
        return (int)(std::lower_bound(ids.begin(), ids.end(), x) - ids.begin());
    };
    std::vector<std::pair<int,int>> e;
    e.reserve(raw.size());
    for (auto [u, v] : raw) e.push_back({label(u), label(v)});

    int n = (int)ids.size();
    raw = {};                                    // free the parsing buffers before CSR is built
    ids = {};
    return from_edges(n, e);
}
