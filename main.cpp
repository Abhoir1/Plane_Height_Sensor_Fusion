// main.cpp
#include "parser.h"
#include <iostream>

int main() {
    const std::string filepath = "C:\\Users\\aditi\\Desktop\\Leet_Code\\OOP\\C++\\Pyka\\Given_Data\\log1.csv";

    std::vector<Row> data = parseCSV(filepath);

    for (const auto datum : data) {
        std::cout << " gps=" << datum.gps << " alt1=" << datum.alt1<< " alt2=" << datum.alt2 << "\n";
    }

    //std::cout << "Loaded " << data.size() << " rows\n";
    //std::cout << "First row: t=" << data[0].timestamp
    //    << " gps=" << data[0].gps
    //    << " alt1=" << data[0].alt1
    //    << " alt2=" << data[0].alt2 << "\n";
    //std::cout << "Last row:  t=" << data.back().timestamp
    //    << " gps=" << data.back().gps << "\n";

    return 0;
}