#include "graph.h"

int main () {
    Graph::generate_grid(20, 15, 2077, "data/generated_grid.txt");
    Graph g("data/generated_grid.txt");

    g.draw();

    // g.global_index_of(1,)

    return 0;
}