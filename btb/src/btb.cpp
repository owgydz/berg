#include <iostream>
#include <string>
#include <cstdlib>
#include "cli.h"
#include "../btbh/inter.h"
#include "../btbh/depend.h"
#include "../btbh/runner.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Error: Missing command." << std::endl;
        return 1;
    }

    std::string command = argv[1];

    if (command == "build") {
        // Parse and build the project.
        // This assumes that the build.berg file is present in the current directory after building via Berg.
        // If not, we can fallback to an error message.
        std::cout << "Starting build process. Please wait." << std::endl;
        BTB::Interpreter interpreter;
        if (!interpreter.parseFile("build.berg")) {
            std::cerr << "Error: Failed to parse build.berg. Is it in the directory?" << std::endl;
            return 1;
        }

        BTB::DependencyManager dependencyManager;
        if (!dependencyManager.resolveDependencies(interpreter.getSources())) {
            std::cerr << "Error: Dependency resolution failed." << std::endl;
            return 1;
        }

        BTB::Runner runner;
        if (!runner.runBuildCommand(interpreter.getBuildCommand())) {
            std::cerr << "Error: Build failed." << std::endl;
            return 1;
        }

        std::cout << "Build completed successfully." << std::endl;
    } else if (command == "help") {
        BTB::CLI::showHelp();
    } else {
        std::cerr << "Unknown command: " << command << std::endl;
        return 1;
    }

    return 0;
}
