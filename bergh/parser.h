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
    bool optionExists(const std::string& option) const;
    std::string getOption(const std::string& option) const;

private:
    void importBergi(const std::string& bergiFile);
    void handleOption(const std::string& optionName);
    void parseKeyValue(const std::string& key, const std::string& value);
    std::string trimWhitespace(const std::string& str) const;

    std::string target;
    std::vector<std::string> sources;
    std::string command;
    std::unordered_map<std::string, std::string> keyValues;
    std::unordered_map<std::string, std::string> options;
};
