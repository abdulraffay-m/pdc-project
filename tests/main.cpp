// Test runner for `make test`. Runs every module's tests and exits with a
// non-zero status if any check failed, which fails make and the CI job.
// Run from the repo root (make does this), because the loader tests open
// files under tests/graphs/.

#include "tests.h"

#include <cstdio>

static int run = 0, failed = 0;

void check(bool ok, const std::string& what) {
    run++;
    if (!ok) {
        failed++;
        std::printf("FAIL: %s\n", what.c_str());
    }
}

int main() {
    test_io();
    test_check();
    std::printf("tests: %d run, %d failed\n", run, failed);
    return failed ? 1 : 0;
}
