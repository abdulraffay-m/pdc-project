## Task
T__: <link to the row in vault/05 Tasks/Task Board.md>

## What
<!-- What this PR adds or changes, in a few lines. -->

## Why
<!-- The reason or the approach. Paper section if it comes from one. -->

## How it was tested
- [ ] `make` builds; `make test` passes (once tests exist)
- [ ] If it computes core numbers: output equals B0 on all test graphs at 1, 2, 4, 8 threads
- [ ] If it changes B0 or the checks: matches hand-computed values and `is_core()`
- [ ] Vault / docs / scripts only: build still passes
- [ ] Machine(s) tested on:

## Checklist
- [ ] Follows `vault/03 Design/Interfaces.md` (or the Decision Log has a row for the change)
- [ ] Code has comments explaining why
- [ ] No data races: shared writes are atomic, private or after a barrier
- [ ] No external code copied; any outside help is in `vault/08 Deliverables/Acknowledgements.md`
- [ ] Branch is rebased on the latest `main`

## Notes for the group
<!-- Anything tricky, open questions, or things you're unsure about. -->
