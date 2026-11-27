# Instructions for Claude (and other AI assistants)

This repo is the CS-3006 PDC semester project of group **Race Condition** (Raffay, Ibrahim, Hadeed): parallel k-core decomposition based on the Julienne paper (SPAA 2017), with our own contribution C1 (degree-aware hybrid hub update) and S (scheduling study).

## Read before doing anything
1. `vault/00 Home.md`
2. `vault/03 Design/Interfaces.md`: the code contract
3. `vault/03 Design/Correctness.md`
4. The page of the person you're helping in `vault/04 Team/`
5. `vault/05 Tasks/Task Board.md`

## Hard rules
- C++17 + OpenMP only. No MPI. No code copied from GBBS (`external/gbbs`) or paper #36's code; read them only.
- Don't change any signature in `Interfaces.md` without the person confirming it's been agreed with the group. If it changes, update `Interfaces.md` and add a row to `vault/01 Project/Decision Log.md`.
- Every parallel variant must produce exactly B0's core numbers. Run `make test` before saying anything works.
- Submitted code needs proper comments (Milestone 3 grades this).
- Parallel edge loops go through `for_edges` in `src/split.h`, so the scheduling study covers every variant.
- Credit ideas: B2 and C2 come from paper #36; B1 from Julienne. Don't describe them as ours.

## Git rules
We use GitHub flow: `main` always builds and passes tests, all work happens on short-lived branches, and everything reaches `main` through a pull request.

### Branches
- Never commit or push to `main` directly. Never force-push `main`.
- One branch per task: `<name>/T<n>-<topic>`, e.g. `raffay/T1-loader`, `hadeed/T5-c1`, `ibrahim/T2-buckets`. Lowercase, hyphens, no spaces.
- Branch from an up-to-date `main` (`git switch main && git pull && git switch -c ...`).
- Keep branches short-lived (a few days at most). Before opening a PR, bring in the latest `main` with `git pull --rebase origin main` and fix any conflicts yourself.
- Only push to your own branches. Don't push to a teammate's branch unless they ask.
- Delete the branch after it's merged.

### Commits
- Commit small, working steps. Each commit should build.
- Message format:
  ```
  T<n>: <what changed, imperative, max ~60 chars>

  <why: the reason, the approach, anything a teammate should know.
  Wrap at ~72 chars. Mention test results if relevant.>
  ```
  Good: `T2: skip stale bucket entries when opening a bucket`
  Bad: `update`, `fix`, `changes`, `wip`, `final final`.
- Non-task work uses a type instead of a task id: `docs:`, `vault:`, `build:`, `test:`, `fix:` (e.g. `vault: record defence feedback`).
- Write the body for anything non-trivial. "Why" matters more than "what"; the diff already shows what.
- Don't amend or rebase commits that are already pushed and shared, except on your own unmerged branch.
- When Claude wrote or substantially helped with a commit, add the trailer `Co-Authored-By: Claude <noreply@anthropic.com>`. The course requires AI use to be acknowledged.

### Pull requests
- Open a PR for every branch and fill in the template in `.github/pull_request_template.md`: what, why, how it was tested, which task, anything to watch.
- PR title follows the commit format: `T3: B1 Julienne-style parallel peeling`.
- Before opening: the checks in the table below pass, and code is commented.
- The author merges their own PR once the checks above pass. No approval is required.
- Merge with **squash and merge**, so `main` gets one clean commit per PR with the PR title as its message.
- If a teammate leaves a comment on a PR, answer it before merging.
- Link the PR in `vault/05 Tasks/Task Board.md` and set the task to ✅ when merged.

### What has to pass before merging
| PR touches | Required |
|---|---|
| Anything (every PR) | `make` builds with no errors; `make test` passes once tests exist (from T1 on) |
| Code that computes core numbers: variants, `bkt`, `split.h`, `opts.h` | Also: output equals B0 on all test graphs at 1, 2, 4, 8 threads |
| B0 (`bz.cpp`) or the checks | Also: matches the hand-computed expected values and `is_core()` (B0 is the reference, so it isn't compared with itself) |
| Vault, docs or scripts only | No tests needed, but the build must not break |

A variant that doesn't match B0 yet stays on its branch until it does.

### Never commit
- Graphs or datasets (`data/` is git-ignored), binaries (`bin/`), large result dumps (`results/raw/`).
- Secrets, tokens or personal config (`.env`, `.vscode/`, Obsidian `workspace.json`).
- Code copied from GBBS or other external code into `src/`.

## Code style
- Follow the file layout and names in `Interfaces.md`.
- Comments explain *why* (the idea, the race being avoided, the paper section it comes from), not just what each line does.
- Every shared write in a parallel region must be one of: atomic, thread-private, or after a barrier. Say which in a comment.
- No new dependencies beyond the C++ standard library, OpenMP and Python matplotlib without group agreement.
- Fixed seeds for anything random, so failures reproduce.

## Before saying a task is done
1. The checks in "What has to pass before merging" pass for this kind of change.
2. For code that computes core numbers: output matches B0 on all test graphs at several thread counts.
3. The task board, results log and acknowledgements are updated.
4. The person you're helping can explain the change.

If you're unsure about a design choice that affects other people's code, stop and ask the person to check with the group instead of guessing.

## The person must understand the code
The viva grades each member's understanding. Explain what you write, keep it simple enough to defend, and don't produce large amounts of code they haven't followed.

## Keep the vault current
When you finish work: update the task's status in `Task Board.md`, log results in `vault/06 Experiments/Results Log.md`, and record any outside source or substantial AI help in `vault/08 Deliverables/Acknowledgements.md`.
