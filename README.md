# Flame Project

**Open Source RPG-гейм мод для [open.mp](https://www.open.mp/) (open multiplayer)**, написанный на Pawn.
Изначально разрабатывался для SA:MP, сейчас полностью переведён на open.mp через слой совместимости `SAMP_COMPAT`.

> Весь гейммод компилируется в один `flame.amx` из единственной точки входа — [`sources/flame.pwn`](sources/flame.pwn).
> Подробное техническое описание архитектуры и систем: **[sources/ARCHITECTURE.md](sources/ARCHITECTURE.md)**.

---

## Возможности

Игровой процесс построен вокруг классической RPG-механики (San Fierro как основная карта):

### Игрок
- **Авторизация** — регистрация/вход, выбор скина при регистрации, ограничение попыток входа.
- **Аккаунт и сохранения** — деньги, банк, RP-уровень/опыт, статистика (kills/deaths), настройки чата.
- **Инвентарь** — предметы, использование, выброс, отображение (textdraw-UI).
- **Банк** — счёт, переводы, проценты по вкладу, история транзакций.
- **Документы и лицензии** — ID-карта, водительские права, паспорт/документы.
- **Квесты** и **RP-рейтинг** — прогрессия персонажа.
- **Смартфон (iPhone)** — интерфейс телефона, SMS с историей, обои, часы, вызов транспорта.
- **Спавн и смерть** — система возрождения и обработка смерти.

### Транспорт
Крупная подсистема ([`sources/vehicles/`](sources/vehicles)):
- владение и покупка (автосалон / shop), ключи, каршеринг (sharing);
- топливо и двигатель, налог, номерные знаки, покраска/компоненты, гараж;
- спидометр и статистика транспорта.

### Мир и системы
- **Автобусные остановки**, **пикапы** (входы/выходы интерьеров), **погода**.
- **Работа** (job Horizon / Cell Fixer).
- **Актёры (NPC)**, **NPC-поезда** (filterscript + записи маршрутов).
- Большой набор **статичных объектов/интерьеров**: банк, госпиталь, полиция (PD), DMV, аэропорт, правительство, апартаменты, бизнесы (бар, кафе, магазин одежды) и др.

### Интерфейс (TextDraws)
Спидометр, инвентарь, iPhone, загрузочный экран, логотип, автосалон, выбор скина, таймер автобуса, инфо-панели.

### Команды
~287 команд, сгруппированных по темам ([`sources/commands/`](sources/commands)):
- **chat** — RP-чат: `/me`, `/do`, `/s`, `/w`, `/b`, `/pm`, `/shout` и т.д.;
- **anim** — большая библиотека анимаций;
- **main** — утилиты, role-play и админ-команды;
- **fraction**, **pame** — фракции и доп. механики.

---

## Технологический стек

| Слой | Что используется |
| --- | --- |
| Платформа | open.mp (open multiplayer), запуск через `omp-server.exe` |
| Язык | Pawn (`SAMP_COMPAT` + `#include <open.mp>`) |
| Библиотеки/инклюды | YSI (`y_hooks`, `y_iterate`), `izcmd`, `sscanf2`, `streamer`, `a_mysql`, `rustext` |
| Плагины (`plugins/`) | `crashdetect`, `jit`, `streamer` (Incognito), `sscanf`, `mysql`, `pawn-memory`, `rustext` |
| Компоненты (`components/`) | нативные подсистемы open.mp: Actors, Vehicles, Objects, TextDraws, Pickups, Dialogs и др. |
| База данных | MySQL, база `flame` (схема — [`database/flame.sql`](database/flame.sql)) |

---

## Сборка

Компиляция под Windows:

```bat
compile.bat
```

Скрипт вызывает `qawno\pawncc.exe` для `sources\flame.pwn` и переносит собранный `flame.amx` в `gamemodes\`.
Отдельного шага линтинга/тестов нет — «сборка прошла» означает, что компилятор Pawn создал `flame.amx` без новых ошибок.

## Запуск

1. Установите **MySQL** и импортируйте схему:
   ```bash
   mysql -u root -p flame < database/flame.sql
   ```
2. Укажите параметры подключения к БД в [`sources/core/mysql.inc`](sources/core/mysql.inc)
   (`MYSQL_HOST` / `MYSQL_USER` / `MYSQL_PASS` / `MYSQL_BASE`) и пересоберите гейммод.
3. Задайте свой **RCON-пароль** в [`config.json`](config.json) (`rcon.password`) — по умолчанию он пустой.
4. Запустите сервер: `omp-server.exe` (Windows). Конфигурация читается из `config.json`
   (заменяет старый `server.cfg`; `qawno` заменяет старый `pawno`).

> ⚠️ **Перед публичным запуском** обязательно задайте RCON-пароль и реальные учётные данные MySQL —
> в репозитории они намеренно пустые/дефолтные (localhost / root / без пароля) и не подходят для продакшена.

## CI/CD (GitHub Actions)

Сборка автоматизирована через [`.github/workflows/build.yml`](.github/workflows/build.yml):

- **На каждый push в `main` / pull request** — геймод компилируется на `windows-latest`
  (проверка, что `flame.amx` собирается), готовый сервер пакуется в `.zip` и загружается
  как artifact прогона (вкладка Actions → конкретный run → Artifacts).
- **На пуш тега `v*`** (например `v1.0.0`) — дополнительно создаётся **GitHub Release**,
  к которому прикрепляется `.zip` со сборкой.

Выпустить релиз:

```bash
git tag v1.0.0
git push origin v1.0.0
```

Собранный `.zip` содержит готовый к запуску Windows-сервер (`omp-server.exe`, `gamemodes/flame.amx`,
компоненты, плагины, `config.json`, схему БД) **без** dev-инструментов (`qawno/`, исходников, `.pdb`).
Linux-сборку планируется добавить отдельной job'ой (см. Roadmap).

---

## Структура репозитория

```
flameproject/
├── sources/            # исходный код гейммода (Pawn)
│   ├── flame.pwn       # точка входа
│   ├── ARCHITECTURE.md # подробное описание систем и архитектуры
│   ├── core/           # ядро: MySQL-хелперы, цвета, диалоги, зоны, таймеры, утилиты
│   ├── player/         # авторизация, аккаунт, инвентарь, банк, документы, телефон, админка
│   ├── vehicles/       # транспортная подсистема
│   ├── textdraws/      # UI (textdraws)
│   ├── objects/        # статичные объекты/интерьеры по локациям
│   ├── systems/        # остановки, пикапы, погода, работы
│   └── commands/       # чат-команды по темам
├── config.json         # конфигурация open.mp-сервера
├── database/flame.sql  # схема базы данных
├── components/         # нативные компоненты open.mp (.dll)
├── plugins/            # legacy-плагины Pawn (.dll)
├── qawno/              # компилятор Pawn и инклюды
├── filterscripts/      # filterscripts (NPC-поезда)
├── npcmodes/           # записи маршрутов NPC
└── scriptfiles/        # runtime-данные сервера
```

## Кодировка (важно)

Исходные файлы с русским текстом сохранены в **Windows-1251 (cp1251)**, MySQL также настроен на cp1251.
Русский текст может отображаться как «кракозябры» в UTF-8-инструментах — это ожидаемо.
**Не перекодируйте `.inc`/`.pwn` файлы в UTF-8** — это необратимо повредит кириллицу.
Подробности и безопасные способы правки — в [`CLAUDE.md`](CLAUDE.md).

---

## Roadmap / Планы развития

Проект **активно развивается** — это не заброшенный дамп кода, а живая база, которую планируется расширять.
Ближайшие направления:

- [ ] **Игровые системы** — улучшать и дописывать существующие механики, добавлять новые.
- [x] **Документация** — сайт на GitHub Pages: [alexdedyura.github.io/flameproject](https://alexdedyura.github.io/flameproject/) (исходники — в [`website/`](website), сборка на [Docusaurus](https://docusaurus.io/)).
- [x] **CI/CD (Windows)** — сборка `.zip` и публикация в Releases через GitHub Actions ([`build.yml`](.github/workflows/build.yml)).
- [ ] **CI/CD (Linux)** — добавить Linux-сборку сервера отдельной job'ой.
- [ ] **flamelibrary** — вынести базовую логику в отдельный фреймворк/библиотеку для переиспользования.

Идеи и предложения приветствуются — открывайте issue или обсуждение.

## Contributing / Вклад в проект

**Пулл-реквесты приветствуются!** 🔥 Проект открыт для развития сообществом.

- Перед крупными изменениями желательно открыть issue и обсудить идею.
- Сохраняйте модульную структуру: новую логику — в ближайший тематический модуль внутри `sources/`.
- Команды добавляйте через `izcmd` (`CMD:name(playerid, params[])`), callbacks расширяйте через `y_hooks`,
  работу с БД ведите через хелперы из [`sources/core/mysql.inc`](sources/core/mysql.inc).
- **Соблюдайте кодировку cp1251** для `.inc`/`.pwn` с кириллицей (см. раздел выше и [`CLAUDE.md`](CLAUDE.md)).
- Убедитесь, что геймод компилируется (`compile.bat`) без новых ошибок/варнингов.

Подробные гайды для контрибьюторов и AI-ассистентов: [`CLAUDE.md`](CLAUDE.md) и [`sources/ARCHITECTURE.md`](sources/ARCHITECTURE.md).

## Авторы

Автор: **Alex Dedyura**.

## Лицензия

Проект распространяется под лицензией **GNU General Public License v3.0** — полный текст в файле [`LICENSE`](LICENSE).

```
Flame Project — Open Source RPG gamemode for open.mp
Copyright (C) 2026 Alex Dedyura

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
```

