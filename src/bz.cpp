// B0: sequential k-core decomposition by Batagelj and Zaversnik,
// "An O(m) Algorithm for Cores Decomposition of Networks" (2003).
// This is the reference every parallel variant must match exactly, and the
// T_serial in every speedup we report.
//
// Peeling repeatedly removes a vertex of minimum current degree. BZ keeps
// all vertices in one array sorted by current degree, so the minimum is
// always the next unprocessed entry, and a degree decrement moves a vertex
// one block down with a single swap. Total work is O(n + m).

#include "graph.h"

#include <algorithm>

std::vector<int> bz(const G& g) {
    const int n = g.n;

    // deg[v]: current degree of v; once v is processed it is v's core number.
    // vert:   vertices sorted by current degree. Vertices of degree d form one
    //         contiguous block, which plays the role of bucket d.
    // pos[v]: index of v in vert, so v can be found in O(1).
    // bin[d]: index in vert where block d starts.
    std::vector<int> deg(n), vert(n), pos(n);
    int md = 0;                                  // maximum degree
    for (int v = 0; v < n; v++) {
        deg[v] = g.deg(v);
        md = std::max(md, deg[v]);
    }

    // Counting sort by degree: count each degree, turn counts into block
    // starts, then place every vertex in its block.
    std::vector<int> bin(md + 1, 0);
    for (int v = 0; v < n; v++) bin[deg[v]]++;
    int start = 0;
    for (int d = 0; d <= md; d++) {
        int count = bin[d];
        bin[d] = start;
        start += count;
    }
    for (int v = 0; v < n; v++) {
        pos[v] = bin[deg[v]];
        vert[pos[v]] = v;
        bin[deg[v]]++;                           // next free slot in v's block
    }
    // Placing advanced each bin[d] to the start of block d+1; shift back.
    for (int d = md; d > 0; d--) bin[d] = bin[d - 1];
    bin[0] = 0;

    // Peel in order. vert[i] always has the minimum current degree among the
    // unprocessed vertices, so its degree right now is its core number.
    for (int i = 0; i < n; i++) {
        int v = vert[i];
        for (long long j = g.off[v]; j < g.off[v + 1]; j++) {
            int u = g.adj[j];
            // Only neighbours with a higher degree lose one. This single test
            // also skips neighbours that are already processed (their degree
            // is <= deg[v]) and keeps same-level neighbours from dropping
            // below the current level: the sequential form of the clamp
            // max(D - c, k) used by the parallel variants.
            if (deg[u] > deg[v]) {
                // Move u from block du to block du-1 in O(1): swap u with the
                // first vertex w of its block, then move the block start one
                // place right, so u becomes the last vertex of block du-1.
                int du = deg[u], pu = pos[u];
                int pw = bin[du], w = vert[pw];
                if (u != w) {
                    vert[pu] = w;
                    pos[w] = pu;
                    vert[pw] = u;
                    pos[u] = pw;
                }
                bin[du]++;
                deg[u]--;
            }
        }
    }
    return deg;
}
