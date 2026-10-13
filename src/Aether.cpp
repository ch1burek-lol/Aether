#include <windows.h>
#include <dwmapi.h>
#include "Resource.h"
#include "Config.h"
#include "Strategy.h"
#include "ProcessManager.h"
#include "WebViewHandler.h"

#pragma comment(lib, "dwmapi.lib")
#pragma comment(lib, "WebView2Loader.dll.lib")
#pragma comment(lib, "comctl32.lib")

#define WM_TRAYICON  (WM_USER + 2)
#define ID_TRAY_OPEN 1001
#define ID_TRAY_EXIT 1002

#define ID_TRAY_STOP        1003
#define ID_STRAT_BASE       2000

HWND g_hWnd = NULL;
NOTIFYICONDATAW g_nid = { sizeof(g_nid) };
HINSTANCE g_hInstance = NULL;

void ShowTrayNotification(const std::wstring& title, const std::wstring& message) {
    NOTIFYICONDATAW nid = { sizeof(NOTIFYICONDATAW) };
    nid.hWnd = g_hWnd;
    nid.uID = 1;
    nid.uFlags = NIF_INFO;
    nid.dwInfoFlags = NIIF_USER | NIIF_LARGE_ICON;
    nid.hBalloonIcon = LoadIcon(g_hInstance, MAKEINTRESOURCE(IDI_WAVEX));
    wcscpy_s(nid.szInfoTitle, title.c_str());
    wcscpy_s(nid.szInfo, message.c_str());
    Shell_NotifyIconW(NIM_MODIFY, &nid);
}

void AddTrayIcon(HWND hWnd) {
    ZeroMemory(&g_nid, sizeof(NOTIFYICONDATAW));
    g_nid.cbSize = sizeof(NOTIFYICONDATAW);
    g_nid.hWnd = hWnd;
    g_nid.uID = 1;
    g_nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    g_nid.uCallbackMessage = WM_TRAYICON;
    g_nid.hIcon = LoadIcon(g_hInstance, MAKEINTRESOURCE(IDI_WAVEX));
    wcscpy_s(g_nid.szTip, L"Aether DPI");
    Shell_NotifyIconW(NIM_ADD, &g_nid);
}

void RemoveTrayIcon() {
    Shell_NotifyIconW(NIM_DELETE, &g_nid);
}

void ShowTrayMenu(HWND hWnd) {
    POINT pt;
    GetCursorPos(&pt);
    HMENU hMenu = CreatePopupMenu();

    InsertMenuW(hMenu, 0, MF_BYPOSITION | MF_STRING, ID_TRAY_OPEN, L"Открыть Aether");

    std::string cfgJson = GetConfig();
    std::string activeStrat = get_json_string(cfgJson, "last_strat");
    if (activeStrat.empty()) activeStrat = "discord";
    bool running = IsWinwsRunning();

    HMENU hSubMenu = CreatePopupMenu();
    for (size_t i = 0; i < G_STRATEGIES.size(); ++i) {
        UINT flags = MF_BYPOSITION | MF_STRING;
        if (running && G_STRATEGIES[i].keyName == activeStrat) {
            flags |= MF_CHECKED;
        }
        InsertMenuW(hSubMenu, static_cast<UINT>(i), flags, ID_STRAT_BASE + static_cast<UINT>(i), G_STRATEGIES[i].titleW.c_str());
    }
    InsertMenuW(hMenu, 1, MF_BYPOSITION | MF_POPUP, (UINT_PTR)hSubMenu, L"Стратегии обхода");

    if (running) {
        InsertMenuW(hMenu, 2, MF_BYPOSITION | MF_STRING, ID_TRAY_STOP, L"Остановить обход");
    }

    InsertMenuW(hMenu, 3, MF_BYPOSITION | MF_SEPARATOR, 0, NULL);
    InsertMenuW(hMenu, 4, MF_BYPOSITION | MF_STRING, ID_TRAY_EXIT, L"Закрыть");

    SetForegroundWindow(hWnd);
    TrackPopupMenu(hMenu, TPM_RIGHTALIGN | TPM_BOTTOMALIGN, pt.x, pt.y, 0, hWnd, NULL);
    DestroyMenu(hMenu);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_SIZE: {
        if (g_controller) {
            RECT bounds;
            GetClientRect(hWnd, &bounds);
            g_controller->put_Bounds(bounds);
        }
        break;
    }
    case WM_TRAYICON: {
        if (lParam == WM_RBUTTONUP) {
            ShowTrayMenu(hWnd);
        }
        else if (lParam == WM_LBUTTONUP) {
            ShowWindow(hWnd, SW_SHOW);
            SetForegroundWindow(hWnd);
        }
        break;
    }
    case WM_COMMAND: {
        int wmId = LOWORD(wParam);
        if (wmId == ID_TRAY_OPEN) {
            ShowWindow(hWnd, SW_SHOW);
            SetForegroundWindow(hWnd);
        }
        else if (wmId == ID_TRAY_STOP) {
            StopBypassAndDriver();
            if (g_webView) {
                g_webView->ExecuteScript(L"if(window.syncUiState) window.syncUiState();", nullptr);
            }
        }
        else if (wmId >= ID_STRAT_BASE && wmId < ID_STRAT_BASE + (int)G_STRATEGIES.size()) {
            int stratIdx = wmId - ID_STRAT_BASE;
            std::string stratName = G_STRATEGIES[stratIdx].keyName;

            std::string cfgJson = GetConfig();
            SaveConfig("{\"last_strat\":\"" + stratName + "\"}");

            RunBypass(stratName);
            if (g_webView) {
                g_webView->ExecuteScript(L"if(window.syncUiState) window.syncUiState();", nullptr);
            }
        }
        else if (wmId == ID_TRAY_EXIT) {
            StopBypassAndDriver();
            RemoveTrayIcon();
            PostQuitMessage(0);
        }
        break;
    }
    case WM_DESTROY:
        RemoveTrayIcon();
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
    g_hInstance = hInstance;
    PreloadDriver();
    InitFiles(false);
    std::string cmdArgs = lpCmdLine ? lpCmdLine : "";
    bool isAutoStart = (cmdArgs.find("--autostart") != std::string::npos);

    WNDCLASSEXW wcex = { sizeof(WNDCLASSEXW) };
    wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DROPSHADOW;
    wcex.lpfnWndProc = WndProc;
    wcex.hInstance = hInstance;
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszClassName = L"AetherWindow";
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WAVEX));
    wcex.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SMALL));
    RegisterClassExW(&wcex);

    g_hWnd = CreateWindowExW(
        0,
        L"AetherWindow",
        L"Aether",
        WS_POPUP,
        CW_USEDEFAULT, CW_USEDEFAULT, 600, 420,
        NULL, NULL, hInstance, NULL
    );
    if (!g_hWnd) return 0;

    AddTrayIcon(g_hWnd);

    std::string cfgJson = GetConfig();
    bool autorunEnabled = get_json_bool(cfgJson, "autorun", false);
    set_autorun(autorunEnabled);
    
    if (isAutoStart) {
        std::string lastStrat = get_json_string(cfgJson, "last_strat");
        if (lastStrat.empty()) lastStrat = "discord.bat";
        RunBypass(lastStrat);
    }

    DWORD attribute = 33;
    DWORD preference = 2;
    DwmSetWindowAttribute(g_hWnd, attribute, &preference, sizeof(preference));

    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    SetWindowPos(g_hWnd, NULL, (screenWidth - 600) / 2, (screenHeight - 420) / 2, 600, 420, SWP_NOZORDER);

    InitializeWebView(g_hWnd);

    if (!isAutoStart) {
        ShowWindow(g_hWnd, SW_SHOW);
        UpdateWindow(g_hWnd);
    }

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}