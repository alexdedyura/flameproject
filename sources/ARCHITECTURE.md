# Flame Project — Архитектура и системы

Подробное техническое описание гейм мода. Краткий обзор — в корневом [README.md](../README.md).
Правила разработки — в [CLAUDE.md](../CLAUDE.md) (EN).

---

## 1. Точка входа и порядок загрузки

Весь гейммод собирается из одного файла — [`flame.pwn`](flame.pwn) — в единственный `flame.amx`.
В начале файла подключается слой совместимости SA-MP → open.mp:

```pawn
#define SAMP_COMPAT
#include <open.mp>
```

Затем `flame.pwn` подключает **агрегирующие `.inc`-файлы**, каждый из которых втягивает свои подмодули.
**Порядок include важен** — он кодирует реальные зависимости:

```pawn
#include <..\..\sources\core\core.inc>          // ядро — базовые хелперы
#include <..\..\sources\textdraws\textdraws.inc> // UI
#include <..\..\sources\player\player.inc>       // игрок: авторизация, аккаунт, инвентарь…
#include <..\..\sources\vehicles\vehicles.inc>   // транспорт
#include <..\..\sources\player\phone.inc>        // телефон (ПОСЛЕ vehicles — нужны enum'ы транспорта)
#include <..\..\sources\player\admin\admin.inc>  // админка
#include <..\..\sources\objects\object.inc>      // статичные объекты/интерьеры
#include <..\..\sources\systems\systems.inc>     // остановки, пикапы, погода, работы
#include <..\..\sources\commands\commands.inc>   // чат-команды
```

`flame.pwn` также вручную диспетчеризует часть callback'ов в per-module функции
(например `Vehicles_OnPlayerStateChange(...)`, `Speed_OnPlayerStateChange(...)`,
`Phone_OnPlayerClickTextDraw(...)`). В остальных местах callbacks расширяются через `YSI\y_hooks`
(`hook OnX()`) — следуйте паттерну соседнего кода.

`OnGameModeInit()` инициализирует подсистемы по очереди: таймеры, textdraws, автосалон (`VShop`),
каршеринг (`VSharing`), ключи (`VKeys`), телефон (`Phone`), топливо (`SetFuelSystemCars`),
и включает серверную русификацию текста через `SetDefaultRussifierType(RussifierType_SanLtd)` (плагин `rustext`).

---

## 2. Модули

### 2.1 `core/` — ядро
Инженерные хелперы, общие для всего мода. Начинать изучение стоит отсюда.

| Файл | Назначение |
| --- | --- |
| `mysql.inc` | Подключение к MySQL и хелперы запросов: `UpdateBaseInt/Str/Float`, паттерны `mysql_format` + `mysql_tquery`. Настройка кодировки cp1251 на соединении. |
| `colors.inc` | Константы цветов (`COLOR_*`). |
| `dialogs.inc` | Константы ID диалогов. |
| `macrosses.inc` | Общие макросы. |
| `zones.inc` | Игровые зоны San Andreas. |
| `timers.inc` | Глобальные таймеры (`Timers_OnGameModeInit`, `Timers_OnPlayerConnect`). |
| `dates.inc` / `mxdate.inc` | Работа с датой/временем. |
| `strlib.inc` | Строковые утилиты. |
| `nearbymessage.inc` | Сообщения игрокам рядом (радиус). |
| `mapicon.inc`, `pos_info.inc`, `vehicles_int.inc` | Карта-иконки, позиции, служебные данные транспорта. |

### 2.2 `textdraws/` — интерфейс
Все textdraw-UI: `speedometer`, `inventory`, `iphone`, `loading`, `logo`, `vehicles_shop`,
`chooseskin`, `bustimer`, `info`. Инициализация — `TextDraws_OnGameModeInit()`.

### 2.3 `player/` — игрок
Авторизация, аккаунт, инвентарь, документы, банк, квесты, RP-рейтинг, спавн, смерть.

| Файл / папка | Назначение |
| --- | --- |
| `authorization.inc` | Регистрация/вход, выбор скина при регистрации (`reg_skins`), камера регистрации, лимит попыток (`MAX_AUTH_TRIES = 3`), стартовые деньги (`REG_START_MONEY = 200`). |
| `playerdata.inc` | Enum'ы и массив данных игрока `pData[playerid][...]`. |
| `player.inc` | Загрузка/сохранение аккаунта и инвентаря, диспетчер `Player_OnPlayerDisconnect`. |
| `inv/` | Инвентарь: `items.inc`, `use.inc`, `drop.inc`, `show.inc`, `inv.inc`. |
| `bank_system.inc` | Банковский счёт, переводы, проценты, история транзакций. |
| `documents.inc`, `id_card.inc`, `driving_licenses.inc` | Документы, ID-карта, водительские права. |
| `quests.inc`, `rp_rating.inc` | Квесты и RP-уровень/опыт. |
| `spawn.inc`, `death.inc` | Спавн и обработка смерти. |
| `actors.inc` | Актёры (NPC-персонажи). |
| `loading_texture.inc` | Экран загрузки текстур. |
| `gps.pwn` | GPS. |
| `phone.inc`, `phone_clock.inc` | Смартфон (см. §3). |
| `admin/` | Админ-инструменты и spectate. |

### 2.4 `vehicles/` — транспорт
Крупнейшая подсистема. Агрегатор — `vehicles.inc`.

| Файл | Назначение |
| --- | --- |
| `vehicles_core.pwn` | Ядро транспорта, enum'ы, спавн. |
| `vehicles_player.pwn` | Владение транспортом игроком. |
| `vehicles_shop.pwn` | Автосалон/покупка (`VShop_*`). |
| `vehicles_keys.pwn` | Ключи (`VKeys_*`). |
| `vehicles_sharing.pwn` | Каршеринг (`VSharing_*`). |
| `vehicles_engine.pwn` | Двигатель, топливная система. |
| `vehicles_tax.pwn` | Налог на транспорт. |
| `vehicles_numbers.pwn` | Номерные знаки. |
| `vehicles_params.pwn`, `vehicles_comp.pwn` | Параметры и компоненты/покраска. |
| `vehicles_garage.pwn` | Гараж. |
| `vehicles_stats.pwn` | Статистика транспорта. |
| `speedometer.pwn` | Спидометр (`Speed_*`, `CreateSpeedometerPTD`). |

### 2.5 `objects/` — статичные объекты и интерьеры
Карта и интерьеры по локациям (агрегатор — `object.inc`): банк, госпиталь, полиция (`pd_*`),
DMV, аэропорт, правительство, апартаменты (Horizon), бизнесы (бар, кафе, магазин одежды),
здания San Fierro, Alcatraz, национальный парк, «Silicon Valley», арена AT-T и др.

### 2.6 `systems/` — мир
| Файл | Назначение |
| --- | --- |
| `bus_stops.inc` | Автобусные остановки и маршруты. |
| `pickups.inc` | Пикапы: входы/выходы интерьеров (enter/exit позиции, виртуальные миры, интерьеры). |
| `weather.inc` | Погода и динамические зоны (`W_EnterDynamicArea`). |
| `job_horizon.inc` | Работа Horizon / Cell Fixer. |

### 2.7 `commands/` — команды
~287 команд через `izcmd` (`CMD:name(playerid, params[])`), парсинг аргументов через `sscanf2`.
Сгруппированы: `chat.inc` (RP-чат), `anim.inc` (анимации), `main.inc` (утилиты/RP/админ),
`fraction.inc` (фракции), `pame.inc`.

---

## 3. Подсистема смартфона (iPhone)

- Логика: `player/phone.inc`; textdraws: `textdraws/iphone.inc` (генерируются из корневого `iphone.txt.txt`).
- Подключается **после** `vehicles.inc`, т.к. функция вызова транспорта с телефона зависит и от
  инвентаря игрока, и от enum'ов транспорта.
- Обои переиспользуют **глобальные** элементы фона `iPhone[6..11]` (рендерятся под статус-баром/иконками);
  индивидуальный цвет задаётся `TextDrawColor` прямо перед `TextDrawShowForPlayer` (фиксируется на момент показа,
  чтобы одновременные зрители не конфликтовали).
- Часы: `PhoneUpdateClock()` в `phone_clock.inc` (**cp1251** — русские названия месяцев/дней недели),
  обновляются при открытии и раз в секунду через `Phone_PlayerSecTimer`.
- Предмет инвентаря: `INV_ITEM_PHONE = 6`, параметр `INV_PHONE_PARAM = 1`; выбор обоев хранится в
  `PlayerInventory[playerid][slot][invInfo]`.
- История SMS — таблица `phone_messages`; лимит на диалог — 100 сообщений, старые строки подрезаются после вставки.
- `/givephone` — тестовая выдача телефона.

---

## 4. База данных

MySQL, база `flame`, схема/дамп — [`database/flame.sql`](../database/flame.sql).
Соединение работает в кодировке cp1251 (см. `core/mysql.inc`).

| Таблица | Назначение |
| --- | --- |
| `accounts` | Аккаунты: имя, пароль, почта, деньги, банк, IP регистрации/входа, admin-уровень, статистика, RP-опыт/уровень, настройки чата и др. |
| `inventory` | Предметы инвентаря игроков. |
| `bank_transactions` | История банковских транзакций. |
| `bank_settings` | Настройки банка (напр. процентная ставка). |
| `documents` | Документы игроков. |
| `vehicles` | Транспорт (владение, параметры). |
| `phone_messages` | История SMS. |
| `actors` | Актёры/NPC. |
| `bus_stops` | Автобусные остановки (позиции, тип). |
| `pickups` | Пикапы входов/выходов интерьеров. |
| `mapping` | Данные маппинга. |

> Дамп содержит только конфигурационные данные (`bank_settings`, `bus_stops`, `pickups`) —
> реальных пользовательских записей в репозитории нет.

---

## 5. Зависимости

Обе группы поставляются в репозитории (считать read-only).

**Legacy Pawn-плагины** (`plugins/*.dll`, список в `config.json` → `pawn.legacy_plugins`):

| Плагин | Назначение |
| --- | --- |
| `crashdetect` | Бэктрейсы падений/ошибок AMX при разработке. |
| `jit` | JIT-компилятор Pawn (скорость выполнения). |
| `streamer` (v2.9.6, Incognito) | Стриминг объектов/пикапов/лейблов/зон сверх лимитов. |
| `sscanf` (2.13.8) | Парсинг строк/аргументов (`sscanf2`). |
| `mysql` | Доступ к MySQL (`a_mysql`), работает в cp1251. |
| `pawn-memory` | Низкоуровневые операции с памятью/кучей. |
| `rustext` | Серверный рендеринг русского текста (`SetDefaultRussifierType`). |

**Компоненты open.mp** (`components/*.dll`): нативные подсистемы движка (Actors, Vehicles, Objects,
TextDraws, Pickups, Dialogs, GangZones, Menus, NPCs, Recordings, Checkpoints, Classes и др.).
Не редактируются — используются их нативы.

Compile-time инклюды: `qawno/include` (`open.mp`, `YSI`, `izcmd`, `sscanf2`, `streamer`, `a_mysql`, `rustext`).

---

## 6. Соглашения

- **Callbacks** — расширять через `y_hooks` (`hook OnX()`), либо диспетчеризовать в per-module функции,
  как это уже сделано в `flame.pwn`. Следуйте паттерну соседнего модуля.
- **Команды** — `izcmd` (`CMD:name(playerid, params[])`), аргументы через `sscanf2`.
- **MySQL** — только через хелперы `core/mysql.inc`. Имя базы — `flame`.
- **Новый подмодуль** — подключать через ближайший агрегирующий `.inc`, а не напрямую из `flame.pwn`.
- **`forward` перед `public`** для timer/MySQL-callback функций, если требует компилятор и так принято рядом.
- **open.mp compat** — использовать `true`/`false`, итераторы `foreach (new i : Vehicle)`,
  выносить литералы `mysql_format` во временные переменные, где этого требуют compat-заголовки.

## 7. Кодировка (критично)

Исходники с русским текстом — в **Windows-1251 (cp1251)**. MySQL настроен на cp1251.
**Никогда** не сохраняйте `.inc`/`.pwn` c кириллицей как UTF-8 (в т.ч. в комментариях) — байты кириллицы
превращаются в `U+FFFD` безвозвратно. Правьте cp1251-файлы только байт-безопасными инструментами
(`perl -i -pe`, `sed -i` по номерам строк, PowerShell через `[byte[]]`). Подробности — в [CLAUDE.md](../CLAUDE.md).
