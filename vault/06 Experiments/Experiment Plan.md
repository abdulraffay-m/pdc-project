# Experiment Plan

## Method
- Time **only the kernel** with `omp_get_wtime()`, not loading or CSR building.
- Each configuration runs **5 times**; report the **median**.
- Threads **1, 2, 4, 8, 12** (up to each machine's limit, see [[Machines]]).
- Speedup = T(B0) / T(variant), i.e. absolute, not self-relative. Efficiency = speedup / threads.
- Every run is validated against B0. Invalid runs are discarded and logged as bugs.
- Record the machine name in every CSV row.
- Close other heavy programs while benchmarking; on laptops, plug in the charger and use the high-performance power mode.

## Experiments
| # | Question | Variants | Graphs | Output |
|---|---|---|---|---|
| E1 | Does the paper's method scale on laptops? | B0, B1 | all | speedup vs threads |
| E2 | **Does C1 beat B1, and how does it compare with B2?** | B1, B2, C1 | skewed SNAP, R-MAT with rising skew, roadNet-CA | time, atomics per round |
| E3 | Best threshold τ | C1 (and B2) | R-MAT, web-Google | time vs th ∈ {4,8,16,32,64} |
| E4 | Schedule × decomposition | B1, B2, C1 | roadNet-CA, com-LiveJournal, com-Orkut | time, imbalance ratio |
| E5 | Bucket window and block size | B1 | 2 graphs | time vs n_B, M |
| E6 | Anchor comparison with the papers | B1 (and GBBS if T10 done) | com-Orkut | ρ, speedup trend, our B1 vs their code |
| E7 | (Tier 2) Fewer rounds with C2? | B1, C2 | high-ρ graphs | ρ, time |

## Expected outcomes (from the proposal)
- B1 scales on large low-ρ graphs and is limited by round overhead on high-ρ graphs like com-Orkut.
- C1's gain over B1 grows with skew; little or no gain on roadNet-CA.
- Edge decomposition matters most on graphs with hubs.

Modest or negative results get reported and explained with the counters, not hidden.

## Figures for the report (plan now, make later)
1. Speedup vs threads, B1 and C1, per machine.
2. C1 vs B1 vs B2 time across graphs (bar chart).
3. Atomics per round, B1 vs C1.
4. Schedule × decomposition heatmap with imbalance.
5. com-Orkut anchor: ρ and speedup next to the papers' reported numbers.
