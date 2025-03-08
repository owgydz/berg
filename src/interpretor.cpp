#include "../bergh/interpretor.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

namespace Berg {

Interpreter::Interpreter(const std::vector<std::string>& files) 
    : files(files), isParsed(false) {}

bool Interpreter::parse() {
    targets.clear();
    for (const auto& file : files) {
        if (!parseFile(file)) {
            return false;
        }
    }
    isParsed = true;
    return true;
}

bool Interpreter::isValid() const {
    return isParsed;
}

std::unordered_map<std::string, std::vector<std::string>> Interpreter::getTargets() const {
    return targets;
}

bool Interpreter::isValidFile(const std::string& file) {
    std::ifstream f(file);
    return f.good();
}

bool Interpreter::parseFile(const std::string& file) {
    if (!isValidFile(file)) {
        std::cerr << "Error: File not found - " << file << "\n";
        return false;
    }

    std::ifstream inFile(file);
    std::string line;
    std::string currentTarget;

    while (std::getline(inFile, line)) {
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

    return true;
}

std::string Interpreter::trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t");
    return str.substr(first, last - first + 1);
}

} // namespace Berg
