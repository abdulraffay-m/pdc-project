# Paper 36: Liu, Dong, Gu, Sun (SIGMOD 2025)

*Parallel k-Core Decomposition: Theory and Practice.* PDF in `09 Sources/`.

## Why it matters to us
It's the newer paper attacking the same problem. The project guide says it becomes our baseline, so its sampling idea is **B2**, and its VGC idea is our stretch goal **C2** (credited). Their headline: up to 52.5× faster than Julienne on 96 cores.

## Its three techniques
### 1. Sampling (reduces contention on high-degree vertices) → our B2
- Each vertex has a sampler: `mode` (sampling on or off), `rate`, `cnt` (samples taken).
- A vertex enters sample mode when its degree is above a `threshold` and is still far from k (`d̃[v]·r > k`).
- In sample mode, a decrement becomes `atomic_inc(cnt)` **with probability `rate`**, instead of an atomic decrement on the degree. Far fewer writes hit the hub.
- `rate = μ / ((1 − r) · d̃[v])`, with μ = Θ(log n) (they use μ = 4c·ln n, c > 2) and r = 10%.
- When `cnt` reaches μ, the vertex is **resampled**: its true degree is recounted from live neighbours, and it either leaves sample mode or gets a new rate.
- Errors are detected and corrected, so the output stays exact (Las Vegas, not Monte Carlo). Sampling doesn't break work-efficiency.

### 2. VGC: vertical granularity control (reduces round overhead on sparse graphs) → our C2
- When peeling a low-degree vertex, put neighbours that drop to k into a **local FIFO queue** and peel them in the same subround, instead of waiting for the next one.
- Queue size fixed at 128 in their code. When full, fall back to the normal next frontier.
- Cuts the number of subrounds by 5–40× on their graphs, and improves sparse graphs by 1.72–31.2×.

### 3. HBS: hierarchical bucketing structure (helps graphs with high coreness)
- Out of our scope. We keep Julienne's bucket structure.

## How C1 differs from their sampling
| | #36 sampling | Our C1 |
|---|---|---|
| Trick | Random subset of decrements on hubs | Per-thread private counters on hubs, merged by reduction once per round |
| Randomness | Yes (rate, μ, r) | None |
| Recount | Yes, on resample | Never needed |
| Parameters | threshold, μ, r | threshold τ only |
| Exact | Yes, after error correction | Yes, by construction |

Use this table in the viva. Don't claim C1 found the problem; claim it's a simpler, exact alternative, measured head to head.

## Open question to check
- [ ] Read their Section 4.1 fully and confirm they don't already use per-thread counters anywhere. (Owner: Hadeed, since C1 is his.)
