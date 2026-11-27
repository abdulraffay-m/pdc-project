# Workflow

## Git (full rules in `CLAUDE.md` at the repo root)
We use **GitHub flow**: `main` always builds and passes tests; all work is on short-lived branches; everything reaches `main` through a PR.

- **Nobody commits or pushes to `main` directly.**
- One branch per task: `<name>/T<n>-<topic>`, e.g. `raffay/T1-loader`, `hadeed/T5-c1`. Branch from an up-to-date `main`, and rebase on `main` before opening the PR.
- Commit messages: `T<n>: <what, imperative>` plus a body saying **why**. Non-task work: `docs:`, `vault:`, `build:`, `test:`, `fix:`. No `update`, `fix`, `wip`.
- PRs use the template in `.github/pull_request_template.md`. Title in the same format as commits.
- Before merging, what has to pass depends on what the PR touches:
  - **Every PR:** `make` builds; `make test` passes once tests exist (from T1 on).
  - **Code that computes core numbers** (variants, `bkt`, `split.h`, `opts.h`): also output equals B0 on all test graphs at 1, 2, 4, 8 threads.
  - **B0 or the checks:** also matches the hand-computed expected values and `is_core()`.
  - **Vault, docs or scripts only:** no tests, but the build must not break.
- A variant that doesn't match B0 yet stays on its branch until it does.
- Code has comments.
- The author merges their own PR once tests pass. No approval needed.
- Merge with **squash and merge**, then delete the branch.
- Small PRs merge faster: one task, or part of one, per PR.
- Never commit graphs, binaries, large result files, secrets or copied external code.

### Recommended GitHub settings (repo owner: Raffay)
Settings → Branches → add a rule for `main`: require a pull request before merging (0 approvals), block force pushes. Settings → General: allow only squash merging, and turn on "automatically delete head branches".

## Communication
- **Sync every two days**, 15 minutes: what I finished, what's next, what's blocking me. Raffay writes the notes in `07 Meetings/` using `Templates/Meeting.md`.
- Blocked for more than half a day? Say so in the group chat right away.
- Any interface change: tell the group, update [[Interfaces]] and add a row to [[Decision Log]] **before** merging.

## The vault
- Edit it in Obsidian: open the `vault/` folder as a vault.
- Update [[Task Board]] when you start and finish a task.
- Log every benchmark you run in [[Results Log]].
- Record anything taken from outside (code, datasets, AI help) in [[Acknowledgements]] when it happens, not at the end.

## Using Claude (or another AI)
- Point it at `CLAUDE.md` in the repo root first.
- You must understand and be able to explain anything you merge. The viva grades your understanding.
- Note substantial AI help in [[Acknowledgements]].
