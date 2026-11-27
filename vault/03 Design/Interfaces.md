# Interfaces (the contract)

Everyone codes against these signatures, so work can happen in parallel. **Don't change a signature without telling the group and adding a row to [[Decision Log]].**

## Build and stack
- C++17, g++ ≥ 9, OpenMP. Linux or WSL2.
- Flags: `-O3 -march=native -fopenmp`. Debug and tests: `-O1 -g -fsanitize=address,undefined` (no OpenMP sanitizer needed).
- One `Makefile` at the root: `make` builds `bin/kcore`; `make test` builds and runs `bin/tests`.

## Repo layout
```
src/
  graph.h      G struct                        (Raffay)
  io.cpp       load(), from_edges()            (Raffay)
  bz.cpp       B0                              (Raffay)
  check.cpp    same(), is_core()               (Raffay)
  opts.h       Opts, Stats, enums              (Ibrahim)
  bkt.h/.cpp   bucket structure                (Ibrahim)
  split.h      vertex/edge decomposition       (Ibrahim)
  julienne.cpp B1                              (Ibrahim)
  sample.cpp   B2                              (Raffay)
  hybrid.cpp   C1                              (Hadeed)
  lq.cpp       C2 (Tier 2)                     (Ibrahim)
  variants.h   declarations of all variants
  main.cpp     driver, CLI, CSV output         (Hadeed)
tests/          one test file per module
scripts/        get_data.sh, gen_rmat, run.sh, plot.py
data/           graphs (git-ignored)
results/        CSVs and plots
external/gbbs   git submodule, reading only
vault/          this vault
```

## Graph (`graph.h`, `io.cpp`)
```cpp
struct G {
    int n;
    long long m;                    // undirected edges
    std::vector<long long> off;     // size n+1
    std::vector<int> adj;           // size 2m, both directions
    int deg(int v) const { return off[v+1] - off[v]; }
};
G load(const std::string& path);                                   // SNAP edge list: '#' comments, "u v" per line
G from_edges(int n, const std::vector<std::pair<int,int>>& e);   // for tests
```
`load` symmetrises, removes self-loops and duplicate edges, and relabels ids to 0..n-1.

## Reference and checks (`bz.cpp`, `check.cpp`)
```cpp
std::vector<int> bz(const G& g);
bool same(const std::vector<int>& a, const std::vector<int>& b);   // prints first mismatch
bool is_core(const G& g, const std::vector<int>& c);              // independent property check
```

## Options and stats (`opts.h`)
```cpp
enum Sch { ST, DY, GU };            // static, dynamic, guided
enum Dec { VTX, EDG };              // split by vertex or by edge
struct Stats {
    int rounds = 0;                 // ρ
    long long atom = 0;             // atomic ops on degree counters (instrumented builds)
    double imb = 0;                 // mean over rounds of max/mean edges per thread
    double t_edge = 0, t_bkt = 0;   // time in edge loop vs re-bucketing
};
struct Opts {
    int t = 1;                      // threads
    Sch s = ST; int ch = 0;         // schedule and chunk (0 = default)
    Dec d = VTX;
    int nb = 128;                   // live bucket window
    int M = 2048;                   // histogram block size
    double th = 16;                 // hub threshold as a multiple of average degree (B2, C1)
    double r = 0.1, c = 3;          // B2: resample factor, μ = 4·c·ln n
    int q = 128;                    // C2 queue size
    unsigned seed = 1;              // B2 random seed
    Stats st;                       // filled by the variant
};
```
Schedules are applied with `omp_set_schedule()` and `schedule(runtime)` loops, so one binary covers all three.

## Bucket structure (`bkt.h`)
```cpp
class Bkt {
public:
    Bkt(int n, const std::vector<int>& D, int nb, int M);
    std::pair<int, std::vector<int>> next();                     // (k, live ids); k = -1 when empty
    void update(const std::vector<int>& ids, const std::vector<int>& D, int k);
};
```
- `next` skips stale entries (`D[v] != bucket` or already peeled).
- `update` reads each id's new (already clamped) degree from `D` and inserts it lock-free using block histograms and a prefix sum.

## Decomposition helper (`split.h`)
```cpp
template <class F> void for_edges(const G& g, const std::vector<int>& fr, const Opts& o, F f);
// calls f(u, v, tid) for every edge u→v with u in fr, using o.d and o.s
```
**B1, B2 and C1 must all use this**, so the S study applies equally to every variant.

## Variants (`variants.h`)
```cpp
std::vector<int> jul(const G& g, Opts& o);
std::vector<int> smp(const G& g, Opts& o);
std::vector<int> hyb(const G& g, Opts& o);
std::vector<int> lq (const G& g, Opts& o);
```
Each returns `core`, size n, and fills `o.st`. Timing is done by the driver, not inside the variant.

## Driver CLI (`main.cpp`)
```
bin/kcore -g data/web-Google.txt -a hyb -t 8 -s dynamic -d edge -th 16 -r 5
```
| Flag | Meaning | Default |
|---|---|---|
| `-g` | graph file | required |
| `-a` | `bz`, `jul`, `smp`, `hyb`, `lq` | `jul` |
| `-t` | threads | 1 |
| `-s` | `static`, `dynamic`, `guided` | `static` |
| `-d` | `vtx`, `edge` | `vtx` |
| `-nb`, `-M`, `-th`, `-q` | see Opts | |
| `-r` | repeats (median reported) | 5 |
| `-nocheck` | skip the B0 comparison | off |

Output: one CSV row on stdout:
`graph,n,m,machine,variant,threads,sched,dec,nb,th,rounds,atomics,imb,t_edge,t_bkt,median_s,valid`
