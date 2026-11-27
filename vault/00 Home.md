# PDC Project Hub: Race Condition

CS-3006 Parallel and Distributed Computing, Fall 2026, BCS-7D.
Group **Race Condition**: Abdul Raffay Moazzam (23i-0587, lead), Ibrahim Azad (23i-3049), Muhammad Hadeed (23i-0764).
Paper **#20: Julienne** (Dhulipala, Blelloch, Shun, SPAA 2017), scoped to **parallel k-core peeling**.

## Start here
If you're new to the project, read these in order. It takes about 30 minutes.
1. [[Overview]]: what we're building and why
2. [[k-core and Peeling]]: the background you need
3. [[Variants]]: B0, B1, B2, C1, S and C2 in one table
4. [[Roles]]: who owns what
5. Your own page: [[Raffay]], [[Ibrahim]] or [[Hadeed]]
6. [[Task Board]]: what to do next

## Where things are
| Folder | What's inside |
|---|---|
| `01 Project` | [[Overview]], [[Milestone 3 Requirements]], [[Defence Feedback]], [[Timeline]], [[Decision Log]] |
| `02 Background` | [[k-core and Peeling]], [[Paper 20 - Julienne]], [[Paper 36 - Liu et al 2025]], [[Glossary]] |
| `03 Design` | [[Variants]], [[Interfaces]], [[Correctness]], [[C1 Hybrid Update]], [[S Scheduling Study]], [[B2 Sampling Baseline]], [[C2 Local Queues]] |
| `04 Team` | [[Roles]], [[Workflow]], per-person pages |
| `05 Tasks` | [[Task Board]] |
| `06 Experiments` | [[Experiment Plan]], [[Datasets]], [[Machines]], [[Results Log]] |
| `07 Meetings` | Meeting notes, one file per meeting |
| `08 Deliverables` | [[Deliverables Checklist]], [[Acknowledgements]], [[Report Outline]] |
| `09 Sources` | Papers, proposal, slides and course documents ([[Sources Index]]) |
| `Templates` | Meeting and result templates |

## Rules that matter most
- Every variant must give **exactly** the same core numbers as B0. See [[Correctness]].
- Code is OpenMP and C++17. No MPI, Ligra or GBBS code in `src/`. See [[Decision Log]].
- Submitted code must have **proper comments**, because Milestone 3 grades it.
- Nothing goes to `main` except through a pull request with passing tests. See [[Workflow]].
- Everyone must be able to explain their own code in the viva, and roughly understand everyone else's.

## For Claude (or any AI assistant)
Read `CLAUDE.md` at the repo root first, then this page, then [[Interfaces]] and the page of the person you're helping.
