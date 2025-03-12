#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <sys/stat.h>
#include <sstream>
#include "../bergh/parser.h"
#include "../bergh/fs.h"
#include "../bergh/option.h"

bool shouldRebuild(const std::vector<std::string>& sources, const std::string& target) {
    if (!fileExists(target)) return true;

    time_t targetTime = getFileModificationTime(target);
    std::cout << "Target: " << target << " last modified at " << ctime(&targetTime);

    for (const std::string& source : sources) {
        if (!fileExists(source)) return true;

        time_t sourceTime = getFileModificationTime(source);
        std::cout << "Source: " << source << " last modified at " << ctime(&sourceTime);

        if (sourceTime > targetTime) return true;
    }

    return false;
}

void clean(const std::string& target) {
    std::cout << "Cleaning target: " << target << std::endl;
    if (fileExists(target)) {
        if (remove(target.c_str()) != 0) {
            std::cerr << "Error: Failed to delete target file " << target << std::endl;
        } else {
            std::cout << "Cleaned: " << target << std::endl;
        }
    } else {
        std::cout << "No target file to clean: " << target << std::endl;
    }
}

void status(const std::vector<std::string>& sources, const std::string& target) {
    std::cout << "Checking status of target: " << target << std::endl;

    if (shouldRebuild(sources, target)) {
        std::cout << "Target " << target << " is out of date or missing. Needs rebuilding.\n";
    } else {
        std::cout << "Target " << target << " is up to date.\n";
    }
}

void printHelp() {
    std::cout << "\nUsage: berg <command>\n\n"
              << "Commands:\n"
              << "  build    - Build the .berg file.\n"
              << "  clean    - Remove the .berg file's targets\n"
              << "  status   - Check if the target is up to date\n"
              << "  init     - Initialize a new project (with optional target file)\n"
              << "  help     - Show this help message\n"
              << "  version  - Show version info\n";
}

void printVersion() {
    std::cout << "\nBerg Build System v1.1.4194.21 BETA\n\n"
              << "Creation of this project was inspired by Ninja.\n"
              << "View here: https://github.com/ninja-build/ninja\n\n"
              << "This project was led by Owen Gaydosz and the Bluegill Studios Berg team.\n"
              << "View the source code here: https://github.com/owgydz/berg\n\n";
}

void initProject(const std::string& target) {
    std::ofstream buildFile(target);
    if (buildFile.is_open()) {
        buildFile << "// Berg build file template.\n"
                  << "target: sample\n"
                  << "source: main.cpp\n"
                  << "command: g++ -o sample main.cpp\n";
        buildFile.close();
        std::cout << "Initialized project with target file: " << target << std::endl;
    } else {
        std::cerr << "Error: Could not create target file " << target << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printHelp();
        return 1;
    }

    std::string command = argv[1];

    if (command == "build") {
        BergParser parser;
        OptionManager optionManager;  
        if (!parser.parseFile("MAIN.berg")) {
            std::cerr << "Error: Could not read the Berg file" << std::endl;
            return 1;
        }

        // Option handling. 
        if (argc > 2) {
            for (int i = 2; i < argc; ++i) {
                if (std::string(argv[i]).find("-opt") == 0) {
                    std::string optionName = std::string(argv[i]).substr(5);
                    if (optionManager.hasOption(optionName)) {
                        std::cout << "Using option: " << optionName << "\n";
                        // Apply the option.
                    } else {
                        std::cerr << "Build option not found. Did you make a typo?\n";
                        return 1;
                    }
                }
            }
        }

        std::string target = parser.getValue("target");
        std::vector<std::string> sources = parser.getSources();
        std::string buildCommand = parser.getCommand();

        if (target.empty() || buildCommand.empty()) {
            std::cerr << "Error: Invalid .berg file. Check your file for errors." << std::endl;
            return 1;
        }

        std::cout << "Checking dependencies for target: " << target << "...\n";
        if (shouldRebuild(sources, target)) {
            std::cout << "Dependencies changed. Rebuilding " << target << "...\n";
            std::cout << "Executing command: " << buildCommand << std::endl;
            int result = system(buildCommand.c_str());
            if (result != 0) {
                std::cerr << "Build failed" << std::endl;
                return result;
            }
            std::cout << target << " built successfully.\n";
        } else {
            std::cout << target << " is up to date.\n";
        }
    } else if (command == "clean") {
        BergParser parser;
        if (!parser.parseFile("MAIN.berg")) {
            std::cerr << "Error: Could not read the .berg file" << std::endl;
            return 1;
        }

        std::string target = parser.getValue("target");
        clean(target);
    } else if (command == "status") {
        BergParser parser;
        if (!parser.parseFile("MAIN.berg")) {
            std::cerr << "Error: Could not read the Berg file" << std::endl;
            return 1;
        }

        std::string target = parser.getValue("target");
        std::vector<std::string> sources = parser.getSources();
        status(sources, target);
    } else if (command == "help") {
        printHelp();
    } else if (command == "version") {
        printVersion();
    } else if (command == "init") {
        std::string target = "build.berg";

        if (argc > 2 && std::string(argv[2]) == "-t") {
            if (argc > 3) {
                target = argv[3];
            } else {
                std::cerr << "Error: Missing target file after -t flag" << std::endl;
                return 1;
            }
        }

        initProject(target);
    } else {
        std::cerr << "Unknown command: " << command << std::endl;
        return 1;
    }

    return 0;
}
