#include "graph.h"

Color::Color () : r(255), g(255), b(255) {}
Color::Color (unsigned char r, unsigned char g, unsigned char b) : r(r), g(g), b(b) {}

Node::Node () {}

Elem Node::get_info() const { return info; }

void Node::set_info(const Elem& element) { info = element; }

void Graph::generate_grid (unsigned int x, unsigned int y, unsigned int max_height, const std::string& target) {
    srand(time(NULL));
    
    std::ofstream file(target);
    if (file.is_open()) {
        file << x << " " << y << "\n";
        for (unsigned int i=0; i<x; ++i) {
            for (unsigned int j=0; j<y; ++j) {
                file << ((rand()%max_height)+1) << " ";
            }
            file << "\n";
        }
    }
    else std::cout << "ERROR : Cannot open 'data/generated_grid.txt' file !\n";
    file.close();
}

Graph::Graph (unsigned int nb_l, unsigned int nb_c) {
    nb_lines = nb_l;
    nb_columns = nb_c;
    nb_nodes = nb_l*nb_c;
    min = max = 0;
    grid = new Node[nb_nodes];
}

Graph::Graph(const std::string& file) {
    std::ifstream f(file);
    if (f.is_open()) {
        f >> nb_lines >> nb_columns;
        // std::cout << "nb_lines : " << nb_lines << "\n";
        // std::cout << "nb_columns : " << nb_columns << "\n";
        nb_nodes = nb_lines*nb_columns;
        grid = new Node[nb_nodes];
        for (unsigned int i=1; i<=nb_lines; ++i) {
            for (unsigned int j=1; j<=nb_columns; ++j) {
                unsigned int global_index = global_index_of(i,j);
                f >> grid[global_index].info;

                if (i==1 && j==1) min=max=grid[global_index].info;
                else {
                    if (grid[global_index].info < min) min = grid[global_index].info;
                    if (grid[global_index].info > max) max = grid[global_index].info;
                }
                // std::cout << "(" << i << ", " << j << ") : " << grid[global_index_of(i,j)] << "\n";
            }
        }
    }
    else std::cout << "ERROR : Cannot open " << file << " file !\n";
    f.close();
}

Graph::~Graph () {
    delete [] grid;
}

unsigned int Graph::global_index_of(unsigned int nb_l, unsigned int nb_c, const std::string& neighbour) const {
    assert(0 <= nb_l && nb_l <= nb_lines && 0 <= nb_c && nb_c <= nb_columns);
    if (neighbour == "north") return (nb_l-2)*nb_columns + (nb_c-1);
    if (neighbour == "east") return (nb_l-1)*nb_columns + (nb_c);
    if (neighbour == "south") return (nb_l)*nb_columns + (nb_c-1);
    if (neighbour == "west") return (nb_l-1)*nb_columns + (nb_c-2);
    return (nb_l-1)*nb_columns + (nb_c-1);
}

Elem Graph::get_info_at(unsigned int nb_l, unsigned int nb_c) const {
    assert(0 <= nb_l && nb_l <= nb_lines && 0 <= nb_c && nb_c <= nb_columns);
    return grid[global_index_of(nb_l, nb_c)].info;
}

void Graph::set_info_at(unsigned int nb_l, unsigned int nb_c, const Elem& value) {
    assert(0 <= nb_l && nb_l <= nb_lines && 0 <= nb_c && nb_c <= nb_columns);
    grid[global_index_of(nb_l, nb_c)].info = value;
}

unsigned int Graph::nb_neighbours (unsigned int nb_l, unsigned int nb_c) const {
    assert(0 <= nb_l && nb_l <= nb_lines && 0 <= nb_c && nb_c <= nb_columns);

    if ((nb_l == 0 && (nb_c == 0 || nb_c == nb_columns)) ||
        (nb_l == nb_lines && (nb_c == 0 || nb_c == nb_columns))) {
            return 2;
    }
    else if (0 < nb_l && nb_l < nb_lines && 0 < nb_c && nb_c < nb_columns) {
        return 4;
    }
    else return 3;
}

void Graph::draw () const {
    // Codes ANSI
    // Premiere couleur = min, interpolation pour les 8 hauteurs intermediaires, la derniere couleur = max
    unsigned char col_codes[] = {28, 64, 100, 136, 172, 208, 202, 196, 160, 124};
    int height_levels[10];

    // On remplit le tableau 'height_levels' avec les hauteurs intermediaires
    unsigned int temp = max / 8;
    unsigned int iterator = temp;

    height_levels[0] = min;
    for(unsigned int i=1; i<9; ++i) {
        height_levels[i] = temp;
        temp += iterator;
    }
    height_levels[9] = max;
    std::cout << "\n";

    // Nombres de chiffres de 'max', pour que la grille soit bien alignee
    std::string max_string = std::to_string(max);
    unsigned int max_digits = max_string.length();

    // On affiche le coloriage pour les differents hauteurs
    std::cout << "Colors for different Height Levels:\n";
    std::cout << "(Left value is the LOWEST Height and Right one is the HIGHEST)\n";
    for(unsigned int i=0; i<10; ++i) {
        printf( "\033[48;5;%dm", col_codes[i]);
        std::cout << height_levels[i];

        max_string = std::to_string(height_levels[i]);
        unsigned int nb_digits = max_string.length();

        while (nb_digits <= max_digits) {
            std::cout << " ";
            ++nb_digits;
        }

        std::cout << "\033[0m" << ((i==9) ? "\n\n" : "");
    }

    // On affiche la grille du terrain
    std::cout << "Terrain:\n";
    for (unsigned int i=0; i<=nb_lines; ++i) {
        if (i == 0) {
            for(unsigned int q=0; q<=max_digits; ++q) std::cout << " ";
        }
        else {
            max_string = std::to_string(i);
            unsigned int nb_digits = max_string.length();
            
            std::cout << i;
            while (nb_digits <= max_digits) {
                std::cout << " ";
                ++nb_digits;
            }
        }
        
        for (unsigned int j=1; j<=nb_columns; ++j) {
            if (i == 0) {
                max_string = std::to_string(j);
                unsigned int nb_digits = max_string.length();
                
                std::cout << j;
                while (nb_digits <= max_digits) {
                    std::cout << " ";
                    ++nb_digits;
                }
            }
            else {
                unsigned int global_index = global_index_of(i,j);

                Elem copy_of_info = grid[global_index].info;
                unsigned int clr_indx = 1;
                while (copy_of_info >= height_levels[clr_indx]) {
                    ++clr_indx;
                }
                if (copy_of_info == min) clr_indx = 0;
                if (copy_of_info == max) clr_indx = 9;

                max_string = std::to_string(grid[global_index].info);
                unsigned int nb_digits = max_string.length();

                printf( "\033[48;5;%dm", col_codes[clr_indx]);
                std::cout << grid[global_index].info;
                while (nb_digits <= max_digits) {
                    std::cout << " ";
                    ++nb_digits;
                }

                std::cout << "\033[0m";
            }
        }
        std::cout << std::endl;
    }
}

float Graph::get_way_cost (unsigned int l1, unsigned int c1, unsigned int l2, unsigned int c2) const {
    return sqrt(1 + pow(grid[global_index_of(l1,c1)].info - grid[global_index_of(l2,c2)].info, 2));
}

