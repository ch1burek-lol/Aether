#include "Config.h"
#include <fstream>
#include <sstream>

const std::string APP_NAME = "Aether";
const std::string VER = "v1.4";

const fs::path ROOT = "C:\\Aether\\Aether 1.4";
const fs::path FILES = ROOT / "files";
const fs::path EX_HOSTS = FILES / "exclude-hosts.txt";
const fs::path EX_IPS = FILES / "exclude-ips.txt";
const fs::path CFG_FILE = ROOT / "webview" / "cfg.json";
const fs::path CUSTOM_HOSTS = FILES / "custom-hosts.txt";

std::wstring Utf8ToWstring(const std::string& str) {
    if (str.empty()) return L"";
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
    std::wstring wstrTo(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
    return wstrTo;
}

std::string WstringToUtf8(const std::wstring& wstr) {
    if (wstr.empty()) return "";
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
    std::string strTo(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
    return strTo;
}

std::wstring get_json_string_w(const std::wstring& json, const std::wstring& key) {
    size_t pos = json.find(L"\"" + key + L"\"");
    if (pos == std::wstring::npos) return L"";
    size_t colon = json.find(L":", pos);
    if (colon == std::wstring::npos) return L"";
    size_t start = json.find(L"\"", colon);
    if (start == std::wstring::npos) return L"";
    size_t end = json.find(L"\"", start + 1);
    while (end != std::wstring::npos && json[end - 1] == L'\\') {
        end = json.find(L"\"", end + 1);
    }
    if (end == std::wstring::npos) return L"";
    std::wstring val = json.substr(start + 1, end - start - 1);
    std::wstring unescaped = L"";
    for (size_t i = 0; i < val.size(); ++i) {
        if (val[i] == L'\\' && i + 1 < val.size()) {
            if (val[i + 1] == L'n') { unescaped += L'\n'; i++; }
            else if (val[i + 1] == L'r') { unescaped += L'\r'; i++; }
            else if (val[i + 1] == L't') { unescaped += L'\t'; i++; }
            else if (val[i + 1] == L'"') { unescaped += L'"'; i++; }
            else if (val[i + 1] == L'\\') { unescaped += L'\\'; i++; }
            else unescaped += val[i];
        }
        else {
            unescaped += val[i];
        }
    }
    return unescaped;
}

std::string get_json_string(const std::string& json, const std::string& key) {
    size_t pos = json.find("\"" + key + "\"");
    if (pos == std::string::npos) return "";
    size_t colon = json.find(":", pos);
    if (colon == std::string::npos) return "";
    size_t start = json.find("\"", colon);
    if (start == std::string::npos) return "";
    size_t end = json.find("\"", start + 1);
    while (end != std::string::npos && json[end - 1] == '\\') {
        end = json.find("\"", end + 1);
    }
    if (end == std::string::npos) return "";
    std::string val = json.substr(start + 1, end - start - 1);
    std::string unescaped = "";
    for (size_t i = 0; i < val.size(); ++i) {
        if (val[i] == '\\' && i + 1 < val.size()) {
            if (val[i + 1] == 'n') { unescaped += '\n'; i++; }
            else if (val[i + 1] == 'r') { unescaped += '\r'; i++; }
            else if (val[i + 1] == 't') { unescaped += '\t'; i++; }
            else if (val[i + 1] == '"') { unescaped += '"'; i++; }
            else if (val[i + 1] == '\\') { unescaped += '\\'; i++; }
            else unescaped += val[i];
        }
        else {
            unescaped += val[i];
        }
    }
    return unescaped;
}

bool get_json_bool(const std::string& json, const std::string& key, bool default_val) {
    size_t pos = json.find("\"" + key + "\"");
    if (pos == std::string::npos) return default_val;
    size_t colon = json.find(":", pos);
    if (colon == std::string::npos) return default_val;
    size_t t_pos = json.find("true", colon);
    size_t f_pos = json.find("false", colon);
    if (t_pos != std::string::npos && (f_pos == std::string::npos || t_pos < f_pos)) {
        return true;
    }
    if (f_pos != std::string::npos && (t_pos == std::string::npos || f_pos < t_pos)) {
        return false;
    }
    return default_val;
}

std::string escape_json_string(const std::string& input) {
    std::string output = "\"";
    for (char c : input) {
        switch (c) {
        case '\"': output += "\\\""; break;
        case '\\': output += "\\\\"; break;
        case '\b': output += "\\b"; break;
        case '\f': output += "\\f"; break;
        case '\n': output += "\\n"; break;
        case '\r': output += "\\r"; break;
        case '\t': output += "\\t"; break;
        default:
            if (c >= 0 && c < 32) {
                char buf[10];
                sprintf_s(buf, "\\u%04x", c);
                output += buf;
            }
            else {
                output += c;
            }
            break;
        }
    }
    output += "\"";
    return output;
}

void set_autorun(bool enable) {
    HKEY hKey;
    LONG lRes = RegCreateKeyExW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, 0, KEY_SET_VALUE | KEY_QUERY_VALUE, NULL, &hKey, NULL);
    if (lRes == ERROR_SUCCESS) {
        if (enable) {
            wchar_t szPath[MAX_PATH];
            GetModuleFileNameW(NULL, szPath, MAX_PATH);
            std::wstring val = L"\"" + std::wstring(szPath) + L"\" --autostart";
            RegSetValueExW(hKey, L"Aether", 0, REG_SZ, (BYTE*)val.c_str(), static_cast<DWORD>((val.size() + 1) * sizeof(wchar_t)));
        }
        else {
            RegDeleteValueW(hKey, L"Aether");
        }
        RegCloseKey(hKey);
    }
}

std::string GetConfig() {
    if (!fs::exists(CFG_FILE)) return "{}";
    try {
        std::ifstream f(CFG_FILE);
        if (!f.is_open()) return "{}";
        std::string str((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
        return str.empty() ? "{}" : str;
    }
    catch (...) {
        return "{}";
    }
}

void SaveConfig(const std::string& cfg_json) {
    try {
        fs::create_directories(CFG_FILE.parent_path());
        std::ofstream f(CFG_FILE, std::ios::trunc);
        if (f.is_open()) {
            f << cfg_json;
            f.close();
        }

        std::string customDomains = get_json_string(cfg_json, "custom_domains");

        fs::create_directories(FILES);
        std::ofstream f_custom(CUSTOM_HOSTS, std::ios::trunc);

        if (f_custom.is_open()) {
            if (!customDomains.empty()) {
                std::stringstream ss(customDomains);
                std::string item;
                while (std::getline(ss, item, ':')) {
                    std::stringstream ss2(item);
                    std::string subItem;
                    while (std::getline(ss2, subItem, ',')) {
                        size_t first = subItem.find_first_not_of(" \t\r\n");
                        size_t last = subItem.find_last_not_of(" \t\r\n");
                        if (first != std::string::npos && last != std::string::npos) {
                            f_custom << subItem.substr(first, (last - first + 1)) << "\n";
                        }
                    }
                }
            }
            f_custom.close();
        }
    }
    catch (...) {}

    bool autorun = get_json_bool(cfg_json, "autorun", false);
    set_autorun(autorun);
}