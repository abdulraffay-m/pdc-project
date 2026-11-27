# Correctness

**The rule:** every parallel variant must give exactly the same core numbers as B0, vertex for vertex, on every graph, at every thread count. A run that fails this is a bug, and its timing is thrown away.

## How it's enforced
1. The driver runs B0 once per graph and compares every variant's output with `same()`. The CSV has a `valid` column.
2. `is_core()` checks the answer independently of B0: for each k, the vertices with core ≥ k all have at least k neighbours among themselves, and no vertex with core = k survives in the (k+1)-core.
3. `make test` must pass before any pull request is merged.

## Hand-checked test graphs (`tests/`)
| Graph | Expected |
|---|---|
| Slide example (L1..L6, H, A, B, C) | leaves and H = 1; A, B, C = 2 |
| 5-vertex proposal example | E = D = 1; A = B = C = 2 |
| 4-cycle plus a pendant | pendant = 1, rest = 2 |
| Clique K5 | all 4 |
| Path of 10 | all 1 |
| Star with 10⁵ leaves | all 1 (hub stress test for B2, C1) |
| Isolated vertex | 0 |
| Empty graph | no crash |

## Fuzzing
100 random G(n, p) plus R-MAT graphs per variant at 1, 2, 4 and 8 threads, with fixed seeds so failures can be reproduced. Races often show up only sometimes, so a single passing run proves little.

## Known traps (from the plan's review focus)
1. **Isolated vertices**: core 0, and they must not break the bucket loop.
2. **Clamp order**: `max(D - c, k)` applies only after *all* of the round's decrements to v. In C1 this means after the hub merge.
3. **Stale entries**: a vertex moved twice in one round must appear once in the correct bucket.
4. **Overflow**: hubs above the n_B window come back from overflow in the right order.
5. **1 thread**: output identical, time close to B0.
6. **B2 sampling**: must recount before it could make a wrong decision. Test with the star graph.
