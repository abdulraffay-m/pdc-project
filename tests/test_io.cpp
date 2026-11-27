// Tests for io.cpp: the CSR guarantees every variant relies on
// (symmetric, sorted, no self-loops, no duplicates) and the SNAP parsing.

#include "tests.h"

#include <fstream>
#include <stdexcept>

// Every neighbour list strictly ascending (so no duplicates), no self-loops,
// and v in adj(u) exactly when u in adj(v).
static bool well_formed(const G& g) {
    if ((int)g.off.size() != g.n + 1 || g.off[0] != 0) return false;
    if (g.off[g.n] != (long long)g.adj.size() || (long long)g.adj.size() != 2 * g.m) return false;
    for (int u = 0; u < g.n; u++) {
        for (long long i = g.off[u]; i < g.off[u + 1]; i++) {
            int v = g.adj[i];
            if (v == u || v < 0 || v >= g.n) return false;
            if (i > g.off[u] && g.adj[i - 1] >= v) return false;
            bool back = false;
            for (long long j = g.off[v]; j < g.off[v + 1]; j++) back |= g.adj[j] == u;
            if (!back) return false;
        }
    }
    return true;
}

static std::vector<int> nbrs(const G& g, int v) {
    return std::vector<int>(g.adj.begin() + g.off[v], g.adj.begin() + g.off[v + 1]);
}

template <class F> static bool throws(F f) {
    try { f(); } catch (const std::exception&) { return true; }
    return false;
}

void test_io() {
    // from_edges cleaning: the edge 0-1 given three times (both directions),
    // a self-loop on 2, and vertex 3 with no edges.
    G g = from_edges(4, {{0, 1}, {1, 0}, {0, 1}, {2, 2}, {1, 2}});
    check(well_formed(g), "from_edges: well-formed CSR");
    check(g.n == 4 && g.m == 2, "from_edges: duplicates and self-loop removed (m == 2)");
    check(nbrs(g, 0) == std::vector<int>{1}, "from_edges: adj(0) == {1}");
    check(nbrs(g, 1) == std::vector<int>({0, 2}), "from_edges: adj(1) == {0,2}");
    check(nbrs(g, 2) == std::vector<int>{1}, "from_edges: adj(2) == {1}");
    check(g.deg(3) == 0, "from_edges: isolated vertex has degree 0");

    G empty = from_edges(0, {});
    check(empty.n == 0 && empty.m == 0 && empty.off.size() == 1, "from_edges: empty graph");
    check(throws([] { from_edges(2, {{0, 2}}); }), "from_edges: id out of range throws");

    // tiny.txt has ids 10, 20, 30, 1000 -> labels 0, 1, 2, 3.
    // Edges after cleaning: 10-20, 20-30, 1000-10 (the 30-30 self-loop is dropped).
    G t = load("tests/graphs/tiny.txt");
    check(well_formed(t), "load: well-formed CSR");
    check(t.n == 4 && t.m == 3, "load: tiny.txt has n == 4, m == 3");
    check(nbrs(t, 0) == std::vector<int>({1, 3}), "load: adj(10) == {20, 1000}");
    check(nbrs(t, 1) == std::vector<int>({0, 2}), "load: adj(20) == {10, 30}");
    check(nbrs(t, 2) == std::vector<int>{1}, "load: adj(30) == {20}, self-loop dropped");
    check(nbrs(t, 3) == std::vector<int>{0}, "load: adj(1000) == {10}");

    check(throws([] { load("tests/graphs/no_such_file.txt"); }), "load: missing file throws");
    {
        std::ofstream bad("bin/bad_edges.txt");
        bad << "# header\n1 2\n3 x\n";
    }
    check(throws([] { load("bin/bad_edges.txt"); }), "load: malformed line throws");
}
