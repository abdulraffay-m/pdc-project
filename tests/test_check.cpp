// Tests for check.cpp. Each check is tested on right answers (must accept)
// and on wrong ones (must reject); a checker that accepts everything would
// otherwise pass silently. Rejections print their reason to stderr, so
// "is_core: ..." lines in the test output are expected.

#include "tests.h"

void test_check() {
    check(same({1, 2, 3}, {1, 2, 3}), "same: equal vectors");
    check(!same({1, 2, 3}, {1, 5, 3}), "same: mismatch detected");
    check(!same({1, 2}, {1, 2, 3}), "same: size difference detected");
    check(same({}, {}), "same: empty vectors");

    // The 5-vertex proposal example: triangle A,B,C, plus A-D and D-E.
    // A=0, B=1, C=2, D=3, E=4. Cores: A=B=C=2, D=E=1.
    G p = from_edges(5, {{0, 1}, {1, 2}, {2, 0}, {0, 3}, {3, 4}});
    check(is_core(p, {2, 2, 2, 1, 1}), "is_core: accepts proposal example");
    check(!is_core(p, {0, 0, 0, 0, 0}), "is_core: rejects all zeros (too low)");
    check(!is_core(p, {2, 2, 2, 2, 1}), "is_core: rejects D = 2 (too high)");
    check(!is_core(p, {2, 2, 2, 1, 0}), "is_core: rejects E = 0 (too low)");
    check(!is_core(p, {2, 2, 2, 1}), "is_core: rejects wrong size");

    // K5: every vertex has core 4.
    std::vector<std::pair<int,int>> k5;
    for (int u = 0; u < 5; u++)
        for (int v = u + 1; v < 5; v++) k5.push_back({u, v});
    G k = from_edges(5, k5);
    check(is_core(k, {4, 4, 4, 4, 4}), "is_core: accepts K5 all 4");
    check(!is_core(k, {3, 3, 3, 3, 3}), "is_core: rejects K5 all 3 (too low)");
    check(!is_core(k, {5, 5, 5, 5, 5}), "is_core: rejects K5 all 5 (above degree)");

    check(is_core(from_edges(0, {}), {}), "is_core: empty graph");
    check(is_core(from_edges(1, {}), {0}), "is_core: isolated vertex has core 0");
}
