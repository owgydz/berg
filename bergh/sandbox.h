#pragma once
#include <string>
#include <vector>

inline bool isCommandSafe(const std::string& command) {
    const std::vector<std::string> forbidden = {";", "&", "|", "`", "$(", ">", "<"};
    for (const auto& token : forbidden) {
        if (command.find(token) != std::string::npos) {
            return false;
        }
    }
    return true;
}
