# k-core and Peeling

## Definitions
- **k-core**: the largest subgraph in which every vertex has at least k neighbours *inside* that subgraph.
- **Core number (coreness)** of v: the largest k for which v is in the k-core.
- **Degeneracy** (k_max): the largest core number in the graph.

## Peeling (the sequential idea)
Repeat until the graph is empty:
1. Find the vertex with the lowest current degree `D[v]`.
2. Remove it and record `core[v] = k`, where k is the current level.
3. Every neighbour still alive loses one degree.

The level k only goes up. Once we're at level 3, nothing can be sent back to level 2.

## Worked example (the one from the slides)
```
L1..L6 are leaves attached to H.   H is also connected to A.   A, B, C form a triangle.

Start:   D[L*] = 1, D[H] = 7, D[A] = 3, D[B] = 2, D[C] = 2
k = 1:   peel L1..L6       → core 1, D[H] drops 7 → 1
         peel H            → core 1, D[A] drops 3 → 2
k = 2:   peel A, B, C      → core 2
```
H started with degree 7 but has core 1, because all but one of its connections were leaves. A high degree doesn't mean a high core number.

## Two arrays, don't mix them up
- `D[v]`: working degree, changes all the time.
- `core[v]`: the answer, written once when v is peeled (it's the current k).

## The clamp
In the parallel version several decrements can hit v in the same round. The rule is
`D[v] = max(D[v] - c, k)`, where c is the number of removed neighbours this round.

Example: k = 3, D[h] = 6, four neighbours removed. Raw 6 − 4 = 2, clamped to 3. h survived to level 3, so its core is at least 3. It now gets peeled at level 3 along with the others. Without the clamp it would land in bucket 2, which has already been processed, and get the wrong answer.

## Sequential algorithm (BZ, our B0)
Batagelj and Zaversnik, O(n + m): bucket sort vertices by degree, process in order, and move a neighbour one bucket down on each decrement using position arrays. This is our correctness reference.

## Why it's hard to parallelise
- **Dependent rounds**: round i+1 needs the degrees left by round i.
- **Uneven rounds**: one round can have millions of vertices, the next just one.
- **Many rounds**: real graphs need thousands (com-Orkut: 5,667), so per-round overhead adds up.
- **Hubs**: many removed vertices hit one hub's counter at the same time.
