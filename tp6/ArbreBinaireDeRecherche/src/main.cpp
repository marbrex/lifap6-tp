#include "abr.h"
#include <queue>
#include <iostream>

void mult_by_two(Node* n) {
    n->element*=2;
    std::cout << n->element << " ";
}

int main() {
    ABR a;

    a.insert(6);
    a.insert(3);
    a.insert(9);
    a.insert(8);
    a.insert(4);
    a.insert(2);
    a.insert(10);
    a.insert(5);
    a.insert(1);
    a.insert(11);

    std::cout << " *** Affichage avec extra informations ***" << std::endl;
    a.draw(true);

    std::cout << " *** Differents parcours de l'ABR (fonction d'affichage par defaut) ***" << std::endl;
    std::cout << "Parcours INFIX : " << std::endl;
    a.parcours(0);

    std::cout << "Parcours PREFIX : " << std::endl;
    a.parcours(1);

    std::cout << "Parcours POSTFIX : " << std::endl;
    a.parcours(2);

    std::cout << "Parcours PREFIX (MULTIPLICATION par 2) : " << std::endl;
    a.parcours(1, mult_by_two);

    std::cout << " *** Affichage sans extra informations (comportement par defaut) ***" << std::endl;
    a.draw();

    std::cout << " *** Affichage a partir du fils gauche ***" << std::endl;
    a.draw_from_node(a.get_head()->left);

    std::cout << " *** Recherche de l'element 6 ***" << std::endl;
    Node* n = a.find(6);
    if (n) {
        std::cout << "Element found : ";
        std::cout << n->element << std::endl << std::endl;
    }
    else std::cout << "Element not found" << std::endl << std::endl;

    std::cout << " *** Creation d'ABR par copie ***" << std::endl;
    ABR b(a);
    b.draw(true);

    std::cout << " *** Affectation d'ABR ***" << std::endl;
    std::cout << "Creation de c et d ..." << std::endl;
    std::cout << "Affectation d = c = b ..." << std::endl;
    ABR c,d;
    d = c = b;

    std::cout << "Insertion de 24 dans b ..." << std::endl;
    b.insert(24);
    std::cout << "Insertion de 14 dans c ..." << std::endl;
    c.insert(14);

    std::cout << "b:" << std::endl;
    b.draw(true);
    std::cout << "c:" << std::endl;
    c.draw(true);
    std::cout << "d:" << std::endl;
    d.draw(true);

    std::cout << " *** Suppression d'un element ***" << std::endl;
    std::cout << "12 dans d:" << std::endl;
    d.remove(12);
    d.draw(true);

    std::cout << "8 dans d:" << std::endl;
    d.remove(8);
    d.draw(true);

    std::cout << "18 dans d:" << std::endl;
    d.remove(18);
    d.draw(true);

    std::cout << "10 dans d:" << std::endl;
    d.remove(10);
    d.draw(true);

    std::cout << "22 dans d:" << std::endl;
    d.remove(22);
    d.draw(true);


    return 0;
}
