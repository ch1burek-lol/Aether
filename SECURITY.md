# Политика безопасности / Security Policy

**Русский** | [English](#english)

## Поддерживаемые версии

Исправления безопасности выпускаются для версии **1.5.x**. Более старые версии (≤ 1.4) не поддерживаются, обновитесь до последней.

## Как сообщить об уязвимости

**Пожалуйста, не создавайте публичный Issue для уязвимостей.**

Откройте вкладку [Security](https://github.com/ch1burek-lol/Aether/security) этого репозитория и нажмите **Report a vulnerability**. Сообщение увидит только автор проекта.

Укажите версию Aether и Windows, описание проблемы и шаги воспроизведения.

Я постараюсь ответить в течение нескольких дней и выпустить исправление как можно скорее. После выхода исправления информация об уязвимости может быть опубликована, по желанию с благодарностью автору отчёта.

## Что считается уязвимостью

- выполнение произвольного кода и повышение привилегий (приложение часто запускается от имени администратора);
- подмена обновлений;
- утечки DNS / IPv6 / трафика;
- утечка конфигураций и ключей.

Уязвимости сторонних компонентов (sing-box, Xray-core, WinDivert, zapret, Wintun) лучше сообщать их авторам.

## Как проверить скачанный файл

Скачивайте Aether только со страницы [Releases](https://github.com/ch1burek-lol/Aether/releases). Исходный код открыт (GPL-3.0), его можно проверить и собрать самостоятельно.

---

<a name="english"></a>

# Security Policy (English)

## Supported Versions

Security fixes are released for version **1.5.x**. Older versions (≤ 1.4) are not supported, please upgrade.

## Reporting a Vulnerability

**Please do not open a public issue for security vulnerabilities.**

Open the [Security](https://github.com/ch1burek-lol/Aether/security) tab of this repository and click **Report a vulnerability**. Only the maintainer will see your report.

Include the Aether and Windows versions, a description of the issue and reproduction steps.

I will try to respond within a few days and release a fix as soon as possible. After the fix is released, the vulnerability may be disclosed publicly, with credit to the reporter if they wish.

## What Counts as a Vulnerability

- arbitrary code execution and privilege escalation (the app is often run as Administrator);
- update tampering;
- DNS / IPv6 / traffic leaks;
- leakage of configs or keys.

Vulnerabilities in third-party components (sing-box, Xray-core, WinDivert, zapret, Wintun) should be reported to their maintainers.

## Verifying Your Download

Download Aether only from the [Releases](https://github.com/ch1burek-lol/Aether/releases) page. The source code is open (GPL-3.0), so you can audit it and build it yourself.
