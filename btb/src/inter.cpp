#include "../btbh/inter.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

namespace BTB {

bool Interpreter::parseFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filePath << std::endl;
        return false;
    }

    std::string line;
    bool readingSources = false;
    bool readingCommand = false;

    while (std::getline(file, line)) {
        if (line.find("target:") == 0) {
            targets.push_back(line.substr(7));
        } else if (line.find("source:") == 0) {
            std::string sourcesLine = line.substr(7);
            std::istringstream stream(sourcesLine);
            std::string source;
            while (stream >> source) {
                sources.push_back(source);
            }
            readingSources = true;
        } else if (line.find("command:") == 0) {
            buildCommand = line.substr(8);
            readingCommand = true;
        } else if (readingCommand && line[0] != '#') { // Allow multi-line commands
            buildCommand += "\n" + line;
        }
    }

    return !targets.empty() && !sources.empty() && !buildCommand.empty();
}

std::vector<std::string> Interpreter::getSources() const {
    return sources;
}

std::string Interpreter::getBuildCommand() const {
    return buildCommand;
}

std::vector<std::string> Interpreter::getTargets() const {
    return targets;
}

} // namespace BTB
