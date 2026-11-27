# Roles and Ownership

Agreed on 2026-11-27 ([[Decision Log]]). "Owner" means you write it, test it and explain it in the viva. Everyone still understands the rest.

| | [[Raffay]] | [[Ibrahim]] (lead) | [[Hadeed]] |
|---|---|---|---|
| **Builds** | CSR loader, B0, validator, test graphs, datasets and R-MAT generator, **B2** | `opts.h`, bucket structure, **B1**, **S** hooks (`split.h`), integration, **C2** (stretch) | **C1**, driver (`main.cpp`), `run.sh`, `plot.py`, demo |
| **Viva story** | "How we know every result is correct, and the #36 baseline" | "The paper's method and the scheduling study" | "Our main contribution and the results" |
| **Machine** | Ryzen 5 5625U, 6C/12T, 7.3 GB | i5-8350U, 4C/8T, 16 GB | i5-13420H, 8C/12T, 16 GB |
| **Benchmark runs** | All graphs except com-Orkut, 1–12 threads | All graphs incl. com-Orkut, 1–8 threads | All graphs incl. com-Orkut, 1–12 threads |
| **Deliverables** | README | Slides lead, report editor | Demo, results figures |

## Lead duties (Ibrahim)
- Keep [[Task Board]] and [[Timeline]] current.
- Run the sync every two days and write the notes.
- Final edit of the report and slides.

## Shared
- Benchmark runs on your own machine (T9).
- Your own report sections, written last.
- Your own entries in [[Acknowledgements]], including AI use.
