// Correctness checks (vault/03 Design/Correctness.md).
//   same()    : exact vertex-by-vertex comparison with B0's answer.
//   is_core() : checks an answer from the definition alone, without B0,
//               so a bug in B0 itself would also be caught.
// Both print the reason for a failure to stderr, so the driver's CSV
// output on stdout stays clean.

#include "graph.h"

#include <algorithm>
#include <cstdio>

bool same(const std::vector<int>& a, const std::vector<int>& b) {
    if (a.size() != b.size()) {
        std::fprintf(stderr, "same: sizes differ (%zu vs %zu)\n", a.size(), b.size());
        return false;
    }
    for (size_t v = 0; v < a.size(); v++) {
        if (a[v] != b[v]) {
            std::fprintf(stderr, "same: first mismatch at vertex %zu: %d vs %d\n", v, a[v], b[v]);
            return false;
        }
    }
    return true;
}

// c is the core decomposition of g exactly when both halves hold:
//
// Half 1, "c is never too high": every v has at least c[v] neighbours u
//   with c[u] >= c[v]. Then for any k, the set S_k = {v : c[v] >= k} gives
//   every member at least k neighbours inside S_k, so S_k lies inside the
//   real k-core and the real core of v is at least c[v].
//   An all-zeros answer passes this half, which is why half 2 exists.
//
// Half 2, "c is never too low": peel the graph using c as the plan. For
//   k = 0, 1, 2, ... remove the vertices with c[v] == k whose remaining
//   degree is <= k, repeatedly, since each removal lowers its neighbours'
//   degrees. If some vertex with c[v] == k is still there afterwards, it
//   has more than k neighbours that outlast level k, so its real core is
//   above k. If all of them go, every vertex was removed with at most
//   c[v] neighbours left, and no vertex can then have a real core above
//   c[v]. (If the real core of v were higher, v's neighbours in that core
//   would all be removed after v, giving v more than c[v] at removal.)
//
// Both halves are O(n + m).
bool is_core(const G& g, const std::vector<int>& c) {
    if ((int)c.size() != g.n) {
        std::fprintf(stderr, "is_core: answer has %zu entries for %d vertices\n", c.size(), g.n);
        return false;
    }
    int kmax = 0;
    for (int v = 0; v < g.n; v++) {
        if (c[v] < 0 || c[v] > g.deg(v)) {
            std::fprintf(stderr, "is_core: vertex %d has core %d but degree %d\n", v, c[v], g.deg(v));
            return false;
        }
        kmax = std::max(kmax, c[v]);
    }

    // Half 1.
    for (int v = 0; v < g.n; v++) {
        int at_least = 0;
        for (long long i = g.off[v]; i < g.off[v + 1]; i++) at_least += c[g.adj[i]] >= c[v];
        if (at_least < c[v]) {
            std::fprintf(stderr, "is_core: vertex %d has core %d but only %d neighbours with core >= %d (too high)\n",
                         v, c[v], at_least, c[v]);
            return false;
        }
    }

    // Half 2. level[k] lists the vertices with c == k (a counting sort).
    std::vector<std::vector<int>> level(kmax + 1);
    for (int v = 0; v < g.n; v++) level[c[v]].push_back(v);

    std::vector<int> d(g.n);                     // degree in what is left of the graph
    for (int v = 0; v < g.n; v++) d[v] = g.deg(v);
    std::vector<char> queued(g.n, 0), removed(g.n, 0);
    std::vector<int> todo;

    for (int k = 0; k <= kmax; k++) {
        for (int v : level[k])
            if (d[v] <= k) { queued[v] = 1; todo.push_back(v); }
        while (!todo.empty()) {
            int v = todo.back();
            todo.pop_back();
            removed[v] = 1;
            for (long long i = g.off[v]; i < g.off[v + 1]; i++) {
                int u = g.adj[i];
                if (removed[u]) continue;
                d[u]--;
                if (c[u] == k && d[u] <= k && !queued[u]) { queued[u] = 1; todo.push_back(u); }
            }
        }
        for (int v : level[k]) {
            if (!removed[v]) {
                std::fprintf(stderr, "is_core: vertex %d has core %d but still has %d neighbours "
                                     "after level %d is peeled (too low)\n", v, k, d[v], k);
                return false;
            }
        }
    }
    return true;
}
