# S: Scheduling and Decomposition Study (our contribution)

Owner: **Ibrahim** (hooks in `src/split.h`); runs are done by everyone; plots by Hadeed.

## Question
Which way of sharing a round's work between threads is fastest, and does it depend on the graph?

## Two decompositions
- **By vertex (`-d vtx`)**: each loop iteration is one peeled vertex and all its edges. Simple, but a thread that gets a hub does far more work.
- **By edge (`-d edge`)**: exclusive prefix sum over the peeled vertices' degrees gives every edge a global index, and the loop runs over edges. Each thread gets about the same number of edges.

Example: degrees `[1,1,1,1,1000,1,1,1]` on 4 threads. By vertex, one thread walks about 1001 edges and the others about 2. By edge, each walks about 252.

## Three schedules
`static`, `dynamic`, `guided` via `omp_set_schedule()` and `schedule(runtime)`. Chunk sizes swept where it matters.

## Bucket parameters
n_B ∈ {16, 32, 64, 128, 256} and block size M, because the paper tuned them for 72 cores.

## Metrics
- Time per configuration.
- **Imbalance ratio** per round = max / mean edges per thread, averaged over rounds.

## Grid
`{B1, B2, C1} × {static, dynamic, guided} × {vtx, edge} × threads {1,2,4,8,12}` on each graph. Keep it small: run the full grid on 3 graphs (one flat, one skewed, com-Orkut), and only the winners elsewhere.

## Link with C1
Edge decomposition fixes balance but spreads a hub's edges over every thread, which makes contention worse. That's why C1 and S are studied together.
