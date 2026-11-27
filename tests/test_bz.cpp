// Tests for B0 (bz.cpp): every hand-checked graph in
// vault/03 Design/Correctness.md must give its hand-computed core numbers,
// and B0's output must also pass the independent is_core() check.

#include "tests.h"

#include <random>

// Runs B0 on g and checks it against the hand-computed answer and is_core().
static void expect(const G& g, const std::vector<int>& want, const std::string& name) {
    std::vector<int> got = bz(g);
    check(same(got, want), "bz: " + name + " matches hand-computed cores");
    check(is_core(g, got), "bz: " + name + " passes is_core");
}

void test_bz() {
    // Slide example: leaves L1..L6 = 0..5 on hub H = 6, H-A, and triangle
    // A, B, C = 7, 8, 9. H has degree 7 but core 1: a high degree does not
    // mean a high core number.
    std::vector<std::pair<int,int>> slide = {{6, 7}, {7, 8}, {8, 9}, {9, 7}};
    for (int leaf = 0; leaf < 6; leaf++) slide.push_back({leaf, 6});
    expect(from_edges(10, slide), {1, 1, 1, 1, 1, 1, 1, 2, 2, 2}, "slide example");

    // Proposal example: triangle A, B, C = 0, 1, 2, then A-D, D-E (D = 3, E = 4).
    expect(from_edges(5, {{0, 1}, {1, 2}, {2, 0}, {0, 3}, {3, 4}}), {2, 2, 2, 1, 1},
           "proposal example");

    // 4-cycle 0-1-2-3-0 with pendant 4 on vertex 0.
    expect(from_edges(5, {{0, 1}, {1, 2}, {2, 3}, {3, 0}, {4, 0}}), {2, 2, 2, 2, 1},
           "4-cycle plus pendant");

    std::vector<std::pair<int,int>> k5;
    for (int u = 0; u < 5; u++)
        for (int v = u + 1; v < 5; v++) k5.push_back({u, v});
    expect(from_edges(5, k5), std::vector<int>(5, 4), "clique K5");

    std::vector<std::pair<int,int>> path;
    for (int v = 0; v + 1 < 10; v++) path.push_back({v, v + 1});
    expect(from_edges(10, path), std::vector<int>(10, 1), "path of 10");

    // Hub stress test (matters most for B2 and C1): hub 0 with 10^5 leaves.
    const int leaves = 100000;
    std::vector<std::pair<int,int>> star;
    for (int v = 1; v <= leaves; v++) star.push_back({0, v});
    expect(from_edges(leaves + 1, star), std::vector<int>(leaves + 1, 1), "star with 10^5 leaves");

    // Isolated vertices have core 0 and must not disturb the others.
    expect(from_edges(1, {}), {0}, "isolated vertex");
    expect(from_edges(4, {{0, 1}, {1, 2}, {2, 0}}), {2, 2, 2, 0}, "triangle plus isolated vertex");

    std::vector<int> none = bz(from_edges(0, {}));
    check(none.empty(), "bz: empty graph gives an empty answer");

    // End to end: tiny.txt is the path 1000-10-20-30, so every core is 1.
    expect(load("tests/graphs/tiny.txt"), {1, 1, 1, 1}, "tiny.txt via load");

    // Random graphs, checked by is_core only (no hand answer). Fixed seed so
    // a failure reproduces; the full fuzz harness is T8.
    std::mt19937 rng(1);
    for (int t = 0; t < 50; t++) {
        int n = 1 + rng() % 60;
        int p = 1 + rng() % 50;                  // edge probability, in percent
        std::vector<std::pair<int,int>> e;
        for (int u = 0; u < n; u++)
            for (int v = u + 1; v < n; v++)
                if ((int)(rng() % 100) < p) e.push_back({u, v});
        G g = from_edges(n, e);
        check(is_core(g, bz(g)), "bz: random graph " + std::to_string(t) + " passes is_core");
    }
}
