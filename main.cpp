// main.cpp
#include "parser.h"
#include "outlierRejection.h"
#include "groundTracker.h"
#include "heightEstimator.h"
#include <iostream>
#include <fstream>
#include <iomanip>

int main() {
    const std::string filePath = "C:\\Users\\aditi\\Desktop\\Leet_Code\\OOP\\C++\\Pyka\\Given_Data\\log2.csv";

    const std::string outputFilePath = "C:\\Users\\aditi\\Desktop\\Leet_Code\\OOP\\C++\\Pyka\\Output\\outputfile2.csv";
    std::ofstream outFile(outputFilePath);
    outFile << "timestamp,gps_altitude,altimeter_1_altitude,altimeter_2_altitude,ok1,ok2,rateAlt1,rateAlt2,prevalt1,prevalt2,estimatedHeight\n";


    std::vector<Row> data = parseCSV(filePath);
    double prevAlt1 = std::numeric_limits<double>::quiet_NaN();
    double prevAlt2 = std::numeric_limits<double>::quiet_NaN();

    const double DT = 0.010; //Timestamp
    const double MAX_CHANGE_RATE = 30.0; //Max allowed vertical speed for outlier rejection
    const double LOW_ALT = 30;  //Crop spraying height below this altimeters should be priorotized
    const double HIGH_ALT = 40;  //Altimeters go crazy after this so GPS calculated AGL should be trusted here
    const double ALPHA = 0.15;

    bool initialized = false;


    int rejectedCount{ 0 };
    double estimatedHeight = 0.0;

    GroundTracker groundTracker;
    HeightEstimator heightEstimator(LOW_ALT, HIGH_ALT, 0.15, 0.02);

    outFile << std::fixed << std::setprecision(10);


    for (const auto& datum : data) {
        //std::cout << " gps=" << datum.gps << " alt1=" << datum.alt1<< " alt2=" << datum.alt2 << "\n";

        bool isAlt1Valid = isValidReading(datum.alt1, prevAlt1, DT, MAX_CHANGE_RATE);
        bool isAlt2Valid = isValidReading(datum.alt2, prevAlt2, DT, MAX_CHANGE_RATE);

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

        if (!initialized && fusedAltimeter >= 0) {
            estimatedHeight = fusedAltimeter;
            initialized = true;
        }

        if (fusedAltimeter >= 0) {
            groundTracker.update(datum.gps, fusedAltimeter);
        }


        double gpsAgl = -1.0;
        if (groundTracker.isReady()) {
            gpsAgl = groundTracker.toAgl(datum.gps);
        }

        double estimatedHeight = heightEstimator.update(fusedAltimeter, gpsAgl);

        outFile << datum.timestamp << "," << datum.gps << "," << datum.alt1 << ","
            << datum.alt2 << "," << isAlt1Valid << "," << isAlt2Valid << "," << std::abs(datum.alt1 - prevAlt1) / DT << "," << std::abs(datum.alt2 - prevAlt2) / DT << "," << prevAlt1 << "," << prevAlt2<< "," << estimatedHeight << "\n";

        if (isAlt1Valid) {
            prevAlt1 = datum.alt1;
        }
        else {
            prevAlt1 = 0.99 * prevAlt1 + 0.01 * estimatedHeight;
        }

        if (isAlt2Valid) {
            prevAlt2 = datum.alt2;
        }
        else {
            prevAlt2 = 0.99 * prevAlt2 + 0.01 * estimatedHeight;
        }
    }
    outFile.close();
    std::cout << "File saved \n";
    return 0;
}