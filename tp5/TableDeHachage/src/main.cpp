#include "table.h"
#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <fstream>

typedef Table<unsigned int,std::string> Table_Int_String;
typedef Table<unsigned int,int> Table_Int;

typedef Key<unsigned int> KeyInt;

typedef Info<std::string> InfoString;
typedef Info<int> InfoInt;



int measure_performance(unsigned int size_of_each_table, unsigned int number_of_tables) {
    std::vector<Table_Int*> tab;

    for(unsigned int i=0; i<number_of_tables; ++i) {
        Table_Int* t = new Table_Int(size_of_each_table);
        tab.push_back(t);
    }

    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    srand(time(NULL));

    for(unsigned int j=0; j<size_of_each_table; ++j) {
        for (unsigned int i=0; i<number_of_tables; ++i) {
            KeyInt key = rand() % 1000;
            InfoInt info = rand() % 1000;
            tab[i]->add(key,info);
        }
    }

    end = std::chrono::system_clock::now();
    int elapsed_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();

    for(unsigned int i=0; i<number_of_tables; ++i) {
        delete tab[i];
    }

    return elapsed_microseconds;
}



int main() {
    unsigned int repeat_times;

    std::cout << "How many performance measurements do you want to make? ";
    std::cin >> repeat_times;
    std::cout << std::endl;

    for (unsigned int i=0; i<repeat_times; ++i) {
        std::cout << "===== " << i+1 << " Measurement =====\n";

        unsigned int size_of_each_table;
        unsigned int number_of_tables;

        std::cout << "Enter Size for 1 Table: ";
        std::cin >> size_of_each_table;

        std::cout << "Enter Number of Tables: ";
        std::cin >> number_of_tables;

        std::cout << "Mesuring performance..." << std::endl;

        int elapsed_microseconds = measure_performance(size_of_each_table, number_of_tables);
        std::cout << "Elapsed Time: " << elapsed_microseconds << " microseconds" << std::endl;

        int elapsed_time_for_one = elapsed_microseconds / number_of_tables;
        std::cout << "Elapsed For One: " << elapsed_time_for_one << " microseconds" << std::endl;

        if (i==0) {
            std::ofstream file("data/performance.txt");
            if (file.is_open()) file << "# \"Nb Tables\" \"Time\"\n";
            file.close();
        }
        std::ofstream file("data/performance.txt", std::ios::app);

        if (file.is_open()) {
            file << number_of_tables << " " << elapsed_microseconds << "\n";
            file.close();
        }
        else std::cout << "Can not open 'data/performance.txt' file\n";

        std::cout << "=========================\n" << std::endl;
    }



    // Demonstration des fonctionnalites du module
    std::cout << "========== Demonstration des fonctionnalites du module ==========\n";

    Table_Int_String t(20);

    t.add(8, std::string("toto"));
    t.add(2, std::string("mew"));
    t.add(9, std::string("nine"));

    t.show(true);

    std::cout << "Info of 9: " << t[9] << std::endl;

    t.remove(2);
    t.show();

    t.add(2, std::string("tata"));
    t.show();

    t.set_info(9, "dom");
    t.show();

    return 0;
}
