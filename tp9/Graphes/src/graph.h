#ifndef _GRAPH
#define _GRAPH

#include "element.h"
#include <cassert>
#include <fstream>
#include <string>
#include <iostream>
#include <cmath>
#include <queue>
#include <utility>

struct Point {
    unsigned int x, y;
    unsigned int indx;
};

class Graph;

class Node {
    friend class Graph;

    private:
        Elem info;

    public:
        Node();

        Elem get_info() const;
        void set_info(const Elem& element);
};

class Graph {
    private:
        unsigned int nb_lines, nb_columns; // dimensions du terrain
        unsigned int nb_nodes; // taille totale du terrain
        Elem min, max; // hauteurs min et max
        Node* grid; // tableau des hauteurs

        // Varibales utiles pour l'algorithme de Dijkstra.
        // Sont initialisees dans les constructeurs.
        unsigned int* path_clrs; // couleurs (0: blanc, 1: gris, 2: noir)
        float* path_dist; // initialisee a l'infinite
        int* path_prev; // initialisee a -1

    public:
        // =========== Constructeurs ===========
        // Preconditions: * nb_l et nb_c : dimensions du terrain (PAS les indices de tableau)
        // Postcondition: Initialise un terrain plat
        //                (cad la hauteur des sommets est a 0) de taile 'nb_l*nb_c'
        Graph(unsigned int nb_l, unsigned int nb_c);

        // Postcondition: Initialise un terrain en prenant les valeurs contenues dans
        //                le fichier 'file'
        Graph(const std::string& file);

        // Destructeur
        ~Graph();

        // =========== Fonctions Membres ===========
        // Preconditions: * nb_l et nb_c : dimensions du terrain (PAS les indices de tableau)
        //                  doivent etre dans l'intervalle [nb_lines; nb_columns]
        // Resultat: l'indice globale dans le tableau 'grid' en fonction de
        //				  * neihbour: "north" -> voisin nord
        //                            "east" -> voisin est
        //                            "south" -> voisin sud
        //                            "west" -> voisin ouest
        //                            tout autre valeur -> case (nb_l, nb_c)
        unsigned int global_index_of(unsigned int nb_l, unsigned int nb_c, const std::string& neighbour="") const;

        // Preconditions: * nb_l et nb_c : dimensions du terrain (PAS les indices de tableau)
        //                  doivent etre dans l'intervalle [nb_lines; nb_columns]
        // Resultat: La hauteur du sommet dont les coordonnees sont (nb_l, nb_c)
        Elem get_info_at(unsigned int nb_l, unsigned int nb_c) const;

        // Preconditions: * nb_l et nb_c : dimensions du terrain (PAS les indices de tableau)
        //                  doivent etre dans l'intervalle [nb_lines; nb_columns]
        // Postcondition: La hauteur du sommet dont les coordonnees sont (nb_l, nb_c)
        //                est mise a jour avec la valeur 'value'
        void set_info_at(unsigned int nb_l, unsigned int nb_c, const Elem& value);

        // Preconditions: * nb_l et nb_c : dimensions du terrain (PAS les indices de tableau)
        //                  doivent etre dans l'intervalle [nb_lines; nb_columns]
        // Resultat: * True si la case (nb_l, nb_c) possede un voisin au nord
        //           * False sinon
        bool has_north_neighbour (unsigned int nb_l, unsigned int nb_c) const;

        // Preconditions: * nb_l et nb_c : dimensions du terrain (PAS les indices de tableau)
        //                  doivent etre dans l'intervalle [nb_lines; nb_columns]
        // Resultat: * True si la case (nb_l, nb_c) possede un voisin a l'est
        //           * False sinon
        bool has_east_neighbour (unsigned int nb_l, unsigned int nb_c) const;

        // Preconditions: * nb_l et nb_c : dimensions du terrain (PAS les indices de tableau)
        //                  doivent etre dans l'intervalle [nb_lines; nb_columns]
        // Resultat: * True si la case (nb_l, nb_c) possede un voisin au sud
        //           * False sinon
        bool has_south_neighbour (unsigned int nb_l, unsigned int nb_c) const;

        // Preconditions: * nb_l et nb_c : dimensions du terrain (PAS les indices de tableau)
        //                  doivent etre dans l'intervalle [nb_lines; nb_columns]
        // Resultat: * True si la case (nb_l, nb_c) possede un voisin a l'ouest
        //           * False sinon
        bool has_west_neighbour (unsigned int nb_l, unsigned int nb_c) const;

        // Preconditions: * nb_l et nb_c : dimensions du terrain (PAS les indices de tableau)
        //                  doivent etre dans l'intervalle [nb_lines; nb_columns]
        // Resultat: nombre des voisins
        unsigned int nb_neighbours (unsigned int nb_l, unsigned int nb_c) const;

        // Preconditions: * x et y : dimensions du terrain (PAS les indices de tableau)
        //                * max_height >= 0
        // Resultat: genere un terrain et sauvegarde les donnees dans le fichier 'target'
        static void generate_grid(unsigned int x, unsigned int y, unsigned int max_height, const std::string& target);

        // Postcondition: Le terrain est affiche en couleur dans le terminal.
        //                Affiche aussi les couleurs pour differents niveaux d'altitude.
        void draw() const;

        // Preconditions: * glbl_indx1 et glbl_indx2 doivent etre entre 0 et 'nb_nodes'
        // Resultat: La valuation de l'arete (glbl_indx1 - glbl_indx2)
        float get_way_cost (unsigned int glbl_indx1, unsigned int glbl_indx2) const;

        // Preconditions: * l et c : representent la source.
        //                  Doivent etre dans l'intervalle [nb_lines; nb_columns]
        // Postconditions: Remplit les tableaux membres prefixes par path_*
        void dijkstraa (Point* libs, unsigned int nb_libs, bool track=false);
};

#endif