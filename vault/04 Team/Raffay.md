# Raffay: Foundation, Correctness and B2 (lead)

Abdul Raffay Moazzam, 23i-0587.

## Your tasks (see [[Task Board]])
- **T0** Repo setup: Makefile, folders, GBBS submodule, CI workflow. Unblocks everyone, so do it first (day 1).
- **T1** CSR loader, B0, validator, hand-checked tests. Everyone depends on this. Target: day 2.
- **T8** Dataset script (download SNAP, symmetrise) and R-MAT generator; fuzz-test harness.
- **T4** B2 simplified sampling.
- Lead: GitHub repo settings and branch protection, task board, syncs, slides lead, final edit of the report, final submission.

## Read first
[[k-core and Peeling]], [[Interfaces]] (Graph, checks), [[Correctness]], [[B2 Sampling Baseline]], [[Paper 36 - Liu et al 2025]] Section 4.1.

## Machine notes
7.3 GB RAM, so skip com-Orkut. Everything else fits.

## Viva: be ready to explain
- How BZ works and why it's O(n + m).
- How `load` turns a SNAP edge list into CSR (symmetrise, dedupe, relabel).
- How we know a parallel result is right (`same`, `is_core`, fuzzing).
- B2: sampling, μ, the recount, and why it's still exact.
- Why the B2 vs C1 comparison is fair (same τ, same bucket code, same split helper).
