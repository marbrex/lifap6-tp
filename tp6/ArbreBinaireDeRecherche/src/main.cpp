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
    a.insert(11);
    a.insert(7);
    a.insert(1);

    a.draw();

    // std::queue<int*> q;
    // q.push(nullptr);
    // if (!q.front()) {
    //     std::cout << "nullptr!" << std::endl;
    // }

    return 0;
}
