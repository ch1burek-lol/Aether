#pragma once
#include <windows.h>
#include <wrl.h>
#include <WebView2.h>
#include <string>

using namespace Microsoft::WRL;

extern ComPtr<ICoreWebView2Controller> g_controller;
extern ComPtr<ICoreWebView2> g_webView;

void InitializeWebView(HWND hWnd);
void HandleWebMessage(const std::wstring& msg);