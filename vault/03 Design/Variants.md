# Variants

| Id | Name | File | CLI `-a` | Owner | Tier | Idea from |
|---|---|---|---|---|---|---|
| B0 | Sequential BZ | `src/bz.cpp` | `bz` | Raffay | 1 | Batagelj and Zaversnik 2003 |
| B1 | Julienne-style parallel | `src/julienne.cpp` | `jul` | Ibrahim | 1 | Paper #20 |
| B2 | Simplified sampling | `src/sample.cpp` | `smp` | Raffay | 1 | Paper #36, Sec 4.1 |
| C1 | Degree-aware hybrid update | `src/hybrid.cpp` | `hyb` | Hadeed | 1 | **Ours** |
| S | Scheduling and decomposition study | `src/split.h` + flags in every parallel variant | `-s`, `-d` | Ibrahim | 1 | **Ours** |
| C2 | Local-queue peeling | `src/lq.cpp` | `lq` | Ibrahim | 2 | Paper #36, Sec 4.2 (VGC) |

## What differs between B1, B2 and C1
All three share the bucket structure, the round loop and the clamp. They differ only in **how a removed edge (u → v) updates v's counter**:

| Variant | Low-degree target v | Hub target v |
|---|---|---|
| B1 | atomic `cnt[v]++` | atomic `cnt[v]++` |
| B2 | atomic `cnt[v]++` | with probability `rate[v]`, atomic `smp[v]++`; recount when `smp[v]` reaches μ |
| C1 | atomic `cnt[v]++` | thread-private `loc[t][hid[v]]++`, summed once per round |

Then, for every touched v: `D[v] = max(D[v] - cnt[v], k)` and re-bucket.

## Comparisons we run
- B0 vs B1: does the paper's method scale on laptops?
- **B1 vs C1**: our main result.
- **C1 vs B2**: our fix against the newer paper's fix.
- S grid on B1, B2 and C1.
- C2 vs B1 (Tier 2 only).

Details: [[C1 Hybrid Update]], [[B2 Sampling Baseline]], [[S Scheduling Study]], [[C2 Local Queues]].
