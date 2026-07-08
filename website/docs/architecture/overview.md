---
id: overview
title: Обзор и порядок загрузки
sidebar_position: 1
---

# Обзор архитектуры

Весь гейммод собирается из одного файла — `sources/flame.pwn` — в единственный `flame.amx`.
В начале файла подключается слой совместимости SA-MP → open.mp:

```c
#define SAMP_COMPAT
#include <open.mp>
```

## Порядок включения модулей

`flame.pwn` подключает **агрегирующие `.inc`-файлы**, каждый из которых втягивает свои подмодули.
**Порядок include важен** — он кодирует реальные зависимости:

```c
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

:::note Почему порядок важен
Например, `player/phone.inc` подключается **после** `vehicles.inc`, потому что функция вызова
транспорта с телефона зависит и от инвентаря игрока, и от enum'ов транспорта.
:::

## Диспетчеризация callback'ов

`flame.pwn` вручную диспетчеризует часть callback'ов в per-module функции — например:

- `Vehicles_OnPlayerStateChange(...)`
- `Speed_OnPlayerStateChange(...)`
- `Phone_OnPlayerClickTextDraw(...)`

В остальных местах callbacks расширяются через `YSI\y_hooks` (`hook OnX()`). При добавлении кода
следуйте паттерну соседнего модуля (см. [Соглашения](conventions)).

## Инициализация в `OnGameModeInit()`

Подсистемы инициализируются по очереди: таймеры, textdraws, автосалон (`VShop`), каршеринг (`VSharing`),
ключи (`VKeys`), телефон (`Phone`), топливо (`SetFuelSystemCars`), а также включается серверная
русификация текста через `SetDefaultRussifierType(RussifierType_SanLtd)` (плагин `rustext`).

## Карта модулей

| Модуль | Агрегатор | Назначение |
| --- | --- | --- |
| **core** | `core/core.inc` | Инженерные хелперы: MySQL-обёртки, цвета, диалоги, макросы, зоны, таймеры, строки/даты. |
| **textdraws** | `textdraws/textdraws.inc` | Весь TextDraw-UI: спидометр, инвентарь, iPhone, загрузочный экран и др. |
| **player** | `player/player.inc` | Авторизация, аккаунт/инвентарь, документы, лицензии, банк, квесты, RP-рейтинг, спавн, смерть. |
| **vehicles** | `vehicles/vehicles.inc` | Транспорт: ядро, владение, ключи, каршеринг, магазин, топливо, налог, спидометр. |
| **phone** | `player/phone.inc` | Подсистема смартфона. |
| **admin** | `player/admin/admin.inc` | Админ-инструменты, spectate. |
| **objects** | `objects/object.inc` | Статичные объекты/интерьеры по локациям. |
| **systems** | `systems/systems.inc` | Автобусные остановки, пикапы, погода, работы. |
| **commands** | `commands/commands.inc` | Все чат-команды, сгруппированные по темам. |

Детали каждой подсистемы — в разделе [Игровые системы](../systems/authorization).
