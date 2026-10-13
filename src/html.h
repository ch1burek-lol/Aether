#pragma once
#include <string>

const std::string HTML_CONTENT = R"rawhtml(
<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<title>Aether</title>
<style>

@font-face {
    font-family: 'icons';
    src: url('https://aether.local/icons.ttf') format('truetype');
    font-weight: normal;
    font-style: normal;
}

@font-face {
    font-family: 'Inter';
    src: url('https://aether.local/Inter.ttf') format('truetype');
    font-weight: 100 900;
    font-style: normal;
}

@font-face {
    font-family: 'Unbounded';
    src: url('https://aether.local/Unbounded.ttf') format('truetype');
    font-weight: 100 900;
    font-style: normal;
}

.icon {
    font-family: 'icons' !important;
    font-style: normal;
    font-weight: normal;
    display: inline-block;
    font-size: 16px;
    line-height: 1;
}

:root {
    --bg: #f3ebe3;
    --card-bg: #ffffff;
    --g: rgba(0,0,0,0.03);
    --gb: rgba(0,0,0,0.06);
    --t: #1c1917;
    --td: #78716c;
    --ac: #0059FF;
    --warn: #f59e0b;
    --err: #ef4444;
    --rad: 26px;
}

* { 
    box-sizing: border-box; 
    user-select: none; 
    outline: none; 
}

body {
    background: var(--bg);
    color: var(--t);
    font-family: 'Inter', sans-serif;
    margin: 0;
    height: 100vh;
    overflow: hidden;
}

.tb {
    position: absolute;
    top: 0; left: 0;
    width: 100%; height: 46px;
    z-index: 4000;
    display: flex;
    justify-content: space-between;
    align-items: center;
    padding: 0 15px;
    background: transparent; 
    cursor: default;
}

.title-pill {
    position: absolute;
    left: 15px;
    top: 7px;
    height: 40px;
    display: flex;
    align-items: center;
    background: #ffffff;
    padding: 4px 14px;
    border-radius: 30px;
    box-shadow: 0 4px 20px rgba(0, 0, 0, 0.06);
    border: 1px solid rgba(0, 0, 0, 0.05);
}

.screen-title {
    font-family: 'Inter', sans-serif;
    font-size: 13px;
    font-weight: 600;
    color: #1c1917;
    pointer-events: none;
    line-height: 1;
    white-space: nowrap;
}

.nav-pill {
    position: absolute;
    left: 50%;
    top: 7px;
    transform: translateX(-50%);
    display: flex;
    align-items: center;
    gap: 4px;
    background: #ffffff;
    padding: 4px 6px;
    border-radius: 30px;
    box-shadow: 0 4px 20px rgba(0, 0, 0, 0.06);
    border: 1px solid rgba(0, 0, 0, 0.05);
}

.nav-btn {
    width: 32px;
    height: 32px;
    border-radius: 50%;
    display: flex;
    align-items: center;
    justify-content: center;
    cursor: pointer;
    color: #78716c;
    transition: all 0.2s cubic-bezier(0.25, 1, 0.5, 1);
}

.nav-btn .icon {
    font-size: 15px;
}

.nav-btn:hover {
    background: #f3ebe3;
    color: #1c1917;
}

.nav-btn.active {
    background: rgba(0, 89, 255, 0.12);
    color: #0059FF;
}

.win-pill {
    position: absolute;
    right: 10px;
    top: 7px;
    display: flex;
    align-items: center;
    gap: 4px;
    background: #ffffff;
    padding: 4px 6px;
    border-radius: 30px;
    box-shadow: 0 4px 20px rgba(0, 0, 0, 0.06);
    border: 1px solid rgba(0, 0, 0, 0.05);
}

.wb-btn {
    width: 32px;
    height: 32px;
    border-radius: 50%;
    display: flex;
    align-items: center;
    justify-content: center;
    cursor: pointer;
    color: #78716c;
    transition: all 0.2s cubic-bezier(0.25, 1, 0.5, 1);
}

.wb-btn svg {
    width: 14px;
    height: 14px;
    fill: currentColor;
    transition: fill 0.2s;
}

.wb-btn.mn:hover {
    background: rgba(245, 158, 11, 0.15);
    color: #d97706;
}

.wb-btn.cl:hover {
    background: rgba(239, 68, 68, 0.15);
    color: #dc2626;
}

.wb-btn:active {
    transform: scale(0.92);
}

.wrap {
    height: 100%;
    border: 1px solid rgba(0,0,0,0.05);
    padding: 20px;
    padding-top: 55px;
    display: flex;
    flex-direction: column;
    position: relative;
    overflow: hidden;
    isolation: isolate;
    background: var(--bg);
}

.main {
    position: relative;
    z-index: 10;
    height: 100%;
    width: 100%;
    opacity: 0;
    transform: scale(0.97);
    transition: opacity 0.8s cubic-bezier(0.25, 1, 0.5, 1), transform 0.8s cubic-bezier(0.25, 1, 0.5, 1);
}

.main.visible {
    opacity: 1;
    transform: scale(1);
}

.btn-power-wrapper {
    position: absolute;
    left: 50%;
    top: 48%;
    transform: translate(-50%, -50%);
    width: 180px;
    height: 180px;
    border-radius: 50%;
    background: #ebe3db;
    display: flex;
    align-items: center;
    justify-content: center;
    box-shadow: 
        inset 0 2px 5px rgba(255, 255, 255, 0.9),
        inset 0 -2px 5px rgba(0, 0, 0, 0.06),
        0 12px 30px rgba(0, 0, 0, 0.07);
}

.btn-power {
    width: 130px;
    height: 130px;
    border-radius: 50%;
    background: #ffffff;
    border: none;
    border-top: 1.5px solid rgba(255, 255, 255, 1);
    color: #a8a29e;
    cursor: pointer;
    display: flex;
    align-items: center;
    justify-content: center;
    padding: 0;
    box-shadow: 
        0 14px 28px rgba(0, 0, 0, 0.08),
        0 6px 12px rgba(0, 0, 0, 0.04);
    transition: color 0.25s ease, box-shadow 0.25s ease, transform 0.15s ease;
}

.btn-power svg {
    width: 54px;
    height: 54px;
    fill: currentColor;
    display: block;
    pointer-events: none;
    transition: filter 0.25s ease;
}

.btn-power:hover {
    color: #1c1917;
    box-shadow: 
        0 18px 35px rgba(0, 0, 0, 0.12),
        0 8px 15px rgba(0, 0, 0, 0.06);
}

.btn-power:active {
    transform: scale(0.97);
}

.btn-power.stop {
    color: #0059FF;
    box-shadow: 
        0 14px 28px rgba(0, 89, 255, 0.2),
        0 6px 12px rgba(0, 89, 255, 0.12);
}

.btn-power.stop svg {
    filter: drop-shadow(0 0 12px rgba(0, 89, 255, 0.65));
}

.action-container {
    position: absolute;
    bottom: 25px;
    left: 50%;
    transform: translateX(-50%);
    display: flex;
    flex-direction: column;
    align-items: center;
}

.preset-info {
    display: flex;
    align-items: center;
    gap: 6px;
    background: #ffffff;
    padding: 9px 17px;
    border-radius: 30px;
    box-shadow: 0 4px 20px rgba(0, 0, 0, 0.06);
    border: 1px solid rgba(0, 0, 0, 0.05);
    white-space: nowrap;
    transform: translateY(26px);
}

.preset-label {
    font-size: 14px;
    font-weight: 600;
    color: #78716c; 
    line-height: 1;
}

.preset-green {
    font-size: 14px;
    font-weight: 700;
    color: #0059FF; 
    line-height: 1;
}

.status-text {
    font-size: 14px;
    font-weight: 600;
    color: #78716c;
    letter-spacing: 0.2px;
    transition: all 0.25s cubic-bezier(0.25, 1, 0.5, 1);
    pointer-events: none;
    text-align: center;
    transform: translateY(-8px);
}

.status-text.active {
    color: #0059FF;
    text-shadow: 0 0 12px rgba(0, 89, 255, 0.35);
}

.modal {
    position: absolute;
    top: 0; left: 0;
    width: 100%; height: 100%;
    background: rgba(243, 235, 227, 0.95);
    backdrop-filter: blur(25px);
    -webkit-backdrop-filter: blur(25px);
    z-index: 2000;
    padding: 75px 25px 25px 25px;
    display: flex;
    flex-direction: column;
    opacity: 0;
    pointer-events: none;
    transition: opacity .3s cubic-bezier(0.25, 1, 0.5, 1);
}

.modal.act { 
    opacity: 1; 
    pointer-events: all; 
}

.modes-list {
    display: flex;
    flex-direction: column;
    gap: 8px;
    background: var(--card-bg);
    box-shadow: 0 10px 30px rgba(0, 0, 0, 0.04);
    border: 1px solid rgba(0, 0, 0, 0.06);
    border-radius: 20px;
    padding: 15px;
    overflow-y: auto;
    width: 100%;
    height: 100%;
}

.mode-item {
    padding: 12px 16px;
    border-radius: 14px;
    background: #ffffff;
    border: 1px solid rgba(0, 0, 0, 0.04);
    box-shadow: 0 4px 15px rgba(0, 0, 0, 0.02);
    display: flex;
    align-items: center;
    gap: 12px;
    cursor: pointer;
    transition: all 0.2s cubic-bezier(0.25, 1, 0.5, 1);
}

.mode-item:hover { 
    background: #fdfbf7;
    box-shadow: 0 6px 18px rgba(0, 0, 0, 0.04);
}

.mode-item.active {
    border-color: rgba(0, 89, 255, 0.35);
}

.mode-item.active .mode-title {
    color: #0059FF;
}

.mode-icon {
    font-size: 18px;
    color: #78716c;
    flex-shrink: 0;
}

.mode-item.active .mode-icon {
    color: #0059FF;
}

.mode-content {
    display: flex;
    flex-direction: column;
    gap: 2px;
    flex-grow: 1;
}

.mode-title {
    font-size: 13px;
    font-weight: 700;
    color: #1c1917;
    transition: color 0.2s;
}

.mode-desc {
    font-size: 11px;
    font-weight: 400;
    color: #78716c;
}

.mode-check {
    font-size: 16px;
    color: #0059FF;
    opacity: 0;
    transition: opacity 0.2s;
}

.mode-item.active .mode-check {
    opacity: 1;
}

.sw {
    width: 38px; height: 20px;
    background: #e7e0d8;
    border: 1px solid rgba(0,0,0,0.08);
    border-radius: 10px;
    position: relative;
    cursor: pointer;
    transition: .3s;
    flex-shrink: 0;
}

.sw::after {
    content: '';
    position: absolute;
    top: 2px; left: 2px;
    width: 14px; height: 14px;
    background: #fff;
    border-radius: 50%;
    box-shadow: 0 2px 4px rgba(0,0,0,0.15);
    transition: .3s;
}

.sw.chk { background: var(--ac); border-color: var(--ac); }
.sw.chk::after { transform: translateX(18px); }

.row {
    display: flex;
    align-items: center;
    justify-content: space-between;
    margin-bottom: 14px;
    padding-bottom: 12px;
    border-bottom: 1px solid rgba(0, 0, 0, 0.05);
}

.row-text {
    display: flex;
    flex-direction: column;
    gap: 3px;
}

.row-title {
    font-size: 13px;
    font-weight: 600;
    color: #1c1917;
}

.row-desc {
    font-size: 11px;
    font-weight: 400;
    color: #78716c;
}

.row-left {
    display: flex;
    align-items: center;
    gap: 12px;
}

.row-title {
    font-size: 13px;
    font-weight: 600;
    color: #1c1917;
}

.tooltip-text {
    font-size: 11px;
    font-weight: 600;
    color: #0059FF;
    background: rgba(0, 89, 255, 0.12);
    padding: 4px 10px;
    border-radius: 8px;
    opacity: 0;
    transform: translateX(-6px);
    pointer-events: none;
    transition: all 0.25s cubic-bezier(0.25, 1, 0.5, 1);
    white-space: nowrap;
}

.domain-input {
    width: 100%;
    height: 38px;
    padding: 8px 12px;
    border-radius: 10px;
    border: 1px solid rgba(0, 0, 0, 0.08);
    background: #fdfbf7;
    font-family: 'Inter', sans-serif;
    font-size: 12px;
    color: #1c1917;
    transition: 0.2s;
}

.domain-input:focus {
    border-color: #0059FF;
    background: #ffffff;
}

.dns-select {
    height: 36px;
    padding: 6px 12px;
    border-radius: 10px;
    border: 1px solid rgba(0, 0, 0, 0.08);
    background: #fdfbf7;
    font-family: 'Inter', sans-serif;
    font-size: 12px;
    font-weight: 600;
    color: #1c1917;
    cursor: pointer;
    transition: 0.2s;
}

.dns-select:focus {
    border-color: #0059FF;
    background: #ffffff;
}

.install-overlay {
    position: absolute;
    top: 0; left: 0;
    width: 100%; height: 100%;
    background: rgba(243, 235, 227, 0.95);
    backdrop-filter: blur(25px);
    -webkit-backdrop-filter: blur(25px);
    z-index: 5000;
    display: flex;
    flex-direction: column;
    align-items: center;
    justify-content: center;
    transition: opacity 0.6s cubic-bezier(0.25, 1, 0.5, 1), visibility 0.6s;
    opacity: 1;
    visibility: visible;
}

.install-overlay.hidden {
    opacity: 0;
    visibility: hidden;
    pointer-events: none;
}

.spinner {
    width: 48px;
    height: 48px;
    border: 3px solid rgba(0, 0, 0, 0.08);
    border-top: 3px solid #0059FF;
    border-radius: 50%;
    animation: spin 1s linear infinite;
    margin-bottom: 20px;
}

.install-text {
    font-family: 'Unbounded', sans-serif;
    font-size: 12px;
    font-weight: 600;
    color: #1c1917;
    letter-spacing: 1px;
    text-transform: uppercase;
    opacity: 0.9;
}

#modal-updates {
    padding: 0;
    overflow: hidden;
    position: absolute;
    top: 0; left: 0;
    width: 100%; height: 100%;
    background: var(--bg);
}

.updates-blur-top {
    position: absolute;
    top: 0;
    left: 0;
    width: 100%;
    height: 90px;
    background: linear-gradient(180deg, rgba(28, 25, 23, 0.45) 0%, rgba(28, 25, 23, 0.15) 60%, rgba(28, 25, 23, 0) 100%);
    z-index: 100;
    pointer-events: none;
}

.updates-list {
    display: flex;
    flex-direction: column;
    gap: 20px;
    padding: 62px 25px 30px 25px;
    overflow-y: auto;
    width: 100%;
    height: 100%;
    scroll-behavior: smooth;
}
.updates-list::-webkit-scrollbar {
    width: 4px;
}

.updates-list::-webkit-scrollbar-thumb {
    background: rgba(0, 0, 0, 0.12);
    border-radius: 10px;
}

.updates-list::-webkit-scrollbar-track {
    background: transparent;
}

.update-card {
    display: flex;
    flex-direction: column;
    gap: 10px;
    border-bottom: 1px solid rgba(0, 0, 0, 0.08);
    padding-bottom: 22px;
}

.update-card:last-child {
    border-bottom: none;
    padding-bottom: 15px;
}
.update-header {
    display: flex;
    justify-content: space-between;
    align-items: baseline;
}

.update-tag {
    font-family: 'Inter', sans-serif;
    font-size: 16px;
    font-weight: 800;
    color: #0059FF;
}

.update-date {
    font-size: 12px;
    font-weight: 500;
    color: #78716c;
}

.update-body {
    font-size: 13px;
    line-height: 1.6;
    color: #1c1917;
    white-space: pre-line;
    font-family: 'Inter', sans-serif;
}

.update-body b {
    font-weight: 700;
    color: #1c1917;
}

.btn-update-download {
    align-self: flex-start;
    background: #0059FF;
    color: #ffffff;
    border: none;
    padding: 7px 16px;
    border-radius: 12px;
    font-family: 'Inter', sans-serif;
    font-size: 12px;
    font-weight: 600;
    cursor: pointer;
    margin-top: 6px;
    box-shadow: 0 4px 12px rgba(0, 89, 255, 0.2);
    transition: background 0.2s ease, opacity 0.2s ease;
}

.btn-update-download:hover {
    background: #0047cc;
}

.btn-update-download:active {
    opacity: 0.85;
}

.hide-view {
    display: none !important;
}

@keyframes spin {
    0% { transform: rotate(0deg); }
    100% { transform: rotate(360deg); }
}

::-webkit-scrollbar { width: 0; }
</style>
</head>
<body>

<div class="wrap">
    <div id="install-overlay" class="install-overlay">
        <div class="spinner"></div>
        <div class="install-text">Установка компонентов</div>
    </div>

    <div class="tb">
    <div class="title-pill">
        <div class="screen-title" id="screen-title">Главная</div>
    </div>

    <div class="nav-pill">
            <div class="nav-btn active" id="nav-q" onclick="switchNav('home')"><span class="icon">q</span></div>
            <div class="nav-btn" id="nav-s" onclick="switchNav('strats')"><span class="icon">$</span></div>
            <div class="nav-btn" id="nav-e" onclick="switchNav('settings')"><span class="icon">&</span></div>
            <div class="nav-btn" id="nav-updates" onclick="switchNav('updates')"><span class="icon">w</span></div>
        </div>

        <div class="win-pill">
            <div class="wb-btn mn" onclick="window.runtime.WindowMinimise()" title="Свернуть">
                <svg viewBox="0 0 24 24"><path d="M19 13H5v-2h14v2z"/></svg>
            </div>
            <div class="wb-btn cl" onclick="window.runtime.Quit()" title="Закрыть">
                <svg viewBox="0 0 24 24"><path d="M19 6.41L17.59 5 12 10.59 6.41 5 5 6.41 10.59 12 5 17.59 6.41 19 12 13.41 17.59 19 19 17.59 13.41 12z"/></svg>
            </div>
        </div>
    </div>

<div id="cfg-modal" class="modal">
        <div class="modes-list" style="padding: 18px 20px;">
            <div class="row">
                <div class="row-text">
                    <span class="row-title">Автозапуск</span>
                    <span class="row-desc">Запускать Aether вместе с Windows</span>
                </div>
                <div class="sw" id="tg-auto" onclick="tSw('tg-auto')"></div>
            </div>

            <div class="row">
                <div class="row-text">
                    <span class="row-title">Сворачивать в трей</span>
                    <span class="row-desc">Прятать в трей у часов при закрытии окна</span>
                </div>
                <div class="sw" id="tg-tray" onclick="tSw('tg-tray')"></div>
            </div>

            <div class="row" style="flex-direction: column; align-items: stretch; gap: 8px; border-bottom: none; margin-bottom: 0; padding-bottom: 0;">
                <div style="display: flex; align-items: center; justify-content: space-between;">
                    <div class="row-text">
                        <span class="row-title">Пользовательские хосты</span>
                        <span class="row-desc">Индивидуальный список сайтов для обхода</span>
                    </div>
                    <div class="sw" id="tg-custom" onclick="tSw('tg-custom')"></div>
                </div>
                <input type="text" id="custom-domains-input" class="domain-input" placeholder="domain1.com:domain2.net" oninput="saveCustomDomains()">
            </div>

             <div class="row">
                <div class="row-text">
                    <span class="row-title">Безопасный DNS</span>
                    <span class="row-desc">Защита от подмены IP и ошибки NXDOMAIN</span>
                </div>
                <select id="sel-dns" class="dns-select" onchange="changeDns()">
                    <option value="disabled">Отключен</option>
                    <option value="cloudflare">Cloudflare (1.1.1.1)</option>
                    <option value="adguard">AdGuard (Без рекламы)</option>
                    <option value="google">Google (8.8.8.8)</option>
                </select>
            </div>
        </div>
    </div>

    <div id="modal-strats" class="modal">
        <div class="modes-list" id="modes-container"></div>
    </div>

<div id="modal-updates" class="modal">
        <div class="updates-blur-top"></div>
        <div class="updates-list" id="updates-container">
            <div class="updates-loading">
                <div class="spinner" style="width: 32px; height: 32px; margin: 0 auto 10px auto;"></div>
                <span>Загрузка обновлений с GitHub...</span>
            </div>
        </div>
    </div>

    <div class="main" id="view-home">
        <div class="btn-power-wrapper">
            <button class="btn-power" id="btn-run" onclick="tRun()">
                <svg viewBox="0 0 24 24">
                    <path d="M13 3h-2v10h2V3zm4.83 2.17l-1.42 1.42C17.99 7.86 19 9.81 19 12c0 3.87-3.13 7-7 7s-7-3.13-7-7c0-2.19 1.01-4.14 2.58-5.42L6.17 5.17C4.23 6.82 3 9.26 3 12c0 4.97 4.03 9 9 9s9-4.03 9-9c0-2.74-1.23-5.18-3.17-6.83z"/>
                </svg>
            </button>
        </div>

        <div class="action-container">
            <div class="status-text" id="status-hint">Нажмите для подключения</div>
            <input type="hidden" id="strat-v" value="">
            <div class="preset-info">
                <span class="preset-label">Текущая стратегия:</span>
                <span id="selected-strat-name" class="preset-green">Не выбран</span>
            </div>
        </div>
    </div>
</div>

<script>
window.cpp_resolves = {};

window.cpp_call = function(action, data) {
    return new Promise((resolve) => {
        const id = Math.random().toString();
        window.cpp_resolves[id] = resolve;
        window.chrome.webview.postMessage(JSON.stringify({id: id, action: action, data: data}));
    });
};

window.cpp_receive = function(id, result) {
    if (window.cpp_resolves[id]) {
        window.cpp_resolves[id](result);
        delete window.cpp_resolves[id];
    }
};

window.runtime = {
    WindowMinimise: function() { window.cpp_call("cpp_Minimize", ""); },
    Quit: function() { window.cpp_call("cpp_Quit", ""); }
};

window.go = {
    main: {
        App: {
            GetStrats: async function() {
                let res = await window.cpp_call("cpp_GetStrats", "");
                return JSON.parse(res);
            },
            GetConfig: async function() {
                let res = await window.cpp_call("cpp_GetConfig", "");
                try {
                    let parsed = JSON.parse(res);
                    if (typeof parsed === 'string') {
                        parsed = JSON.parse(parsed);
                    }
                    return parsed || {};
                } catch(e) {
                    return {};
                }
            },
            SaveConfig: async function(cfg) {
                await window.cpp_call("cpp_SaveConfig", JSON.stringify(cfg));
            },
            Run: async function(strat) {
                await window.cpp_call("cpp_Run", strat);
            },
            Kill: async function() {
                await window.cpp_call("cpp_Kill", "");
            }
        }
    }
};

let running = false;
let cfg = {};
let strats = {};

function switchNav(screen) {
    const homeView = document.getElementById('view-home');
    const cfgModal = document.getElementById('cfg-modal');
    const stratsModal = document.getElementById('modal-strats');
    const updatesModal = document.getElementById('modal-updates');

    cfgModal.classList.remove('act');
    stratsModal.classList.remove('act');
    if (updatesModal) updatesModal.classList.remove('act');
    
    document.getElementById('nav-q').classList.remove('active');
    document.getElementById('nav-s').classList.remove('active');
    document.getElementById('nav-e').classList.remove('active');
    const navUpdates = document.getElementById('nav-updates');
    if (navUpdates) navUpdates.classList.remove('active');

    const titleEl = document.getElementById('screen-title');

    if (screen === 'home') {
        homeView.classList.remove('hide-view'); 
        document.getElementById('nav-q').classList.add('active');
        titleEl.textContent = 'Главная';
    } else {
        homeView.classList.add('hide-view');

        if (screen === 'strats') {
            stratsModal.classList.add('act');
            document.getElementById('nav-s').classList.add('active');
            titleEl.textContent = 'Лист стратегий';
        } else if (screen === 'settings') {
            cfgModal.classList.add('act');
            document.getElementById('nav-e').classList.add('active');
            titleEl.textContent = 'Настройки';
        } else if (screen === 'updates') {
            if (updatesModal) updatesModal.classList.add('act');
            if (navUpdates) navUpdates.classList.add('active');
            titleEl.textContent = 'Список обновлений';
            fetchReleases();
        }
    }
}

window.installationComplete = function() {
    const overlay = document.getElementById('install-overlay');
    const mainNode = document.querySelector('.main');
    if (overlay) {
        overlay.classList.add('hidden');
    }
    if (mainNode) {
        mainNode.classList.add('visible');
    }
};

async function init() {
    if (!window.go || !window.go.main) {
        alert("Инициализация не удалась.");
        return;
    }

    fetchReleases();

    window.cpp_call("cpp_CheckInstall", "");

    try {
        strats = await window.go.main.App.GetStrats();
    } catch (e) {
        strats = {};
    }

    try {
        cfg = await window.go.main.App.GetConfig();
    } catch(e) {
        cfg = {};
    }

    renderModes();
    applyCfg();

    let isRunning = await window.cpp_call("cpp_IsRunning", "");
    if (isRunning === "true" || isRunning === true) {
        running = true;
        const btn = document.getElementById('btn-run');
        const hint = document.getElementById('status-hint');
        btn.classList.add('stop');
        if (hint) {
            hint.textContent = "Подключено";
            hint.classList.add('active');
        }
    }
    if (cfg && cfg.custom_domains) {
        document.getElementById('custom-domains-input').value = cfg.custom_domains;
    }
}

function renderModes() {
    const container = document.getElementById('modes-container');
    container.innerHTML = '';
    
    const savedStrat = (cfg && cfg.last_strat) ? cfg.last_strat : (strats[0] ? strats[0].key : 'discord');

    strats.forEach(item => {
        const div = document.createElement('div');
        div.className = 'mode-item';
        
        if (item.key === savedStrat) {
            div.classList.add('active');
            document.getElementById('strat-v').value = item.key;
            document.getElementById('selected-strat-name').textContent = item.title;
        }

        let iconHtml = '';
        const nameLower = item.title.toLowerCase();
        if (nameLower.includes('discord')) {
            iconHtml = '<span class="icon mode-icon">5</span>';
        } else if (nameLower.includes('youtube')) {
            iconHtml = '<span class="icon mode-icon">z</span>';
        } else if (nameLower.includes('custom')) {
            iconHtml = '<span class="icon mode-icon">f</span>';
        }

        div.innerHTML = `
            ${iconHtml}
            <div class="mode-content">
                <span class="mode-title">${item.title}</span>
                <span class="mode-desc">${item.desc}</span>
            </div>
            <span class="icon mode-check">3</span>
        `;
        
        div.onclick = async () => {
            document.querySelectorAll('.mode-item').forEach(e => e.classList.remove('active'));
            div.classList.add('active');
            document.getElementById('strat-v').value = item.key;
            document.getElementById('selected-strat-name').textContent = item.title;
            
            cfg.last_strat = item.key;
            await saveCfg(cfg);

            if (running) {
                await window.go.main.App.Run(item.key);
            }
        };
        container.appendChild(div);
    });
}

async function tRun() {
    const strat = document.getElementById('strat-v').value;
    if (!strat) return;
    const btn = document.getElementById('btn-run');
    const hint = document.getElementById('status-hint');

    if (!running) {
        await window.go.main.App.Run(strat);
        btn.classList.add('stop');
        if (hint) {
            hint.textContent = "Подключено";
            hint.classList.add('active');
        }
        running = true;
    } else {
        await window.go.main.App.Kill();
        btn.classList.remove('stop');
        if (hint) {
            hint.textContent = "Нажмите для подключения";
            hint.classList.remove('active');
        }
        running = false;
    }
}

async function tSw(id) {
    const el = document.getElementById(id);
    el.classList.toggle('chk');
    
    cfg.autorun = document.getElementById('tg-auto').classList.contains('chk');
    cfg.tray = document.getElementById('tg-tray').classList.contains('chk');
    cfg.custom_enabled = document.getElementById('tg-custom').classList.contains('chk');
    await saveCfg(cfg);
}

async function saveCfg(data) {
    cfg = data;
    let jsonStr = JSON.stringify(data);
    await window.cpp_call("cpp_SaveConfig", jsonStr);
}

function applyCfg() {
    if (cfg && cfg.autorun) document.getElementById('tg-auto').classList.add('chk');
    else document.getElementById('tg-auto').classList.remove('chk');

    if (!cfg || cfg.tray === undefined || cfg.tray === true) {
        document.getElementById('tg-tray').classList.add('chk');
    } else {
        document.getElementById('tg-tray').classList.remove('chk');
    }

    if (cfg && cfg.custom_enabled) {
        document.getElementById('tg-custom').classList.add('chk');
    } else {
        document.getElementById('tg-custom').classList.remove('chk');
    }

    if (cfg && cfg.custom_domains) {
        document.getElementById('custom-domains-input').value = cfg.custom_domains;
    }
    if (cfg && cfg.dns_mode) {
        document.getElementById('sel-dns').value = cfg.dns_mode;
    } else {
        document.getElementById('sel-dns').value = 'disabled';
    }
}

document.addEventListener('DOMContentLoaded', function() {
    init();

    const tb = document.querySelector('.tb');
    if (tb) {
        tb.addEventListener('mousedown', function(e) {
            if (e.target.closest('.win-pill') || e.target.closest('.nav-pill')) return;
            window.cpp_call("cpp_DragWindow", "");
        });
    }
});

let customDomainTimeout = null;
async function saveCustomDomains() {
    clearTimeout(customDomainTimeout);
    customDomainTimeout = setTimeout(async () => {
        const val = document.getElementById('custom-domains-input').value;
        cfg.custom_domains = val;
        
        if (val.trim().length > 0) {
            cfg.custom_enabled = true;
            document.getElementById('tg-custom').classList.add('chk');
        }

        await saveCfg(cfg);

        if (running) {
            const strat = document.getElementById('strat-v').value;
            await window.go.main.App.Run(strat);
        }
    }, 800);
}

let releasesCached = null;
let lastCheckTime = 0;

function formatMarkdown(text) {
    if (!text) return 'Описание отсутствует';
    
    let md = text;

    md = md.replace(/^(?:---|\*\*\*|___)\s*$/gm, '<hr style="border: none; border-top: 1px solid rgba(0,0,0,0.06); margin: 10px 0;">');


    md = md.replace(/^###\s+(.*$)/gim, '<div style="font-size: 13px; font-weight: 700; color: #1c1917; margin: 6px 0 2px 0;">$1</div>');
    md = md.replace(/^##\s+(.*$)/gim, '<div style="font-size: 14px; font-weight: 700; color: #1c1917; margin: 8px 0 3px 0;">$1</div>');
    md = md.replace(/^#\s+(.*$)/gim, '<div style="font-size: 15px; font-weight: 800; color: #0059FF; margin: 10px 0 4px 0;">$1</div>');

    md = md.replace(/\*\*(.*?)\*\*/g, '<b>$1</b>');
    md = md.replace(/__(.*?)__/g, '<b>$1</b>');

    md = md.replace(/~~(.*?)~~/g, '<del>$1</del>');

    md = md.replace(/(^|[^\*])\*(?!\*)(.*?)\*(?!\*)/g, '$1<i>$2</i>');
    md = md.replace(/(^|[^_])_(?!_)(.*?)_(?!_)/g, '$1<i>$2</i>');

    md = md.replace(/`([^`]+)`/g, '<code style="background: rgba(0,0,0,0.05); padding: 2px 5px; border-radius: 4px; font-family: monospace; font-size: 11px;">$1</code>');

    md = md.replace(/^\s*[\-\*]\s+(.*$)/gim, '<div style="display: flex; gap: 6px; margin: 2px 0;"><span style="color: #0059FF;">•</span><span>$1</span></div>');

    md = md.replace(/\[([^\]]+)\]\((https?:\/\/[^\)]+)\)/g, '<a href="javascript:void(0)" onclick="window.cpp_call(\'cpp_OpenUrl\', \'$2\')" style="color: #0059FF; text-decoration: underline;">$1</a>');

    return md.trim();
}

async function fetchReleases(force = false) {
    const now = Date.now();
    if (!force && releasesCached && (now - lastCheckTime < 60000)) {
        renderReleases(releasesCached);
        return;
    }

    const container = document.getElementById('updates-container');
    if (!releasesCached) {
        container.innerHTML = `
            <div class="updates-loading">
                <div class="spinner" style="width: 32px; height: 32px; margin: 0 auto 10px auto;"></div>
                <span>Загрузка обновлений с GitHub...</span>
            </div>`;
    }

    try {
        const response = await fetch('https://api.github.com/repos/ch1burek-lol/Aether/releases', {
            headers: { 'Accept': 'application/vnd.github.v3+json' }
        });
        if (!response.ok) throw new Error("GitHub rate limit or network error");
        
        const data = await response.json();
        releasesCached = data;
        lastCheckTime = Date.now();
        renderReleases(data);
    } catch (e) {
        if (!releasesCached) {
            container.innerHTML = `
                <div class="updates-loading" style="color: #ef4444;">
                    <span>Не удалось загрузить данные с GitHub</span>
                    <button class="btn-update-download" style="margin-top: 10px;" onclick="fetchReleases(true)">Повторить</button>
                </div>`;
        }
    }
}

function renderReleases(releases) {
    const container = document.getElementById('updates-container');
    if (!releases || releases.length === 0) {
        container.innerHTML = '<div class="updates-loading">Релизов пока нет</div>';
        return;
    }

    container.innerHTML = '';
    releases.forEach(rel => {
        const card = document.createElement('div');
        card.className = 'update-card';

        const dateStr = new Date(rel.published_at).toLocaleDateString('ru-RU', {
            day: 'numeric', month: 'short', year: 'numeric'
        });

        const formattedBody = formatMarkdown(rel.body);

        card.innerHTML = `
            <div class="update-header">
                <span class="update-tag">${rel.name || rel.tag_name}</span>
                <span class="update-date">${dateStr}</span>
            </div>
            <div class="update-body">${formattedBody}</div>
<button class="btn-update-download" onclick="window.cpp_call('cpp_OpenUrl', '${rel.html_url}')">Перейти на GitHub</button>
        `;
        container.appendChild(card);
    });
}
async function changeDns() {
    const dnsVal = document.getElementById('sel-dns').value;
    cfg.dns_mode = dnsVal;
    await saveCfg(cfg);
    await window.cpp_call("cpp_SetDns", dnsVal);
}
</script>
</body>
</html>
)rawhtml";