#include "WebViewHandler.h"
#include "Config.h"
#include "ProcessManager.h"
#include "Strategy.h"
#include "html.h"
#include <thread>
#include <fstream>

ComPtr<ICoreWebView2Controller> g_controller;
ComPtr<ICoreWebView2> g_webView;

extern HWND g_hWnd;
void RemoveTrayIcon();

void HandleWebMessage(const std::wstring& msg) {
    std::wstring id = get_json_string_w(msg, L"id");
    std::wstring action = get_json_string_w(msg, L"action");
    std::wstring data = get_json_string_w(msg, L"data");
    std::wstring result = L"";

    if (action == L"cpp_Minimize") {
        ShowWindow(g_hWnd, SW_MINIMIZE);
    }
    else if (action == L"cpp_OpenUrl") {
        ShellExecuteW(NULL, L"open", data.c_str(), NULL, NULL, SW_SHOWNORMAL);
    }
    else if (action == L"cpp_Run") {
        std::string bat_name = WstringToUtf8(data);
        RunBypass(bat_name);

        std::string stratTitle = bat_name;
        for (const auto& item : G_STRATEGIES) {
            if (item.keyName == bat_name) {
                stratTitle = WstringToUtf8(item.titleW);
                break;
            }
        }

        std::string msg = "AetherWS успешно подключен.\nАктивная стратегия: " + stratTitle;

        extern void ShowTrayNotification(const std::wstring & title, const std::wstring & message);
        ShowTrayNotification(L"", Utf8ToWstring(msg));
    }
    else if (action == L"cpp_DragWindow") {
        ReleaseCapture();
        SendMessage(g_hWnd, WM_SYSCOMMAND, SC_MOVE | HTCAPTION, 0);
    }
    else if (action == L"cpp_Kill") {
        StopBypassAndDriver();
    }
    else if (action == L"cpp_Quit") {
        std::string cfg_json = GetConfig();
        bool minimize_to_tray = get_json_bool(cfg_json, "tray", true);
        if (minimize_to_tray) {
            ShowWindow(g_hWnd, SW_HIDE);
        }
        else {
            bool kill_on_exit = get_json_bool(cfg_json, "kill_on_exit", true);
            if (kill_on_exit) {
                StopBypassAndDriver();
            }
            RemoveTrayIcon();
            PostQuitMessage(0);
        }
    }
    else if (action == L"cpp_IsRunning") {
        result = IsWinwsRunning() ? L"true" : L"false";
    }
    else if (action == L"cpp_CheckInstall") {
        if (g_webView) {
            g_webView->ExecuteScript(L"window.installationComplete();", nullptr);
        }
    }
    else if (action == L"cpp_GetStrats") {
        result = Utf8ToWstring(escape_json_string(GetStratsJson()));
    }
    else if (action == L"cpp_GetConfig") {
        result = Utf8ToWstring(escape_json_string(GetConfig()));
    }
    else if (action == L"cpp_SaveConfig") {
        std::string cfg_json = WstringToUtf8(data);
        SaveConfig(cfg_json);
    }
    else if (action == L"cpp_SetDns") {
        std::string dnsMode = WstringToUtf8(data);
        SetSystemDns(dnsMode);
    }
    else if (action == L"cpp_ReadFile") {
        std::string type = WstringToUtf8(data);
        fs::path p = (type == "hosts") ? EX_HOSTS : EX_IPS;
        if (fs::exists(p)) {
            std::ifstream f(p);
            std::string str((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
            result = Utf8ToWstring(escape_json_string(str));
        }
        else {
            result = L"\"\"";
        }
    }
    else if (action == L"cpp_WriteFile") {
        std::string raw_json = WstringToUtf8(data);
        std::string type = get_json_string(raw_json, "type");
        std::string content = get_json_string(raw_json, "content");
        fs::path p = (type == "hosts") ? EX_HOSTS : EX_IPS;
        std::ofstream f(p);
        if (f.is_open()) {
            f << content;
        }
    }

    if (g_webView) {
        std::wstring js = L"window.cpp_receive('" + id + L"', " + result + L");";
        if (result.empty()) {
            js = L"window.cpp_receive('" + id + L"', null);";
        }
        g_webView->ExecuteScript(js.c_str(), nullptr);
    }
}

void InitializeWebView(HWND hWnd) {
    CreateCoreWebView2EnvironmentWithOptions(
        nullptr, nullptr, nullptr,
        Callback<ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler>(
            [hWnd](HRESULT result, ICoreWebView2Environment* env) -> HRESULT {
                if (FAILED(result)) return result;
                env->CreateCoreWebView2Controller(hWnd,
                    Callback<ICoreWebView2CreateCoreWebView2ControllerCompletedHandler>(
                        [hWnd](HRESULT result, ICoreWebView2Controller* controller) -> HRESULT {
                            if (FAILED(result)) return result;
                            g_controller = controller;
                            g_controller->get_CoreWebView2(&g_webView);

                            RECT bounds;
                            GetClientRect(hWnd, &bounds);
                            g_controller->put_Bounds(bounds);

                            ComPtr<ICoreWebView2Settings> settings;
                            g_webView->get_Settings(&settings);
                            if (settings) {
                                settings->put_AreDevToolsEnabled(FALSE);
                                settings->put_AreDefaultContextMenusEnabled(FALSE);
                                settings->put_IsStatusBarEnabled(FALSE);
                            }

                            ComPtr<ICoreWebView2_3> webView3;
                            if (SUCCEEDED(g_webView.As(&webView3))) {
                                webView3->SetVirtualHostNameToFolderMapping(
                                    L"aether.local",
                                    L"C:\\Aether\\Aether 1.4\\webview",
                                    COREWEBVIEW2_HOST_RESOURCE_ACCESS_KIND_ALLOW
                                );
                            }

                            std::wstring w_html = Utf8ToWstring(HTML_CONTENT);
                            g_webView->NavigateToString(w_html.c_str());

                            EventRegistrationToken token;
                            g_webView->add_WebMessageReceived(
                                Callback<ICoreWebView2WebMessageReceivedEventHandler>(
                                    [](ICoreWebView2* sender, ICoreWebView2WebMessageReceivedEventArgs* args) -> HRESULT {
                                        LPWSTR messageRaw = nullptr;
                                        args->TryGetWebMessageAsString(&messageRaw);
                                        if (messageRaw) {
                                            std::wstring msg(messageRaw);
                                            CoTaskMemFree(messageRaw);
                                            HandleWebMessage(msg);
                                        }
                                        return S_OK;
                                    }).Get(), &token);

                            std::thread([]() {
                                fs::path exe = find_exe(ROOT);
                                bool wasFirstInstall = exe.empty();

                                if (wasFirstInstall) {
                                    InitFiles(true);
                                }
                                else {
                                    InitFiles(false);
                                }

                                Sleep(300);

                                if (g_webView) {
                                    if (wasFirstInstall) {
                                        std::wstring w_html = Utf8ToWstring(HTML_CONTENT);
                                        g_webView->NavigateToString(w_html.c_str());
                                        Sleep(200);
                                    }
                                    g_webView->ExecuteScript(L"window.installationComplete();", nullptr);
                                }
                                }).detach();

                            return S_OK;
                        }).Get());
                return S_OK;
            }).Get());
}