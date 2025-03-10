#include "../bergh/parser.h"
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <iostream>

bool BergParser::parseFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) return false;

    std::string line;
    while (std::getline(file, line)) {
        // Trim whitespace from the line
        line = trimWhitespace(line);

        if (line.empty() || line[0] == '//') continue; // Skip empty or comment lines

        // Check for imp statement to import .bergi files
        if (line.substr(0, 3) == "imp") {
            std::string bergiFile = line.substr(4);
            importBergi(bergiFile);
            continue;
        }

        size_t pos = line.find(':');
        if (pos == std::string::npos) continue;

        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1);

        if (key == "option") {
            // Process the option definitions inside the .berg file
            handleOption(value);
        } else {
            // Parse any other general key-value pairs
            parseKeyValue(key, value);
        }
    }

    return true;
}

std::string BergParser::getValue(const std::string& key) const {
    auto it = keyValues.find(key);
    if (it != keyValues.end()) {
        return it->second;
    }
    return "";
}

std::vector<std::string> BergParser::getSources() const {
    return sources;
}

std::string BergParser::getCommand() const {
    return command;
}

// Helper function to trim whitespace from the start and end of a string
std::string BergParser::trimWhitespace(const std::string& str) const {
    size_t start = str.find_first_not_of(" \t");
    size_t end = str.find_last_not_of(" \t");
    return (start == std::string::npos || end == std::string::npos) ? "" : str.substr(start, end - start + 1);
}

// Function to import .bergi files and store their options
void BergParser::importBergi(const std::string& bergiFile) {
    std::ifstream file(bergiFile);
    if (!file) {
        std::cerr << "ERR: Could not open .bergi file and/or missing an import. Is it not in this directory? " << bergiFile << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        line = trimWhitespace(line);
        if (line.empty() || line[0] == '#') continue;

        size_t pos = line.find(':');
        if (pos == std::string::npos) continue;

        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1);
        
        if (key == "option") {
            handleOption(value);
        }
    }
}

// Function to handle the "option" keyword in both .bergi and .berg files
void BergParser::handleOption(const std::string& optionName) {
    // Check if this option has been previously defined
    if (options.find(optionName) != options.end()) {
        std::cerr << "WARN!: Option " << optionName << " is already defined.\n";
    } else {
        options[optionName] = optionName; // Just store the option name for now, can add values later
    }
}

// Parse other key-value pairs (command, target, etc.)
void BergParser::parseKeyValue(const std::string& key, const std::string& value) {
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
    } else {
        keyValues[key] = value; // For general key-value pairs
    }
}
