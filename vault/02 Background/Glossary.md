# Glossary

| Term | Meaning |
|---|---|
| **Coreness / core number** | Largest k such that a vertex is in the k-core |
| **Degeneracy (k_max)** | Largest core number in the graph |
| **Peeling** | Repeatedly removing the lowest-degree vertices |
| **ρ (rho)** | Number of peeling rounds. Sets the depth and the number of barriers |
| **Work** | Total number of operations over all threads |
| **Depth (span)** | Longest chain of steps that must happen one after another |
| **Work-efficient** | Parallel version does asymptotically the same work as the best sequential one |
| **Self-relative speedup** | Parallel time vs your own code on 1 thread |
| **Absolute speedup** | Parallel time vs the best sequential code (for us, B0) |
| **Strong scaling** | Fixed input, more threads |
| **CSR** | Compressed Sparse Row: `off[v]..off[v+1]` indexes into `adj`, which holds v's neighbours |
| **Bucket** | A list of vertices with the same current degree |
| **Lazy update** | Leave a stale entry in the old bucket and skip it later |
| **Overflow bucket** | Holds vertices whose degree is beyond the live window |
| **Prefix sum (scan)** | Running totals, computed in parallel; gives each thread its own write range |
| **Histogram** | Per-block counts of how many items go to each bucket |
| **Atomic / CAS** | Hardware operation that updates a value without a race; compare-and-swap is one kind |
| **Contention** | Many threads updating the same memory location at once |
| **Cache-line bouncing** | One cache line moving between cores because they all write to it |
| **Hub** | A vertex with very high degree (above threshold τ) |
| **Power-law / skewed graph** | Few huge-degree vertices, many tiny-degree ones |
| **Reduction** | Combining per-thread partial results into one (here, summing hub counters) |
| **Load imbalance** | One thread gets far more work, the others wait. Measured as max/mean edges per thread |
| **Barrier** | Point where all threads wait for each other |
| **static / dynamic / guided** | OpenMP loop schedules: fixed split / grab chunks on demand / shrinking chunks |
| **Vertex vs edge decomposition** | Split a round's work by number of vertices, or by number of edges (using a prefix sum over degrees) |
| **Sampling (B2)** | #36's trick: random subset of decrements on hubs, recount when enough samples |
| **VGC (C2)** | #36's trick: local queue to peel chains in the same subround |
| **R-MAT** | Synthetic graph generator with tunable skew |
| **SNAP** | Stanford graph dataset collection |
