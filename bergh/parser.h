#pragma once
#include <string>
#include <unordered_map>
#include <vector>

class BergParser {
public:
    bool parseFile(const std::string& filename);
    std::string getValue(const std::string& key) const;
    std::vector<std::string> getSources() const;
    std::string getCommand() const;

private:
    std::string target;
    std::vector<std::string> sources;
    std::string command;
};
