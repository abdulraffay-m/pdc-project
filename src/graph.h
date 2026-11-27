// Graph type and the sequential building blocks every variant relies on:
// loading, the B0 reference algorithm and the correctness checks.
// Signatures are fixed by vault/03 Design/Interfaces.md.

#pragma once

#include <string>
#include <utility>
#include <vector>

// Undirected graph in CSR (Compressed Sparse Row) form.
// The neighbours of v are adj[off[v]] .. adj[off[v+1]-1], sorted ascending.
// Every undirected edge {u, v} is stored twice (u->v and v->u), so a vertex
// can read all its neighbours from one contiguous range. That is what makes
// the parallel edge loops and the edge decomposition (S study) cheap.
// There are no self-loops and no duplicate edges.
struct G {
    int n;                          // vertices, ids 0..n-1
    long long m;                    // undirected edges
    std::vector<long long> off;     // size n+1; long long because 2m can exceed 2^31
    std::vector<int> adj;           // size 2m, both directions
    int deg(int v) const { return off[v+1] - off[v]; }
};

// io.cpp
G load(const std::string& path);                                   // SNAP edge list: '#' comments, "u v" per line
G from_edges(int n, const std::vector<std::pair<int,int>>& e);   // for tests

// bz.cpp: B0, the sequential reference. Returns core[v] for every v.
std::vector<int> bz(const G& g);

// check.cpp
bool same(const std::vector<int>& a, const std::vector<int>& b);   // prints first mismatch
bool is_core(const G& g, const std::vector<int>& c);              // independent property check
