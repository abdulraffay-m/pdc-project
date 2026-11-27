# Task Board

Status: ⬜ todo · 🟡 in progress · ✅ done · ⛔ blocked

Move a task by editing its status. Add the PR link when you open one.

## Phase 1: Foundation
| Id | Task | Owner | Needs | Status | PR |
|---|---|---|---|---|---|
| T0 | Repo setup: Makefile, folders, GBBS submodule, CI workflow | Raffay | | ✅ | [#2](https://github.com/abdulraffay-m/pdc-project/pull/2) |
| T1 | CSR loader, B0 (BZ), `same`, `is_core`, hand-checked tests | Raffay | T0 | 🟡 | |
| T2a | Headers: `opts.h`, `bkt.h`, `split.h`, `variants.h` | Ibrahim | T0 | ⬜ | |
| T7a | Driver skeleton: CLI, B0 check, CSV row | Hadeed | T1 | ⬜ | |

## Phase 2: Variants
| Id | Task | Owner | Needs | Status | PR |
|---|---|---|---|---|---|
| T2 | Bucket structure with tests (stale skip, overflow, re-insert) | Ibrahim | T2a | ⬜ | |
| T3 | B1 Julienne-style peeling | Ibrahim | T1, T2 | ⬜ | |
| T6 | S hooks: `for_edges` (vtx/edge), runtime schedule, imbalance | Ibrahim | T2a | ⬜ | |
| T4 | B2 simplified sampling | Raffay | T1, T2, T6 | ⬜ | |
| T5 | C1 hybrid hub update, atomic counter instrumentation | Hadeed | T2a, T6; validate after T3 | ⬜ | |
| T8 | `get_data.sh`, R-MAT generator, fuzz harness | Raffay | T1 | ⬜ | |

## Phase 3: Experiments
| Id | Task | Owner | Needs | Status | PR |
|---|---|---|---|---|---|
| T7 | `run.sh` sweep and `plot.py` | Hadeed | T7a | ⬜ | |
| T9 | Benchmark runs on all 3 machines, results into `results/` | All | T3–T8 | ⬜ | |
| T10 | GBBS reference run on com-Orkut (optional) | Ibrahim, Hadeed | T0 | ⬜ | |
| — | **Tier 1 freeze** | | | | |

## Phase 4: Stretch
| Id | Task | Owner | Needs | Status | PR |
|---|---|---|---|---|---|
| T11 | C2 local-queue peeling | Ibrahim | freeze | ⬜ | |

## Phase 5: Deliverables (report last)
| Id | Task | Owner | Needs | Status | PR |
|---|---|---|---|---|---|
| T12a | README.md | Ibrahim | T9 | ⬜ | |
| T12b | Slides (5–7) | Raffay lead, all | T9 | ⬜ | |
| T12c | Demo instructions or link | Hadeed | T9 | ⬜ | |
| T12d | Code comment pass | All (own code) | T9 | ⬜ | |
| T12e | **Technical report**, 5–6 pages | All (own sections), Raffay edits | everything | ⬜ | |
| T12f | Final zip and acknowledgements check | Raffay | T12a–e | ⬜ | |
