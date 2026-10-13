#pragma once
#include <string>
#include <filesystem>
#include <windows.h>

namespace fs = std::filesystem;

fs::path find_exe(const fs::path& root);
bool IsWinwsRunning();
void run_process_non_blocking(const std::string& cmd, const std::string& working_dir);
void run_cmd_silent(const std::string& cmd);
void KillProcessByName(const wchar_t* filename);
void StopBypassAndDriver();
void InitFiles(bool force);
void RunBypass(const std::string& bat_name);
void SetSystemDns(const std::string& mode);
void PreloadDriver();