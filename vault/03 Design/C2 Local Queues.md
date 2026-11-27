# C2: Local-Queue Peeling (Tier 2, stretch)

Owner: **Ibrahim**. File: `src/lq.cpp`. Credit: VGC from paper #36, Section 4.2. **Not claimed as our contribution.**

Only starts after the Tier 1 freeze ([[Timeline]]).

## Idea
When a decrement drops a neighbour to exactly k, the thread pushes it onto its own bounded local queue and peels it straight away, in the same round. Chains of low-degree vertices get peeled without extra global barriers, so ρ goes down.

## Our variation
#36 fixes the queue at 128. We try sizing it from the current bucket size (`-q`), so small buckets do more local work per barrier.

## The hard part
C2 needs a neighbour's **current** degree mid-round, which C1 deliberately delays for hubs. So C2 is built on B1 first. Combining C2 with C1 is extra credit only.

## Success measure
Fewer rounds and less time than B1 on high-ρ graphs, with exact output.
