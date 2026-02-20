#include "parser.h"
#include <iostream>
#include <sstream>
#include <fstream>

std::vector<Row> parseCSV(const std::string& file_path) {
	std::vector<Row> rows;
	std::ifstream file(file_path);

	if (!file.is_open()) {
		std::cerr << "Could not open the file. \n";
		return rows;
	}

    std::string line;
    std::getline(file, line); 

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::istringstream ss(line);
        std::string token;
        Row r;

        std::getline(ss, token, ','); r.timestamp = std::stod(token);
        std::getline(ss, token, ','); r.gps = std::stod(token);
        std::getline(ss, token, ','); r.alt1 = std::stod(token);
        std::getline(ss, token, ','); r.alt2 = std::stod(token);

        rows.push_back(r);
    }

    return rows;
}