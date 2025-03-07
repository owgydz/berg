#include "parser.h"
#include <fstream>
#include <sstream>

bool BergParser::parseFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) return false;

    std::string line;
    while (std::getline(file, line)) {
        size_t pos = line.find(':');
        if (pos == std::string::npos) continue;
        
        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1);
        data[key] = value;
    }

    return true;
}

std::string BergParser::getValue(const std::string& key) const {
    auto it = data.find(key);
    return it != data.end() ? it->second : "";
}
