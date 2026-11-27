# B2: Simplified Sampling Baseline (from paper #36)

Owner: **Raffay**. File: `src/sample.cpp`. Credit: Liu, Dong, Gu, Sun, SIGMOD 2025, Section 4.1.

## Why it exists
The project guide says a newer paper on the same idea becomes the baseline. #36 attacks hub contention with sampling, so we compare C1 against it.

## What we keep from #36 (simplified)
Per vertex sampler: `mode`, `rate`, `cnt`.
- **Enter sample mode** if `deg(v) > τ` (same τ as C1 for a fair comparison) and `D[v]·r > k`.
- **Rate:** `rate = μ / ((1 − r) · D[v])`, with `μ = 4·c·ln n`, c = 3, r = 0.1 (their defaults).
- **In sample mode**, a removed edge to v does `atomic cnt[v]++` with probability `rate`, instead of decrementing D[v].
- **Resample** when `cnt[v]` reaches μ: recount v's true degree from live neighbours, then either leave sample mode or reset the rate.
- **Safety:** before v could reach level k, it must leave sample mode and be recounted exactly. This keeps the output exact.

## What we leave out
Their online peeling framework, HBS, and the restart-on-error path (we validate against B0 instead, and stop if any mismatch appears).

## Randomness
Use a per-thread RNG seeded from `o.seed + tid`, so runs are reproducible.

## Tests
All of [[Correctness]], plus the star with 10⁵ leaves, plus a check that mismatches never appear across 100 seeds.

## Viva questions to be ready for
- Why is sampling still exact? (Recount before any decision near k.)
- What does μ control? (How many samples before trusting the estimate; Θ(log n) gives the probability guarantee.)
- Why did we simplify it? (Time, and the comparison only needs the contention-reducing part.)
