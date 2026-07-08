---
id: interface
title: Интерфейс (TextDraws)
sidebar_position: 11
---

# Интерфейс (TextDraws)

Весь пользовательский интерфейс построен на TextDraw'ах. Агрегатор — `sources/textdraws/textdraws.inc`,
инициализация — `TextDraws_OnGameModeInit()`.

## Элементы интерфейса

| Файл | Элемент |
| --- | --- |
| `speedometer.inc` | Спидометр. |
| `inventory.inc` | Инвентарь. |
| `iphone.inc` | Смартфон (iPhone). |
| `loading.inc` | Загрузочный экран. |
| `logo.inc` | Логотип. |
| `vehicles_shop.inc` | Автосалон. |
| `chooseskin.inc` | Выбор скина (при регистрации). |
| `bustimer.inc` | Таймер автобуса. |
| `info.inc` | Инфо-панели. |

## Связь с игровыми системами

- **Спидометр** — часть [Транспорта](vehicles), обновляется через `Speed_*`.
- **Инвентарь** — UI для системы [Инвентаря](inventory).
- **iPhone** — UI [Смартфона](phone); textdraws генерируются из корневого `iphone.txt.txt`.
- **Выбор скина** — используется при [Авторизации](authorization).
- **Таймер автобуса** — привязан к [автобусным остановкам](world).

## Обработка кликов

Клики по интерактивным textdraw'ам диспетчеризуются в per-module функции — например,
`Phone_OnPlayerClickTextDraw(...)` для смартфона.
