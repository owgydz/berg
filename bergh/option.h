#pragma once
#include <string>
#include <unordered_map>

class OptionManager {
public:
    void addOption(const std::string& name, const std::string& value) {
        options[name] = value;
    }

    bool hasOption(const std::string& name) const {
        return options.find(name) != options.end();
    }

    std::string getOptionValue(const std::string& name) const {
        auto it = options.find(name);
        if (it != options.end()) {
            return it->second;
        }
        return "";
    }

private:
    std::unordered_map<std::string, std::string> options;  
};
