#include "ProcessManager.h"
#include "Config.h"
#include "Strategy.h"
#include "Resource.h"
#include <tlhelp32.h>
#include <thread>
#include <fstream>
#include <windns.h>

#pragma comment(lib, "dnsapi.lib")

fs::path find_exe(const fs::path& root) {
    try {
        if (!fs::exists(root)) return "";
        for (const auto& entry : fs::recursive_directory_iterator(root, fs::directory_options::skip_permission_denied)) {
            if (entry.is_regular_file() && entry.path().filename() == "AetherWS.exe") {
                return entry.path();
            }
        }
    }
    catch (...) {}
    return "";
}

bool IsWinwsRunning() {
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnap == INVALID_HANDLE_VALUE) return false;
    PROCESSENTRY32W pe;
    pe.dwSize = sizeof(pe);
    bool running = false;
    if (Process32FirstW(hSnap, &pe)) {
        do {
            if (_wcsicmp(pe.szExeFile, L"AetherWS.exe") == 0) {
                running = true;
                break;
            }
        } while (Process32NextW(hSnap, &pe));
    }
    CloseHandle(hSnap);
    return running;
}

void run_cmd_silent(const std::string& cmd) {
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;
    ZeroMemory(&pi, sizeof(pi));
    std::string command_line = "cmd.exe /c " + cmd;
    char* cl = _strdup(command_line.c_str());
    if (CreateProcessA(NULL, cl, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi)) {
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    free(cl);
}

void KillProcessByName(const wchar_t* filename) {
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnap == INVALID_HANDLE_VALUE) return;

    PROCESSENTRY32W pe;
    pe.dwSize = sizeof(pe);

    if (Process32FirstW(hSnap, &pe)) {
        do {
            if (_wcsicmp(pe.szExeFile, filename) == 0) {
                HANDLE hProc = OpenProcess(PROCESS_TERMINATE, FALSE, pe.th32ProcessID);
                if (hProc) {
                    TerminateProcess(hProc, 0);
                    CloseHandle(hProc);
                }
            }
        } while (Process32NextW(hSnap, &pe));
    }
    CloseHandle(hSnap);
}

typedef BOOL(WINAPI* pDnsFlushResolverCacheFunc)();

void WarmupNetworkAndDns() {
    HMODULE hDnsApi = LoadLibraryA("dnsapi.dll");
    if (hDnsApi) {
        pDnsFlushResolverCacheFunc DnsFlushResolverCache =
            (pDnsFlushResolverCacheFunc)GetProcAddress(hDnsApi, "DnsFlushResolverCache");
        if (DnsFlushResolverCache) {
            DnsFlushResolverCache();
        }
        FreeLibrary(hDnsApi);
    }

    std::thread([]() {
        run_cmd_silent("ipconfig /flushdns >nul 2>&1");
        run_cmd_silent("powershell -WindowStyle Hidden -Command \"try { (New-Object Net.Sockets.TcpClient).ConnectAsync('discord.com', 443).Wait(300) } catch {}\"");
        }).detach();
}

void SetSystemDns(const std::string& mode) {
    std::thread([mode]() {
        if (mode == "cloudflare") {
            run_cmd_silent("powershell -WindowStyle Hidden -Command \"Get-NetAdapter | Where-Object {$_.Status -eq 'Up'} | Set-DnsClientServerAddress -ServerAddresses ('1.1.1.1','1.0.0.1')\"");
        }
        else if (mode == "adguard") {
            run_cmd_silent("powershell -WindowStyle Hidden -Command \"Get-NetAdapter | Where-Object {$_.Status -eq 'Up'} | Set-DnsClientServerAddress -ServerAddresses ('94.140.14.14','94.140.15.15')\"");
        }
        else if (mode == "google") {
            run_cmd_silent("powershell -WindowStyle Hidden -Command \"Get-NetAdapter | Where-Object {$_.Status -eq 'Up'} | Set-DnsClientServerAddress -ServerAddresses ('8.8.8.8','8.8.4.4')\"");
        }
        else {
            run_cmd_silent("powershell -WindowStyle Hidden -Command \"Get-NetAdapter | Where-Object {$_.Status -eq 'Up'} | Set-DnsClientServerAddress -ResetServerAddresses\"");
        }

        run_cmd_silent("ipconfig /flushdns >nul 2>&1");
        WarmupNetworkAndDns();
        }).detach();
}

void StopBypassAndDriver() {
    KillProcessByName(L"AetherWS.exe");
    KillProcessByName(L"goodbyedpi.exe");
    std::thread([]() {
        run_cmd_silent("sc stop WinDivert >nul 2>&1");
        run_cmd_silent("sc stop WinDivert14 >nul 2>&1");
        }).detach();

    WarmupNetworkAndDns();
}

void PreloadDriver() {
    std::thread([]() {
        run_cmd_silent("sc start WinDivert >nul 2>&1");
        run_cmd_silent("sc start WinDivert14 >nul 2>&1");
        }).detach();
}

bool ExtractResource(int resourceId, const fs::path& outputPath) {
    HMODULE hModule = GetModuleHandle(NULL);
    HRSRC hRes = FindResource(hModule, MAKEINTRESOURCE(resourceId), RT_RCDATA);
    if (!hRes) return false;

    HGLOBAL hData = LoadResource(hModule, hRes);
    if (!hData) return false;

    DWORD size = SizeofResource(hModule, hRes);
    char* pData = (char*)LockResource(hData);
    if (!pData || size == 0) return false;

    std::ofstream f(outputPath, std::ios::binary);
    if (!f.is_open()) return false;

    f.write(pData, size);
    f.close();
    return true;
}

void InitFiles(bool force) {
    StopBypassAndDriver();
    Sleep(200);

    fs::create_directories(ROOT);
    fs::create_directories(FILES);
    for (const auto& p : { EX_HOSTS, EX_IPS }) {
        if (!fs::exists(p)) {
            std::ofstream f(p);
        }
    }
    fs::path exe = find_exe(ROOT);
    if (!exe.empty() && !force) {
        return;
    }

    fs::path zip_path = ROOT / "Aether 1.4.zip";

    if (ExtractResource(201, zip_path)) {
        std::string cmd = "powershell -WindowStyle Hidden -Command \""
            "Expand-Archive -Path '" + zip_path.string() + "' -DestinationPath '" + ROOT.string() + "' -Force; "
            "Remove-Item '" + zip_path.string() + "' -Force -ErrorAction SilentlyContinue\"";
        run_cmd_silent(cmd);
    }
}
void RunBypass(const std::string& stratName) {
    StopBypassAndDriver();

    fs::path exe = find_exe(ROOT);
    if (exe.empty()) {
        InitFiles(true);
        exe = find_exe(ROOT);
        if (exe.empty()) return;
    }

    std::string extraArgs = "";
    if (fs::exists(EX_HOSTS) && fs::file_size(EX_HOSTS) > 0) {
        extraArgs += " --hostlist-exclude=\"" + EX_HOSTS.string() + "\"";
    }
    if (fs::exists(EX_IPS) && fs::file_size(EX_IPS) > 0) {
        extraArgs += " --ipset-exclude=\"" + EX_IPS.string() + "\"";
    }

    std::string stratArgs = BuildStrategyCommandLine(stratName, ROOT);
    std::string fullCmd = "\"" + exe.string() + "\" " + extraArgs + " " + stratArgs;

    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;
    ZeroMemory(&pi, sizeof(pi));

    char* cl = _strdup(fullCmd.c_str());
    if (CreateProcessA(NULL, cl, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, exe.parent_path().string().c_str(), &si, &pi)) {
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    free(cl);

    WarmupNetworkAndDns();
}