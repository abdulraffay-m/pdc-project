# C1: Degree-Aware Hybrid Update (our main contribution)

Owner: **Hadeed**. File: `src/hybrid.cpp`.

## The problem
In B1 each removed edge does an atomic increment on its target's counter. If thousands of removed vertices share one hub, all threads queue on that single counter, and its cache line bounces between cores.

## The idea in one line
Hubs get thread-private counters, everyone else keeps the shared atomic counter.

## Picture
One scoreboard with one pen (atomics, people queue) versus everyone keeping a sticky note and adding the notes up once at the end.

## Design
1. **Before peeling:** threshold `τ = o.th × (2m / n)`. Every vertex with `deg(v) > τ` is a hub and gets an index `hid[v]` in `0..H-1`. There are at most 2m/τ hubs, so this stays small.
2. **Per-thread arrays:** `loc[t]` of size H for each thread. Pad each thread's array to a cache-line boundary to avoid false sharing between threads.
3. **Edge loop** (through `for_edges` from [[Interfaces]]):
   - `deg(v) ≤ τ`: atomic `cnt[v]++`, as in B1.
   - hub: `loc[tid][hid[v]]++`, no atomic.
4. **Merge** (parallel over hubs): `cnt[v] = Σ_t loc[t][hid[v]]`, then zero the locals that were touched. Keep a per-thread list of touched hubs so the merge doesn't scan all H every round.
5. **Clamp and re-bucket**, exactly as B1: `D[v] = max(D[v] - cnt[v], k)`.

## Why it's exact
- Addition is commutative and associative, so the sum of private counts equals the number of atomic increments B1 would have done.
- Nobody reads a hub's degree mid-round. The round's peel set is fixed at the start, and new degrees are only used after the round.

So C1's output is identical to B1's by construction. Tests confirm it against B0.

## What we measure
- Time vs B1 and B2 on skewed graphs (SNAP social, R-MAT with rising skew) and flat graphs (roadNet-CA).
- **Atomics per round** (instrumented build) to show the reduction directly.
- τ sweep: `th ∈ {4, 8, 16, 32, 64}`.

## Expected result
Matches B1 on flat graphs, beats B1 on power-law graphs, competitive with B2 without B2's recount cost or probability parameter. If not, we report that and explain it from the counters.

## Viva questions to be ready for
- Why not use private counters for every vertex? (Memory n × threads, and the merge would cost O(n) per round.)
- Why is it exact? (Above.)
- How is it different from #36's sampling? (See the table in [[Paper 36 - Liu et al 2025]].)
- What happens with edge decomposition? (A hub's edges spread over all threads, which worsens contention in B1 and is exactly where C1 helps most.)
