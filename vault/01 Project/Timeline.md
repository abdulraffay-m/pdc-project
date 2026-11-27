# Timeline

**Milestone 3 deadline:** ________ (fill in)
**Viva:** dead week, ________ (fill in)
**Tier 1 freeze:** ________ (set it to deadline minus 7 days; the proposal's 30 Nov date is no longer realistic)

Phases are counted from the kickoff (27 Nov). Once the deadline is known, replace the day numbers with dates.

| Phase | Days | What's finished at the end | Gate |
|---|---|---|---|
| 1. Foundation | 1–3 | Loader, B0, validator, tests (T1); bucket interface published (T2a); driver skeleton (T7a) | `make test` passes on all 3 machines |
| 2. Variants | 4–9 | Bucket structure (T2), B1 (T3), B2 (T4), C1 (T5), S hooks (T6), datasets (T8) | Every variant equals B0 on all tests at 1–8 threads |
| 3. Experiments | 10–13 | Full benchmark on all 3 machines (T9), plots, GBBS reference run (T10, optional) | CSVs in `results/`, plots in `results/plots/` |
| **Tier 1 freeze** | | No new features after this, only fixes | |
| 4. Stretch | if time | C2 (T11) | Equals B0 |
| 5. Deliverables | last 5 days | README, slides, demo, **report last** (T12) | [[Deliverables Checklist]] all ticked |
| 6. Viva prep | final 2 days | Everyone explains every part out loud | Mock viva with questions in each person page |

## Checkpoints
A short sync every two days (see [[Workflow]]). Notes go in `07 Meetings/`.
