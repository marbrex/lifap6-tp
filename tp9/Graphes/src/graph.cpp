#include "graph.h"

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
    for (unsigned int i=0; i<nb_nodes; ++i) grid[i].info = 0;
    path_clrs = new unsigned int[nb_nodes];
    for (unsigned int i=0; i<nb_nodes; ++i) path_clrs[i] = 0;
    path_dist = new float[nb_nodes];
    for (unsigned int i=0; i<nb_nodes; ++i) path_dist[i] = (float)INTMAX_MAX;
    path_prev = new int[nb_nodes];
    for (unsigned int i=0; i<nb_nodes; ++i) path_prev[i] = -1;
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

    path_clrs = new unsigned int[nb_nodes];
    for (unsigned int i=0; i<nb_nodes; ++i) path_clrs[i] = 0;
    path_dist = new float[nb_nodes];
    for (unsigned int i=0; i<nb_nodes; ++i) path_dist[i] = (float)INTMAX_MAX;
    path_prev = new int[nb_nodes];
    for (unsigned int i=0; i<nb_nodes; ++i) path_prev[i] = -1;
}

Graph::~Graph () {
    delete [] grid;
    delete [] path_clrs;
    delete [] path_dist;
    delete [] path_prev;
}

bool Graph::has_north_neighbour (unsigned int nb_l, unsigned int nb_c) const {
    assert(1 <= nb_l && nb_l <= nb_lines && 1 <= nb_c && nb_c <= nb_columns);
    if (nb_l == 1) return false;
    return true;
}

bool Graph::has_east_neighbour (unsigned int nb_l, unsigned int nb_c) const {
    assert(1 <= nb_l && nb_l <= nb_lines && 1 <= nb_c && nb_c <= nb_columns);
    if (nb_c == nb_columns) return false;
    return true;
}

bool Graph::has_south_neighbour (unsigned int nb_l, unsigned int nb_c) const {
    assert(1 <= nb_l && nb_l <= nb_lines && 1 <= nb_c && nb_c <= nb_columns);
    if (nb_l == nb_lines) return false;
    return true;
}

bool Graph::has_west_neighbour (unsigned int nb_l, unsigned int nb_c) const {
    assert(1 <= nb_l && nb_l <= nb_lines && 1 <= nb_c && nb_c <= nb_columns);
    if (nb_c == 1) return false;
    return true;
}

unsigned int Graph::global_index_of(unsigned int nb_l, unsigned int nb_c, const std::string& neighbour) const {
    assert(1 <= nb_l && nb_l <= nb_lines && 1 <= nb_c && nb_c <= nb_columns);
    if (neighbour == "north" && has_north_neighbour(nb_l, nb_c)) return (nb_l-2)*nb_columns + (nb_c-1);
    if (neighbour == "east" && has_east_neighbour(nb_l, nb_c)) return (nb_l-1)*nb_columns + (nb_c);
    if (neighbour == "south" && has_south_neighbour(nb_l, nb_c)) return (nb_l)*nb_columns + (nb_c-1);
    if (neighbour == "west" && has_west_neighbour(nb_l, nb_c)) return (nb_l-1)*nb_columns + (nb_c-2);
    return (nb_l-1)*nb_columns + (nb_c-1);
}

Elem Graph::get_info_at(unsigned int nb_l, unsigned int nb_c) const {
    assert(1 <= nb_l && nb_l <= nb_lines && 1 <= nb_c && nb_c <= nb_columns);
    return grid[global_index_of(nb_l, nb_c)].info;
}

void Graph::set_info_at(unsigned int nb_l, unsigned int nb_c, const Elem& value) {
    assert(1 <= nb_l && nb_l <= nb_lines && 1 <= nb_c && nb_c <= nb_columns);
    grid[global_index_of(nb_l, nb_c)].info = value;
}

unsigned int Graph::nb_neighbours (unsigned int nb_l, unsigned int nb_c) const {
    assert(1 <= nb_l && nb_l <= nb_lines && 1 <= nb_c && nb_c <= nb_columns);

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
        // Si nombre max de chiffres dans la grille est < au
        // nombre des chiffres de 'nb_lines'
        max_string = std::to_string(nb_lines);
        unsigned int max_digits_line = max_string.length();
        if (max_digits_line > max_digits) max_digits = max_digits_line;

        // affiche un carre vide de taille 'max_digits'
        if (i == 0) for(unsigned int q=0; q<=max_digits; ++q) std::cout << " ";
        else { // affiche les indices de ligne
            max_string = std::to_string(i);
            unsigned int nb_digits = max_string.length();
            
            // affichage des espaces supplementaires pour bien aligner les cases de la grille
            std::cout << i;
            while (nb_digits <= max_digits) {
                std::cout << " ";
                ++nb_digits;
            }
        }
        
        for (unsigned int j=1; j<=nb_columns; ++j) {
            if (i == 0) { // affiche les indices de colonne
                max_string = std::to_string(j);
                unsigned int nb_digits = max_string.length();

                // Si nombre max de chiffres dans la grille est < au
                // nombre des chiffres de 'nb_columns'
                max_string = std::to_string(nb_columns);
                unsigned int max_digits_columns = max_string.length();
                if (max_digits_columns > max_digits) max_digits = max_digits_columns;
                
                // affichage des espaces supplementaires pour bien aligner les cases de la grille
                std::cout << j;
                while (nb_digits <= max_digits) {
                    std::cout << " ";
                    ++nb_digits;
                }
            }
            else { // On affiche la grille
                unsigned int global_index = global_index_of(i,j);

                // On cherche l'indice de couleur
                Elem copy_of_info = grid[global_index].info;
                unsigned int clr_indx = 1;
                while (copy_of_info > height_levels[clr_indx]) ++clr_indx;
                if (copy_of_info == min) clr_indx = 0;
                if (copy_of_info == max) clr_indx = 9;
                if (copy_of_info == min && copy_of_info == max) clr_indx = 0;

                // Calcul de nombre de chiffres pour bien aligner la grille
                max_string = std::to_string(grid[global_index].info);
                unsigned int nb_digits = max_string.length();

                // Set color
                printf( "\033[48;5;%dm", col_codes[clr_indx]);

                // affiche la case actuelle de la grille
                std::cout << grid[global_index].info;
                while (nb_digits <= max_digits) {
                    std::cout << " ";
                    ++nb_digits;
                }

                // Reset color
                std::cout << "\033[0m";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

float Graph::get_way_cost (unsigned int glbl_indx1, unsigned int glbl_indx2) const {
    assert(0 <= glbl_indx1 && glbl_indx1 < nb_nodes);
    assert(0 <= glbl_indx2 && glbl_indx2 < nb_nodes);

    return sqrt(1 + pow(grid[glbl_indx1].info - grid[glbl_indx2].info, 2));
}

void Graph::dijkstraa (Point* libs, unsigned int nb_libs, bool track) {
    for(unsigned int i=0; i<nb_libs; ++i) {
        assert(1 <= libs[i].x && libs[i].x <= nb_lines && 1 <= libs[i].y && libs[i].y <= nb_columns);
        libs[i].indx = global_index_of(libs[i].x, libs[i].y);
    }

    unsigned int min_indx;

    std::priority_queue<std::pair<float, unsigned int>,
                        std::vector<std::pair<float, unsigned int>>,
                        std::greater<std::pair<float, unsigned int>>> gray;

    for(unsigned int j=0; j<nb_libs; ++j) {
        for(unsigned int i=0; i<nb_nodes; ++i) {
            float dist = get_way_cost(libs[j].indx, i);
            path_dist[i] = dist;

            unsigned int north_indx;
            if (has_north_neighbour(libs[j].x, libs[j].y)) north_indx = global_index_of(libs[j].x, libs[j].y,"north");
            unsigned int east_indx;
            if (has_east_neighbour(libs[j].x, libs[j].y)) east_indx = global_index_of(libs[j].x, libs[j].y,"east");
            unsigned int south_indx;
            if (has_south_neighbour(libs[j].x, libs[j].y)) south_indx = global_index_of(libs[j].x, libs[j].y,"south");
            unsigned int west_indx;
            if (has_west_neighbour(libs[j].x, libs[j].y)) west_indx = global_index_of(libs[j].x, libs[j].y,"west");

            if (i == north_indx || i == east_indx || i == south_indx || i == west_indx) {
                path_prev[i] = libs[j].indx;
                path_clrs[i] = 1;
                gray.push(std::make_pair(path_dist[i],i));
            }
        }

        path_clrs[libs[j].indx] = 2;
        path_dist[libs[j].indx] = 0;
    }

    while (!gray.empty()) {
        min_indx = gray.top().second;
        gray.pop();

        for (unsigned int i=0; i<4; ++i) {
            unsigned int y = min_indx % nb_columns;
            unsigned int x = (min_indx - y) / nb_columns;
            ++x; ++y;

            unsigned int neighbour_indx;
            if (i == 0 && has_north_neighbour(x,y)) neighbour_indx = global_index_of(x,y,"north");
            if (i == 1 && has_east_neighbour(x,y)) neighbour_indx = global_index_of(x,y,"east");
            if (i == 2 && has_south_neighbour(x,y)) neighbour_indx = global_index_of(x,y,"south");
            if (i == 3 && has_west_neighbour(x,y)) neighbour_indx = global_index_of(x,y,"west");
            
            if (path_clrs[neighbour_indx] != 2) {
                if (path_clrs[neighbour_indx] == 0) {
                    path_clrs[neighbour_indx] = 1;
                    gray.push(std::make_pair(path_dist[neighbour_indx], neighbour_indx));
                }
                float distance = path_dist[min_indx] + get_way_cost(min_indx, neighbour_indx);
                if (distance < path_dist[neighbour_indx]) {
                    path_dist[neighbour_indx] = distance;
                    path_prev[neighbour_indx] = min_indx;
                }
            }
        }

        path_clrs[min_indx] = 2;

        if (track) {
            for (unsigned int i=1; i<=nb_lines; ++i) {
                for (unsigned int j=1; j<=nb_columns; ++j) {
                    switch (path_clrs[global_index_of(i,j)]) {
                        case 1:
                            printf( "\033[48;5;250m%d\033[0m", path_clrs[global_index_of(i,j)]);
                            break;
                        case 2:
                            printf( "\033[48;5;240m%d\033[0m", path_clrs[global_index_of(i,j)]);
                            break;
                        default:
                            printf( "\033[48;5;255m%d\033[0m", path_clrs[global_index_of(i,j)]);
                            break;
                    }
                }
                std::cout << "\n";
            }
            std::cout << "\n";
        }
    }
}