---
id: includes
title: Инклюды
sidebar_position: 3
---

# Инклюды (compile-time)

Compile-time инклюды живут в `qawno/include` и подключаются при сборке гейммода.
Изменения в коде должны оставаться совместимыми со всеми ними.

## Список инклюдов

| Инклюд | Назначение |
| --- | --- |
| `open.mp` | Основной заголовок движка (+ слой `SAMP_COMPAT`). |
| `YSI` | Библиотека YSI: `y_hooks` (хуки callback'ов), `y_iterate` (`foreach`-итераторы). |
| `izcmd` | Быстрый процессор команд (`CMD:name(...)`). |
| `sscanf2` | Парсинг строк и аргументов команд. |
| `streamer` | API стримера объектов/пикапов/зон (Incognito). |
| `a_mysql` | API MySQL-плагина. |
| `rustext` | API русификатора текста. |

## Как они используются

- **YSI `y_hooks`** — расширение callback'ов (`hook OnPlayerConnect(...)`), см. [Соглашения](../architecture/conventions).
- **YSI `y_iterate`** — итерация в стиле `foreach (new i : Vehicle)`, требуется совместимостью open.mp.
- **izcmd** — все [команды](../systems/commands).
- **sscanf2** — разбор аргументов команд.
- **streamer** — [объекты и интерьеры](../systems/objects), пикапы.
- **a_mysql** — [база данных](../database) через хелперы `core/mysql.inc`.
- **rustext** — серверный рендер русского текста.

## Совместимость

Каждый инклюд соответствует своему плагину/компоненту. При обновлении кода держите совместимость
с `SAMP_COMPAT`: `true`/`false` для булевых, `foreach`-итераторы, вынос литералов `mysql_format`
во временные переменные там, где этого требуют compat-заголовки.
