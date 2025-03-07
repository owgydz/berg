#include "../bergh/parser.h"
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
        if (key == "target") {
            target = value;
        } else if (key == "source") {
            std::stringstream ss(value);
            std::string source;
            while (ss >> source) {
                sources.push_back(source);
            }
        } else if (key == "command") {
            command = value;
        }
    }

    return true;
}

std::string BergParser::getValue(const std::string& key) const {
    if (key == "target") return target;
    if (key == "command") return command;
    return "";
}

std::vector<std::string> BergParser::getSources() const {
    return sources;
}

std::string BergParser::getCommand() const {
    return command;
}
