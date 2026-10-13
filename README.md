# ⚡ Aether DPI (formerly WaveX)

<p align="center">
  <img src="https://img.shields.io/badge/Platform-Windows%2010%20%7C%2011-black?style=for-the-badge&logo=windows" alt="Platform">
  <img src="https://img.shields.io/badge/Language-C%2B%2B%20%2F%20WebView2-blue?style=for-the-badge&logo=c%2B%2B" alt="Language">
  <img src="https://img.shields.io/badge/License-MIT-green?style=for-the-badge" alt="License">
</p>

<p align="center">
  <b>Aether DPI</b> — это мощный, автономный и быстрый инструмент с современным интерфейсом для обхода блокировок DPI. Разработан на базе C++ WinAPI и Microsoft Edge WebView2.
</p>

---

## 🇷🇺 Описание (RU)

**Aether** восстанавливает стабильный доступ к популярным сервисам, серверам Discord (включая голосовые каналы RTC), потоковому видео на YouTube в 4K и другим заблокированным веб-ресурсам без необходимости использования тяжелых VPN-сервисов.

### 🔥 Главные особенности:

* **⚡ Полная автономность:** Все необходимые компоненты, драйверы и списки вшиты прямо в тело `.exe`. Никаких долгих загрузок из сети при первом запуске — распаковка занимает 0.1 секунды.
* **🚫 Без .bat файлов и консолей:** Все стратегии и параметры командной строки zapret зашиты напрямую в C++ движок. Процесс стартует мгновенно без вызова `cmd.exe` и мусора на диске.
* **🎨 Премиальный UI:** Чистый, минималистичный неоморфный интерфейс на базе WebView2 с плавной анимацией и SVG-графикой.
* **🔔 Нативные уведомления Windows:** Программа сообщает о статусе подключения и активной стратегии через стандартные системные тосты Windows.
* **🌐 Умная работа с сетью:** 
  * Автоматический сброс DNS-кэша Windows (`DnsFlushResolverCache`).
  * Предварительная инициализация драйвера `WinDivert` при старте системы.
  * Мгновенный коннект к голосовым серверам Discord без зависания на «Подключении к RTC».

### 📋 Доступные стратегии:
1. **Discord** — точечный обход блокировок голосовых комнат, звонков и медиа-серверов Discord.
2. **YouTube** — пробитие блокировок видеопотоков GoogleVideo (воспроизведение вплоть до 4K/60fps).
3. **Optimized standard** — универсальный режим для большинства заблокированных сайтов.
4. **Custom hosts** — работа по собственному списку доменов, настраиваемому прямо в интерфейсе программы.

---

## 🇺🇸 Description (US)

**Aether** is a high-performance, standalone DPI bypass utility designed to restore smooth access to Discord (including voice/RTC servers), YouTube 4K streaming, and blocked websites without the overhead and latency of traditional VPNs.

### 🔥 Key Features:

* **⚡ 100% Standalone (Zero-Download):** All core engine files, lists, and network filters are embedded directly inside the `.exe`. Instant local extraction with zero network dependency on launch.
* **🚫 Pure C++ Engine (No .bat scripts):** All zapret bypass strategies are embedded into the compiled C++ core. Starts instantly via native system calls without popping up `cmd.exe` windows or writing temporary scripts to disk.
* **🎨 Modern Neomorphic UI:** Clean, polished light-mode interface powered by Edge WebView2 with smooth vector transitions.
* **🔔 Native Windows Toast Notifications:** Immediate system feedback on connection status and active strategy names.
* **🌐 Network Optimizations:**
  * Auto-flush of system DNS resolver cache on startup.
  * WinDivert kernel driver preloading for zero-latency filter engagement.
  * Instant Discord voice server connectivity without hanging on "RTC Connecting".

---

## 🚀 Установка и запуск / Quick Start

1. Перейдите во вкладку [Releases](https://github.com/ch1burek-lol/WaveX/releases).
2. Скачайте последнюю версию `Aether.exe`.
3. Запустите файл от имени **Администратора** *(требуется для загрузки сетевого драйвера WinDivert)*.
4. Нажмите центральную кнопку питания для активации обхода.

> ⚠️ **Примечание:** Если у вас установлен сторонний антивирус (Kaspersky, Dr.Web и др.), рекомендуется добавить папку `C:\Aether` в исключения, так как сетевые фильтры уровня ядра (WinDivert) могут вызывать ложные срабатывания эвристики.

---

## 🛠️ Технологический стек / Tech Stack

* **Language:** C++20
* **Framework:** Pure WinAPI, Microsoft WRL
* **Rendering Engine:** Microsoft Edge WebView2
* **Packet Filtering:** WinDivert kernel-mode network driver
* **Frontend:** HTML5, CSS3, ES6 JavaScript, Google Fonts

---

<p align="center">
  <b>Developed with ❤️ by <a href="https://github.com/ch1burek-lol">@ch1burek-lol</a></b>
</p>
