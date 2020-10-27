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

    a.draw();

    a.parcours(mult_by_two);

    a.draw(false);

    // a.draw_from_node(a.get_head()->right);

    // Node* n = a.find(11);
    // if (n) {
    //     std::cout << "OK" << std::endl;
    //     std::cout << n->element << std::endl;
    // }
    // else std::cout << "NOPE" << std::endl;

    // std::queue<int*> q;
    // q.push(nullptr);
    // if (!q.front()) {
    //     std::cout << "nullptr!" << std::endl;
    // }

    return 0;
}
