#include "../bergh/interpreter.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

namespace Berg {

Interpreter::Interpreter(const std::string& filename) 
    : filename(filename), valid(false) {}

bool Interpreter::parse() {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Could not open " << filename << "\n";
        return false;
    }

    std::string line;
    std::string currentTarget;
    while (std::getline(file, line)) {
        line = trim(line);

        // Skip empty lines or comments
        if (line.empty() || line[0] == '#') continue;

        // Target definition
        if (line.back() == ':') {
            currentTarget = line.substr(0, line.size() - 1);
            targets[currentTarget] = {};
        }
        // Commands for the target
        else if (!currentTarget.empty()) {
            targets[currentTarget].push_back(line);
        } else {
            std::cerr << "Syntax Error: Unexpected command outside a target block: " << line << "\n";
            return false;
        }
    }

    valid = true;
    return true;
}

std::unordered_map<std::string, std::vector<std::string>> Interpreter::getTargets() const {
    return targets;
}

bool Interpreter::isValid() const {
    return valid;
}

std::string Interpreter::trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t");
    return str.substr(first, last - first + 1);
}

} // namespace Berg
