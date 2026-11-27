# Datasets

All undirected after symmetrising. Sizes approximate. Downloaded by `scripts/get_data.sh` into `data/` (git-ignored). Source: SNAP, https://snap.stanford.edu/data/

| Graph | n | m | Type | Why | Machines |
|---|---|---|---|---|---|
| roadNet-CA | 2.0 M | 2.8 M | Road, flat degrees | No hubs; C1 should not help | all |
| com-Youtube | 1.1 M | 3.0 M | Social, skewed | Small skewed graph | all |
| web-Google | 0.9 M | 4.3 M | Web, hubs | Hubs, τ sweep | all |
| com-LiveJournal | 4.0 M | 34.7 M | Social | Large skewed graph | all |
| **com-Orkut** | 3.1 M | 117 M | Social, many rounds | **Anchor: used in both papers** | Ibrahim, Hadeed only |
| R-MAT | 2²⁰–2²³ | 16n | Synthetic | Controlled skew for C1 | all (size to RAM) |

## Notes
- com-Orkut needs roughly 1–2 GB in CSR plus loading overhead. Not on the 7.3 GB machine.
- R-MAT skew parameters (a, b, c, d): start from (0.57, 0.19, 0.19, 0.05) for strong skew and move toward (0.25, 0.25, 0.25, 0.25) for flat. Fix seeds.
- Every dataset goes in [[Acknowledgements]] with its citation.
