# Build for the k-core project (see vault/03 Design/Interfaces.md).
#
#   make        builds bin/kcore, the optimised driver used for benchmarks
#   make test   builds bin/tests with sanitizers and runs it
#   make clean  removes bin/
#
# Sources are found with wildcards, so a new src/*.cpp or tests/*.cpp is
# picked up without editing this file. That also lets the build work while
# most of the planned files don't exist yet.
#
# There are no object files: every build compiles all sources in one g++
# call. The project is small, so this takes seconds, and it means a changed
# header can never leave a stale object behind.

CXX      = g++
WARN     = -std=c++17 -Wall -Wextra

# Benchmark build: flags fixed by Interfaces.md.
OPT      = -O3 -march=native -fopenmp

# Test build: AddressSanitizer catches out-of-bounds and use-after-free,
# UndefinedBehaviorSanitizer catches overflow and bad shifts. -O1 keeps it
# reasonably fast; -g gives file:line in sanitizer reports. -fopenmp is kept
# so tests exercise the parallel code paths.
DBG      = -O1 -g -fsanitize=address,undefined -fno-omit-frame-pointer -fopenmp

SRC      = $(wildcard src/*.cpp)
HDR      = $(wildcard src/*.h)
# Tests link every module except the driver, because tests have their own main().
LIB      = $(filter-out src/main.cpp,$(SRC))
TESTS    = $(wildcard tests/*.cpp)
TESTHDR  = $(wildcard tests/*.h)

all: bin/kcore

bin/kcore: $(SRC) $(HDR)
	@mkdir -p bin
	$(CXX) $(WARN) $(OPT) $(SRC) -o $@

bin/tests: $(LIB) $(TESTS) $(HDR) $(TESTHDR)
	@mkdir -p bin
	$(CXX) $(WARN) $(DBG) -Isrc $(LIB) $(TESTS) -o $@

test: bin/tests
	./bin/tests

clean:
	rm -rf bin

.PHONY: all test clean
