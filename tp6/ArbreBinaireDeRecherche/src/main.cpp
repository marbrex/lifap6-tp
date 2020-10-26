#include "abr.h"
#include <queue>
#include <iostream>

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
    a.insert(7);
    a.insert(11);

    // a.insert(50);
    // a.insert(60);
    // a.insert(40);
    // a.insert(30);
    // a.insert(45);
    // a.insert(55);
    // a.insert(65);

    a.draw();

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
