#pragma once
#include <string>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

struct StrategyItem {
    std::wstring titleW;
    std::string keyName;
    std::string desc;
    std::string args;
};

extern const std::vector<StrategyItem> G_STRATEGIES;

std::string GetStratsJson();
std::string BuildStrategyCommandLine(const std::string& keyName, const fs::path& rootPath);