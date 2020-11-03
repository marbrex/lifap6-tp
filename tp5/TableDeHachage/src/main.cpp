#include "table.h"
#include <iostream>
#include <string>

typedef Table<unsigned int,std::string> Table_;
typedef Info<std::string> InfoString;
typedef Key<unsigned int> KeyInt;

int main() {
    Table_ t(20);

    // KeyInt k;
    // k = 8;
    // InfoString i;
    // i = std::string("toto");

    // KeyInt k2(2);
    // InfoString i2("mew");
    
    // KeyInt k3(234);
    // k3 = 9;
    // InfoString i3("tata");
    // i3 = std::string("nine");

    t.add(8, std::string("toto"));
    t.add(2, std::string("mew"));
    t.add(9, std::string("nine"));

    t.show(true);

    std::cout << "Info of 9: " << t[9] << std::endl;

    t.remove(2);
    t.show();

    t.add(2, std::string("tata"));
    t.show();

    return 0;
}
