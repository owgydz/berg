#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <sys/stat.h>
#include <sstream>
#include <string>
#include <thread>
#include <chrono>
#include <sys/inotify.h>
#include <unistd.h>
#include "../bergh/parser.h"
#include "../bergh/fs.h"
#include "../bergh/option.h"

bool verbose = false;

bool shouldRebuild(const std::vector<std::string>& sources, const std::string& target) {
    if (!fileExists(target)) return true;

    time_t targetTime = getFileModificationTime(target);
    if (verbose)
        std::cout << "Target: " << target << " last modified at " << ctime(&targetTime);

    for (const std::string& source : sources) {
        if (!fileExists(source)) return true;

        time_t sourceTime = getFileModificationTime(source);
        if (verbose)
            std::cout << "Source: " << source << " last modified at " << ctime(&sourceTime);

        if (sourceTime > targetTime) return true;
    }

    return false;
}

void clean(const std::string& target) {
    if (verbose)
        std::cout << "Cleaning target: " << target << std::endl;
    if (fileExists(target)) {
        if (remove(target.c_str()) != 0) {
            std::cerr << "Error: Failed to delete target file " << target << std::endl;
        } else {
            if (verbose)
                std::cout << "Cleaned: " << target << std::endl;
        }
    } else {
        if (verbose)
            std::cout << "No target file to clean: " << target << std::endl;
    }
}

void status(const std::vector<std::string>& sources, const std::string& target) {
    if (verbose)
        std::cout << "Checking status of target: " << target << std::endl;

    if (shouldRebuild(sources, target)) {
        std::cout << "Target " << target << " is out of date or missing. Needs rebuilding.\n";
    } else {
        std::cout << "Target " << target << " is up to date.\n";
    }
}

void printHelp() {
    std::cout << "\nUsage: berg <command> [options]\n\n"
              << "Commands:\n"
              << "  build    - Build the .berg file.\n"
              << "  clean    - Remove the .berg file's targets\n"
              << "  status   - Check if the target is up to date\n"
              << "  init     - Initialize a new project (with optional target file)\n"
              << "  help     - Show this help message\n"
              << "  version  - Show version info\n"
              << "  watch    - Watch for file changes and rebuild automatically\n"
              << "Options:\n"
              << "  --verbose  - Enable verbose output\n";
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
        if (verbose)
            std::cout << "Initialized project with target file: " << target << std::endl;
    } else {
        std::cerr << "Error: Could not create target file " << target << std::endl;
    }
}

void executeScript(const std::string& script) {
    if (!script.empty()) {
        if (verbose)
            std::cout << "Executing script: " << script << std::endl;
        int result = system(script.c_str());
        if (result != 0) {
            std::cerr << "Script execution failed: " << script << std::endl;
        }
    }
}

void watchFiles(const std::vector<std::string>& sources, const std::string& target, const std::string& buildCommand) {
    int inotifyFd = inotify_init();
    if (inotifyFd < 0) {
        std::cerr << "Error: inotify_init failed" << std::endl;
        return;
    }

    for (const std::string& source : sources) {
        int wd = inotify_add_watch(inotifyFd, source.c_str(), IN_MODIFY);
        if (wd < 0) {
            std::cerr << "Error: inotify_add_watch failed for " << source << std::endl;
            return;
        }
    }

    char buffer[1024];
    while (true) {
        int length = read(inotifyFd, buffer, 1024);
        if (length < 0) {
            std::cerr << "Error: read failed" << std::endl;
            return;
        }

        for (int i = 0; i < length; i += sizeof(struct inotify_event)) {
            struct inotify_event *event = (struct inotify_event *) &buffer[i];
            if (event->mask & IN_MODIFY) {
                std::cout << "File modified: " << event->name << std::endl;
                std::cout << "Rebuilding target: " << target << std::endl;
                int result = system(buildCommand.c_str());
                if (result != 0) {
                    std::cerr << "Build failed" << std::endl;
                } else {
                    std::cout << target << " built successfully.\n";
                }
            }
        }
    }

    close(inotifyFd);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printHelp();
        return 1;
    }

    std::string command = argv[1];

    // Check for verbose flag
    for (int i = 2; i < argc; ++i) {
        if (std::string(argv[i]) == "--verbose") {
            verbose = true;
        }
    }

    if (command == "build") {
        BergParser parser;
        OptionManager optionManager;
        if (!parser.parseFile("build.berg")) {
            std::cerr << "Error: Could not read the Berg file" << std::endl;
            return 1;
        }

        std::string preBuildScript = parser.getValue("pre_build_script");
        std::string postBuildScript = parser.getValue("post_build_script");

        // Execute pre-build script
        executeScript(preBuildScript);

        std::string target = parser.getValue("target");
        std::vector<std::string> sources = parser.getSources();
        std::string buildCommand = parser.getCommand();

        if (target.empty() || buildCommand.empty()) {
            std::cerr << "Error: Invalid .berg file. Check your file for errors." << std::endl;
            return 1;
        }

        if (verbose)
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

        // Execute post-build script
        executeScript(postBuildScript);

    } else if (command == "clean") {
        BergParser parser;
        if (!parser.parseFile("build.berg")) {
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
    } else if (command == "watch") {
        BergParser parser;
        if (!parser.parseFile("build.berg")) {
            std::cerr << "Error: Could not read the Berg file" << std::endl;
            return 1;
        }

        std::string target = parser.getValue("target");
        std::vector<std::string> sources = parser.getSources();
        std::string buildCommand = parser.getCommand();

        if (target.empty() || buildCommand.empty()) {
            std::cerr << "Error: Invalid .berg file. Check your file for errors." << std::endl;
            return 1;
        }

        watchFiles(sources, target, buildCommand);
    } else {
        std::cerr << "Unknown command: " << command << std::endl;
        return 1
