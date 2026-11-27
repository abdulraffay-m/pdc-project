# Paper 20: Julienne

Dhulipala, Blelloch, Shun. *Julienne: A Framework for Parallel Graph Algorithms using Work-efficient Bucketing.* SPAA 2017. PDF in `09 Sources/`.

## What it is
An extension of **Ligra** (a shared-memory graph framework built around frontiers and `edgeMap`) with a **bucketing interface**. Ligra has no good way to keep vertices in many ordered buckets, so its k-core rescans every vertex for every level and does O(k_max·n + m) work. Julienne adds buckets and gets the first **work-efficient** parallel k-core with real parallelism.

## Bucket interface
`makeBuckets`, `nextBucket`, `getBucket`, `updateBuckets`.

## The three practical tricks (slide 3)
1. **Lazy updates.** When a vertex moves bucket, add a new entry and leave the old one. When a bucket is opened, skip any entry where `D[v]` no longer matches the bucket (or v is already peeled). Degrees only go down, so there's exactly one valid copy. Stale copies total at most about m, so the bound still holds.
2. **Window of n_B = 128 buckets plus one overflow bucket.** Only the next 128 levels are live. Anything higher waits in overflow and is redistributed when the window runs out.
3. **Block histograms plus a prefix sum instead of a semisort.** Split the moves into blocks of M = 2048, count per bucket per block, prefix-sum the counts to give every block its own write range, and write without locks.

## Bounds
- Work O(n + m), depth O(ρ log n), where ρ is the number of peeling rounds.

## Their experiments (k-core part)
- Machine: 72-core Xeon server, 1 TB RAM, 144 hyper-threads, Cilk Plus, g++ 5.4.1 -O3.
- Graphs (all symmetrised for k-core):

| Graph | n | m | ρ |
|---|---|---|---|
| com-Orkut | 3.1 M | 234 M (directed entries) | 5,667 |
| Twitter-Sym | 41.7 M | 2.4 B | 14,963 |
| Friendster | 124.8 M | 3.6 B | 10,034 |
| Hyperlink2012-Host-Sym | 101.7 M | 3.9 B | 19,063 |
| Hyperlink2012-Sym | 3.56 B | 225.8 B | 58,710 |
| Hyperlink2014-Sym | 1.72 B | 124.1 B | 130,728 |

- Results: 4–41× **self-relative** speedup; 2.6–9.2× faster than Ligra's work-inefficient k-core; about 1.3× faster than BZ on one thread (a vertex moves once per round instead of once per removed edge).
- Speedup is lowest on com-Orkut, where ρ is large relative to the graph size.

## Our critical review (slide 4)
**Strengths:** first work-efficient parallel k-core; small reusable interface; proven bounds plus practical tricks.
**Gaps:**
- Mostly self-relative speedup.
- One barrier per round, which is costly when ρ is large.
- Hub contention is never measured.
- Only tested on a 72-core server, not commodity machines.

## Code
GBBS repo, `benchmarks/KCore/JulienneDBS17` (https://github.com/ParAlg/gbbs). Reference reading only, see [[Decision Log]].
