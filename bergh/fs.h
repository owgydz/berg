#pragma once
#include <string>

bool fileExists(const std::string& filename);
time_t getFileModificationTime(const std::string& filename);
