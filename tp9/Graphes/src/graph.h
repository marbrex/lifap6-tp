#ifndef _GRAPH
#define _GRAPH

#include "element.h"
#include <cassert>
#include <fstream>
#include <string>
#include <iostream>
#include <cmath>

class Graph;

struct Color {
    unsigned char r;
    unsigned char g;
    unsigned char b;

    Color();
    Color(unsigned char r, unsigned char g, unsigned char b);
};

class Node {
    friend class Graph;

    private:
        Elem info;
        Color color;

    public:
        Node();

        Elem get_info() const;
        void set_info(const Elem& element);
};

class Graph {
    private:
        unsigned int nb_lines, nb_columns;
        unsigned int nb_nodes;
        Elem min, max;
        Node* grid;

    public:
        // initialise un terrain vide (cad sommets sont pas definies) de taile nb_l*nb_c
        Graph(unsigned int nb_l, unsigned int nb_c);

        // initialise un terrain en prenant les valeurs contenues dans
        // le fichier 'file'
        Graph(const std::string& file);
        ~Graph();

        // unsigned int global_index_of(unsigned int nb_l, unsigned int nb_c) const;
        unsigned int global_index_of(unsigned int nb_l, unsigned int nb_c, const std::string& neighbour="") const;

        Elem get_info_at(unsigned int nb_l, unsigned int nb_c) const;
        void set_info_at(unsigned int nb_l, unsigned int nb_c, const Elem& value);

        unsigned int nb_neighbours (unsigned int nb_l, unsigned int nb_c) const;

        static void generate_grid(unsigned int x, unsigned int y, unsigned int max_height, const std::string& target);

        void draw() const;

        float get_way_cost (unsigned int l1, unsigned int c1, unsigned int l2, unsigned int c2) const;
};

#endif