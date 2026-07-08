---
id: contributing
title: Разработка и вклад
sidebar_position: 7
---

# Разработка и вклад в проект

Проект **активно развивается** и открыт для сообщества. Пулл-реквесты приветствуются. 🔥

## Прежде чем писать код

- Перед крупными изменениями откройте issue и обсудите идею.
- Сохраняйте модульную структуру: новую логику — в ближайший тематический модуль внутри `sources/`.
- Ознакомьтесь с [Архитектурой](architecture/overview) и [Соглашениями](architecture/conventions).

## Основные правила

| Тема | Правило |
| --- | --- |
| Команды | Добавляйте через `izcmd` (`CMD:name(playerid, params[])`), аргументы — через `sscanf2`. |
| Callbacks | Расширяйте через `y_hooks` (`hook OnX()`) либо диспетчеризуйте, как в `flame.pwn`. |
| MySQL | Только через хелперы `sources/core/mysql.inc`. |
| Модули | Новый подмодуль — через ближайший агрегирующий `.inc`, не напрямую из `flame.pwn`. |
| Кодировка | cp1251 для `.inc`/`.pwn` с кириллицей — см. [Кодировка cp1251](architecture/encoding). |
| Сборка | Убедитесь, что гейммод компилируется (`compile.bat`) без новых ошибок/варнингов. |

## CI/CD (GitHub Actions)

Сборка автоматизирована через `.github/workflows/build.yml`:

- **На каждый push в `main` / pull request** — гейммод компилируется на `windows-latest`
  (проверка, что `flame.amx` собирается), готовый сервер пакуется в `.zip` и загружается как
  artifact прогона (вкладка **Actions** → конкретный run → **Artifacts**).
- **На пуш тега `v*`** (например `v1.0.0`) — дополнительно создаётся **GitHub Release** с `.zip`-сборкой.

Выпустить релиз:

```bash
git tag v1.0.0
git push origin v1.0.0
```

Собранный `.zip` содержит готовый к запуску Windows-сервер (`omp-server.exe`, `gamemodes/flame.amx`,
компоненты, плагины, `config.json`, схему БД) **без** dev-инструментов (`qawno/`, исходников, `.pdb`).

## Документация (этот сайт)

Сайт документации собран на [Docusaurus](https://docusaurus.io/) и лежит в каталоге `website/`.

Локальный запуск:

```bash
cd website
npm install
npm start
```

Продакшн-сборка:

```bash
npm run build
```

Сайт публикуется на **GitHub Pages** автоматически через `.github/workflows/deploy-docs.yml`
при пуше в `main` (изменения в `website/`). Итоговый адрес —
[alexdedyura.github.io/flameproject](https://alexdedyura.github.io/flameproject/).

## Roadmap

- [ ] **Игровые системы** — улучшать и дописывать механики, добавлять новые.
- [x] **Документация** — этот сайт на GitHub Pages.
- [x] **CI/CD (Windows)** — сборка `.zip` и публикация в Releases.
- [ ] **CI/CD (Linux)** — добавить Linux-сборку сервера отдельной job'ой.
- [ ] **flamelibrary** — вынести базовую логику в отдельный фреймворк/библиотеку.

## Лицензия

Проект распространяется под лицензией **GNU General Public License v3.0**. Автор — **Alex Dedyura**.
