# Defence Feedback (Milestone 2)

Recorded from memory after the proposal defence, so the wording isn't exact. Original notes: `09 Sources/TeachersInput-Defense.txt`.

## 1. "Are you using different datasets than the paper? If yes, how will you compare?"
**Our answer and actions:**
- Julienne's graphs (Twitter, Friendster, Hyperlink) have 2 to 225 billion edges and need a 1 TB server. They don't fit on our laptops.
- **Anchor graph: com-Orkut.** It's in Julienne's experiments *and* in #36's, and at about 117M undirected edges it fits on the 16 GB machines. We run B1 on it and compare the *shape* of results (rounds ρ, speedup trend, where time goes) with the papers' reported behaviour.
- **Same-hardware reference run (optional, [[Task Board]] T10):** build GBBS and run the authors' own Julienne k-core on com-Orkut on our machine, then compare it with our B1. Same graph, same hardware, their code against ours.
- The other SNAP and R-MAT graphs answer *our* question (skewed vs flat), which the papers don't isolate.
- In the report, say plainly that absolute times aren't comparable across hardware and compare trends instead.

## 2. "You need to test on 4, 8, ... threads"
**Our answer and actions:**
- Fixed thread counts: **1, 2, 4, 8, 12** (12 only on the 12-thread machines).
- Every machine runs the full sweep up to its own limit. See [[Machines]].
- Report strong scaling with speedup against B0 (absolute), not only against our own 1-thread run.

## Open
- [ ] Anything else said in the defence that one of us remembers? Add it here.
