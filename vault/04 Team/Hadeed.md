# Hadeed: C1, Driver and Experiments

Muhammad Hadeed, 23i-0764.

## Your tasks (see [[Task Board]])
- **T7a** Driver skeleton (`main.cpp`): CLI, B0 comparison, CSV output. Can start day 1 using B0 only.
- **T5** C1 hybrid hub update, against the headers Ibrahim publishes (T2a). Validate once T3 lands.
- **T7** `scripts/run.sh` (benchmark sweep) and `scripts/plot.py`.
- **T9** Collect everyone's CSVs, make the figures.
- **T10** (optional, with Ibrahim) GBBS reference run.
- **T12c** Demo.

## Read first
[[C1 Hybrid Update]], [[Interfaces]], [[Experiment Plan]], [[Paper 36 - Liu et al 2025]] (to confirm C1 isn't already in it).

## Machine notes
8C/12T, 16 GB: the best machine for scaling and com-Orkut.

## Viva: be ready to explain
- The hub contention problem and why atomics serialise on a hub.
- How C1 works, why it's exact, and why only hubs get private counters.
- How C1 differs from #36's sampling.
- The results: what improved, where, and why, using the atomic and imbalance counters.
