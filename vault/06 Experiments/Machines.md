# Machines

| Owner | CPU | Cores / threads | RAM | OS | Compiler | Max threads in runs |
|---|---|---|---|---|---|---|
| Raffay | AMD Ryzen 5 5625U | 6 / 12 | ~7.3 GB | fill in | gcc 11.2.0 | 12 |
| Ibrahim | Intel i5-8350U | 4 / 8 | 16 GB | Win 10 + WSL2 Ubuntu 24.04 | gcc 13.3 | 8 |
| Hadeed | Intel i5-13420H (4P + 4E) | 8 / 12 | 16 GB | Win 11 + WSL2 Ubuntu 24.04 | gcc 13.3 | 12 |

## Notes
- Machine names in the CSV: `raffay`, `ibrahim`, `hadeed`.
- Three different chips (AMD; old Intel; Intel hybrid with P and E cores) is useful for the report: does C1 help on all of them?
- Hadeed's i5-13420H has performance and efficiency cores. Scaling past 8 threads may flatten because E-cores are slower; mention this if it shows up.
- WSL2: give it enough memory in `.wslconfig` for com-Orkut (e.g. `memory=12GB`).
- Raffay: please fill in your OS and confirm you build under Linux or WSL.
