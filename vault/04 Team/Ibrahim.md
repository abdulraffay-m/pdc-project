# Ibrahim: Bucket Structure, B1, S

Ibrahim Azad, 23i-3049.

## Your tasks (see [[Task Board]])
- **T2a** Publish `opts.h`, `bkt.h`, `split.h`, `variants.h` headers on day 1, so Hadeed and Raffay can code against them.
- **T2** Bucket structure: lazy entries, n_B window plus overflow, block histograms plus prefix sum.
- **T3** B1 Julienne-style peeling.
- **T6** S hooks: `for_edges` with vertex and edge decomposition, runtime schedules, imbalance counters.
- **T10** (optional, with Hadeed) GBBS reference run on com-Orkut.
- **T11** C2, Tier 2 only.
- **T12a** README.

## Read first
[[Paper 20 - Julienne]], [[Interfaces]], [[S Scheduling Study]], [[C2 Local Queues]].

## Viva: be ready to explain
- The three tricks: lazy updates, the 128-bucket window, histograms plus prefix sum.
- Why the clamp is `max(D − c, k)` and when it's applied.
- Why work is O(n + m) and depth is O(ρ log n).
- Vertex vs edge decomposition and the three schedules, with your results.
- Why we reimplemented instead of using GBBS.
