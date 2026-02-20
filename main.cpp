// main.cpp
#include "parser.h"
#include "outlier_rejection.h"
#include <iostream>

int main() {
    const std::string filePath = "C:\\Users\\aditi\\Desktop\\Leet_Code\\OOP\\C++\\Pyka\\Given_Data\\log1.csv";

    std::vector<Row> data = parseCSV(filePath);
    double prevAlt1 = std::numeric_limits<double>::quiet_NaN();
    double prevAlt2 = std::numeric_limits<double>::quiet_NaN();

    double DT = 0.010;
    double MAX_CHANGE_RATE = 30.0;
    int rejectedCount{ 0 };

    for (const auto& datum : data) {
        //std::cout << " gps=" << datum.gps << " alt1=" << datum.alt1<< " alt2=" << datum.alt2 << "\n";

        bool isAlt1Valid = isValidReading(datum.alt1, prevAlt1, DT, MAX_CHANGE_RATE);
        bool isAlt2Valid = isValidReading(datum.alt2, prevAlt2, DT, MAX_CHANGE_RATE);

        if (!isAlt1Valid || !isAlt2Valid) {
            rejectedCount++;
        }

        if (isAlt1Valid) {
            prevAlt1 = datum.alt1;
        }

        if (isAlt2Valid) {
            prevAlt2 = datum.alt2;
        }

        double fusedAltimeter = -1.0;

        if (isAlt1Valid && isAlt2Valid) {
            fusedAltimeter = (datum.alt1 + datum.alt2) / 2.0;
        }
        else if (isAlt1Valid) {
            fusedAltimeter = datum.alt1;
        }
        else if (isAlt2Valid) {
            fusedAltimeter = datum.alt2;
        }
    }

    std::cout << "Rejected readings: " << rejectedCount << "\n";



    return 0;
}