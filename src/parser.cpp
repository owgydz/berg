#include "../bergh/parser.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

// Function to check if a file exists
bool fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

// Function to execute the build command for the target
void executeTarget(const std::string& target) {
    // Implementation of the build command execution
    std::cout << "Executing build command for target: " << target << "\n";
    // Add your build command execution logic here
}

void tar(std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cerr << "Usage: berg tar <target> <file1> [file2] ...\n";
        return;
    }

    std::string target = args[0];  // The first argument is the target
    std::string buildFile = args[1]; // The second argument is the build file

    // Process the target and build file properly.
    if (!fileExists(buildFile)) {
        std::cerr << "Error: Build file not found - " << buildFile << "\n";
        return;
    }

    // Load and parse the build file
    std::ifstream file(buildFile);
    std::string line;
    while (std::getline(file, line)) {
        // Look for the target in the build file and execute it
        if (line.find("target " + target) != std::string::npos) {
            // Execute the build command for the target
            std::cout << "Building target: " << target << "\n";
            // Call the function to execute the build command for the target
            executeTarget(target);
            return;
        }
    }

    std::cerr << "Error: Target not found - " << target << "\n";
}

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
