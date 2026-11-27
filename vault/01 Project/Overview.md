# Overview

## The problem
**k-core decomposition** gives every vertex a *core number*: the largest k such that the vertex survives in a subgraph where everyone has at least k neighbours. It's computed by **peeling**: repeatedly delete the lowest-degree vertex, and the level at which it's deleted is its core number. Background is in [[k-core and Peeling]].

Peeling is hard to parallelise because each round depends on the one before it.

## The paper (Julienne, #20)
Julienne keeps vertices in **buckets** by current degree, so each round only touches what changed. That makes parallel k-core **work-efficient**: O(n + m) total work, the same as the sequential BZ algorithm. Details in [[Paper 20 - Julienne]].

## The newer paper (#36)
Liu, Dong, Gu and Sun (SIGMOD 2025) attack Julienne's weak spots with **sampling** for hub contention and **VGC** (local queues) for round overhead. The project guide says a newer paper on the same idea becomes our baseline, so we use a simplified version of its sampling as **B2**. Details in [[Paper 36 - Liu et al 2025]].

## What we build
| Id | What | Whose idea |
|---|---|---|
| B0 | Sequential BZ peeling, the reference | Batagelj and Zaversnik |
| B1 | Julienne-style OpenMP peeling | Julienne |
| B2 | Simplified sampling baseline | Paper #36 |
| **C1** | **Degree-aware hybrid hub update** | **Ours** |
| **S** | **Scheduling and decomposition study** | **Ours** |
| C2 | Local-queue peeling (stretch) | Paper #36 (VGC), credited |

Full table: [[Variants]].

## Our claim, in one sentence
On graphs with big hubs, C1 removes the atomic traffic jam on hub counters and runs faster than B1 with identical output. On flat graphs it makes little difference. We compare it head to head with #36's sampling.

## Honest framing
- #36 already found the hub contention problem. Our contribution is a **different, exact** fix (no randomness, no recount) and a measured comparison, not the discovery of the problem.
- We build on the papers' **ideas** and write our own **code**. See [[Decision Log]].

## Tiers
- **Tier 1** (must finish): B0, B1, B2, C1, S, all experiments. This is a complete project on its own.
- **Tier 2** (only after the Tier 1 freeze): C2.

The freeze date is in [[Timeline]].
