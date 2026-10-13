#pragma once
#include <string>
#include <filesystem>
#include <windows.h>
#include <vector>

namespace fs = std::filesystem;

extern const std::string APP_NAME;
extern const std::string VER;
extern const std::string URL_ZIP;

extern const fs::path ROOT;
extern const fs::path FILES;
extern const fs::path EX_HOSTS;
extern const fs::path EX_IPS;
extern const fs::path CFG_FILE;
extern const fs::path CUSTOM_HOSTS;

extern const std::string STRATS_JSON;

std::wstring Utf8ToWstring(const std::string& str);
std::string WstringToUtf8(const std::wstring& wstr);
std::wstring get_json_string_w(const std::wstring& json, const std::wstring& key);
std::string get_json_string(const std::string& json, const std::string& key);
bool get_json_bool(const std::string& json, const std::string& key, bool default_val = false);
std::string escape_json_string(const std::string& input);

void set_autorun(bool enable);
std::string GetConfig();
void SaveConfig(const std::string& cfg_json);