#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <sys/stat.h>
#include <sstream>
#include "../bergh/parser.h"
#include "../bergh/fs.h"
#include "../bergh/interpretor.h"   
#include "../bergh/runner.h"


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
              << "  build    - Build the target\n"
              << "  clean    - Remove the target file\n"
              << "  status   - Check if the target is up to date\n"
              << "  init     - Initialize a new project (with optional target file)\n"
              << "  help     - Show this help message\n"
              << "  version  - Show version info\n";
}

void printVersion() {
    std::cout << "\nBerg Build System v1.1.13287\n"
              << "Current BTB (build the berg) version: v0.6.12471.9\n\n"
              << "The creation of this project was inspired by Ninja.\n"
              << "View here: https://github.com/ninja-build/ninja\n\n"
              << "This project is led by Owen Gaydosz and the Bluegill Studios Berg team.\n"
              << "View the source code here: https://github.com/owgydz/berg\n\n";
}

void initProject(const std::string& target) {
    std::ofstream buildFile(target);
    if (buildFile.is_open()) {
        buildFile << "target: my_program\n"
                  << "source:\n"
                  << "command: g++ -o my_program\n";
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
        if (!parser.parseFile("build.berg")) {
            std::cerr << "Error: Could not read build.berg" << std::endl;
            return 1;
        }

        std::string target = parser.getValue("target");
        std::vector<std::string> sources = parser.getSources();
        std::string buildCommand = parser.getCommand();

        if (target.empty() || buildCommand.empty()) {
            std::cerr << "Error: Invalid build.berg file" << std::endl;
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
        if (!parser.parseFile("build.berg")) {
            std::cerr << "Error: Could not read build.berg" << std::endl;
            return 1;
        }

        std::string target = parser.getValue("target");
        clean(target);
    } else if (command == "status") {
        BergParser parser;
        if (!parser.parseFile("build.berg")) {
            std::cerr << "Error: Could not read build.berg" << std::endl;
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
    } else if (command == "tar") {
        if (argc < 3 || argv[1] != std::string("tar")) {
            std::cerr << "Usage: berg tar <target> <file1> [file2] ...\n";
            return 1;
        }

        std::vector<std::string> files(argv + 2, argv + argc);
        Berg::Interpreter interpreter(files);

        if (!interpreter.parse()) {
            return 1;
        }

        Berg::Runner runner(interpreter);
        if (!runner.executeTarget(argv[2])) {
            return 1;
        }

        return 0;
    } else {
        std::cerr << "Unknown command: " << command << std::endl;
        return 1;
    }

    return 0;
}