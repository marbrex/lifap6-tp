#include "table.h"
#include <iostream>
#include <string>

typedef Table<std::string> TableString;
typedef Info<std::string> InfoString;

int main() {
    TableString t(20);

    InfoString i;
    i = std::string("toto");

    InfoString i2("mew");
    
    InfoString i3("tata");
    i3 = std::string("nine");

    t.add(8, i);
    t.add(3, i);
    t.add(2, i);
    t.add(2, i2);
    t.add(9, i3);

    t.show();

    return 0;
}
