// Shared by all test files. Each module has one test file defining one
// test_<module>() function; tests/main.cpp calls them all. To add a
// module's tests: declare its function here and call it from main().

#pragma once

#include "graph.h"

#include <string>

// Records one check. A failure prints `what` and makes `make test` fail.
void check(bool ok, const std::string& what);

void test_io();
