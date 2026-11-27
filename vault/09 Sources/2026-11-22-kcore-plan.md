# Parallel k-Core with Work-Efficient Bucketing — Implementation Plan

**Goal:** OpenMP k-core decomposition built on a simplified Julienne-style bucket structure, compared against a sequential baseline and against a recent-paper baseline, with our own contention and scheduling contributions.

**Architecture:** One C++17 program, CSR graph in memory, one source file per variant behind a shared `int* run(const G&, Opts&)` interface so the driver, the validator and the timing harness are shared.

**Tech stack:** C++17, g++ (>= 9), OpenMP, Linux or WSL2, `-O3 -march=native -fopenmp`, Python only for plots.

**Spec:** the approved design (this conversation) and the Milestone 2 proposal.

## Global constraints

- Peeling only for k-core. No delta-stepping, set cover, Ligra, semisort or compression.
- Every variant must give core numbers identical to B0 on every input.
- Timing covers the kernel only, reported as the median of 5 runs. No numbers are copied from either paper.
- Tier 1 (B0, B1, B2, C1, scheduling study) is frozen on 30 Nov. Tier 2 (C2) only starts after the freeze.

## Review focus

1. Isolated vertices (degree 0): core 0, and they never enter the bucket loop incorrectly.
2. A vertex whose degree drops below k in one round from several neighbours at once: the clamp `max(d, k)` must apply after all decrements.
3. Stale bucket entries: a vertex moved twice in one round appears once in the right bucket.
4. Hubs with degree above the nB window go to the overflow bucket and come back in order.
5. Thread count 1 must give the same output and roughly B0's time.

## Tasks

### Task 1: CSR loader, B0 and validator
Files: `src/graph.h`, `src/io.cpp`, `src/bz.cpp`, `src/check.cpp`, `tests/`.
Produces: `G load(const char*)` (SNAP edge list, symmetrised, self-loops and duplicates removed); `int* bz(const G&)`; `bool same(const int*, const int*, int n)`; `bool is_core(const G&, const int*)`.
Tests: the 5-vertex example (E=D=1, A=B=C=2); the square plus pendant (T=1, rest 2); a clique K5 (all 4); a path (all 1); an isolated vertex (0).

### Task 2: Bucket structure
Files: `src/bkt.h`, `src/bkt.cpp`.
Produces: `Bkt(int n, const int* d, int nb)`, `pair<int, vector<int>> next()`, `void update(const int* id, const int* to, int k)`.
Algorithm: lazy entries; window of `nb` buckets plus one overflow; `update` uses per-block histograms (block size 2048) with an exclusive prefix sum so each thread writes to disjoint slots.
Tests: the same id moved twice is returned once; overflow ids reappear when the window advances; `next` returns the current bucket again after re-insertion.

### Task 3: B1, Julienne-style parallel peeling
File: `src/julienne.cpp`. Produces `int* jul(const G&, Opts&)`.
Per round: parallel scan of the open bucket's edges, count removed edges per neighbour, apply once per neighbour with clamp `max(d - c, k)`, collect moved ids, then `update`.
Tests: equal to B0 on all Task 1 graphs and on 100 random G(n,p) graphs, at 1, 2, 4 and 8 threads.

### Task 4: B2, simplified sampling baseline (after #36)
File: `src/sample.cpp`. Produces `int* smp(const G&, Opts&)` with `Opts.p`, `Opts.th`.
Hubs above `th` take sampled decrements; when a hub's estimate gets within a safety margin of k it is recounted exactly from live neighbours.
Tests: same as Task 3, plus a star graph with a hub of degree 10^5.

### Task 5: C1, degree-aware hybrid update (ours)
File: `src/hybrid.cpp`. Produces `int* hyb(const G&, Opts&)` with `Opts.th`.
Targets with degree <= th use `#pragma omp atomic` decrements; hubs use per-thread counters merged once at the end of the round.
Tests: same as Task 4. Instrumentation counts atomics per round.

### Task 6: Driver and experiments
Files: `src/main.cpp`, `scripts/run.sh`, `scripts/plot.py`.
Options: `-a {bz,jul,smp,hyb,lq}`, `-t threads`, `-s {static,dynamic,guided}`, `-d {vtx,edge}`, `-nb`, `-th`, `-p`, `-r 5`.
Outputs a CSV row with graph, n, m, variant, threads, schedule, decomposition, rounds, atomics, imbalance and median time.

### Task 7 (Tier 2): C2, local-queue peeling
File: `src/lq.cpp`. Produces `int* lq(const G&, Opts&)` with `Opts.q`.
A neighbour that drops to exactly k is pushed onto the thread's bounded local queue and peeled in the same round. Queue size is set from the current bucket size.
Tests: equal to B0 everywhere; the reported round count is <= B1's.
