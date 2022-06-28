#include "graph.h"

int main () {
    Graph::generate_grid(10, 15, 29, "data/generated_grid.txt");
    Graph g("data/generated_grid.txt");

    g.draw();

    unsigned int nb_libs = 3;
    Point p1;
    p1.x = 5; p1.y = 2;
    Point p2;
    p2.x = 7; p2.y = 13;
    Point p3;
    p3.x = 8; p3.y = 7;
    Point libs[3] = {p1, p2, p3};

    // True - Pour afficher les etapes de l'algorithme
    // False - Ne pas afficher (Par Defaut)
    g.dijkstraa(libs, nb_libs);

    return 0;
}