// csvParser.h
#pragma once
#include <string>
#include <vector>

struct Row {
    double timestamp;
    double gps;
    double alt1;
    double alt2;
};

std::vector<Row> parseCSV(const std::string& filepath);
