// main.cpp
#include "parser.h"
#include "outlierRejection.h"
#include "groundTracker.h"
#include <iostream>
#include <fstream>

int main() {
    const std::string filePath = "C:\\Users\\aditi\\Desktop\\Leet_Code\\OOP\\C++\\Pyka\\Given_Data\\log1.csv";

    const std::string outputFilePath = "C:\\Users\\aditi\\Desktop\\Leet_Code\\OOP\\C++\\Pyka\\Output\\file.csv";
    std::ofstream outFile(outputFilePath);
    outFile << "timestamp,gps_altitude,altimeter_1_altitude,altimeter_2_altitude,ok1,ok2,estimatedHeight\n";


    std::vector<Row> data = parseCSV(filePath);
    double prevAlt1 = std::numeric_limits<double>::quiet_NaN();
    double prevAlt2 = std::numeric_limits<double>::quiet_NaN();

    const double DT = 0.010; //Timestamp
    const double MAX_CHANGE_RATE = 30.0; //Max allowed vertical speed for outlier rejection
    const double LOW_ALT = 15.0;  //Crop spraying height below this altimeters should be priorotized
    const double HIGH_ALT = 40.9;  //Altimeters go crazy after this so GPS calculated AGL should be trusted here
    const double ALPHA = 0.15;


    int rejectedCount{ 0 };
    double estimatedHeight = 0.0;

    GroundTracker groundTracker;

    for (const auto& datum : data) {
        //std::cout << " gps=" << datum.gps << " alt1=" << datum.alt1<< " alt2=" << datum.alt2 << "\n";

        bool isAlt1Valid = isValidReading(datum.alt1, prevAlt1, DT, MAX_CHANGE_RATE);
        bool isAlt2Valid = isValidReading(datum.alt2, prevAlt2, DT, MAX_CHANGE_RATE);

        if (!isAlt1Valid || !isAlt2Valid) {
            rejectedCount++;
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

        if (isAlt1Valid && datum.alt1 < 40.0) {
            groundTracker.update(datum.gps, datum.alt1);
        }

        if (isAlt2Valid && datum.alt2 < 40.0) {
            groundTracker.update(datum.gps, datum.alt2);
        }

        double gpsAgl = -1.0;
        if (groundTracker.isReady()) {
            gpsAgl = groundTracker.toAgl(datum.gps);
        }

        //EMA between fused altimeters and GPS agl

        double blend = 0.0;
        if (estimatedHeight <= LOW_ALT) {
            blend = 1.0;
        }
        else if (estimatedHeight > HIGH_ALT) {
            blend = 0.0;
        }
        else {
            blend = 1.0 - (estimatedHeight - LOW_ALT) / (HIGH_ALT - LOW_ALT);
        }

        double target = estimatedHeight;

        if (fusedAltimeter >= 0 && gpsAgl >= 0) {
            target = blend * fusedAltimeter + (1 - blend) * gpsAgl;
        }
        else if (fusedAltimeter >= 0) {
            target = fusedAltimeter;
        }
        else if (gpsAgl >= 0) {
            target = gpsAgl;
        }

        estimatedHeight = ALPHA * target + (1 - ALPHA) * estimatedHeight;

        if (isAlt1Valid) {
            prevAlt1 = datum.alt1;
        }

        if (isAlt2Valid) {
            prevAlt2 = datum.alt2;
        }


        outFile << datum.timestamp << "," << datum.gps << "," << datum.alt1 << ","
            << datum.alt2 << "," << isAlt1Valid << ","  << isAlt2Valid << "," << estimatedHeight << "\n";

    }


    outFile.close();
    std::cout << "File saved \n";
    return 0;
}