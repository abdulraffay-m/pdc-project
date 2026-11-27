# Decision Log

Newest first. Add a row whenever we decide something the others need to know. Never delete a row; if we change our minds, add a new one that replaces it.

| Date | Decision | Why | Decided by |
|---|---|---|---|
| 2026-11-27 | Variants return `std::vector<int>` instead of `int*` (changes the earlier plan) | No manual memory handling, same speed | Ibrahim |
| 2026-11-27 | GBBS goes in as a git submodule under `external/gbbs`, used only for reading and the reference run | Keeps their code clearly separate from ours; satisfies acknowledgement rules | Ibrahim |
| 2026-11-27 | We reimplement from the papers' ideas; no code is taken from GBBS or #36's code | OpenMP is needed for the S study; the viva needs code we can explain; the proposal commits to it; the course comment said to avoid the full framework | Group |
| 2026-11-27 | com-Orkut is the anchor graph for comparison with both papers | Teacher's defence question on datasets; it fits in 16 GB | Group |
| 2026-11-27 | Thread counts 1, 2, 4, 8, 12 | Teacher's defence comment | Group |
| 2026-11-27 | Rebalanced work split (see [[Roles]]) | The proposal's split overloaded Hadeed and left two members without a contribution to defend | Group |
| 2026-11-27 | Submitted code is commented | Milestone 3 grades "proper comments" | Group |
| Milestone 2 | Scope is k-core only, not Δ-stepping | More traffic through buckets; exact output makes checking easy | Group |
| Milestone 2 | No MPI | k-core needs a global sync every round, over thousands of rounds | Group |
| Milestone 2 | Paper #36's sampling is baseline B2 | Project guide: a newer paper on the same idea becomes the baseline | Group |
