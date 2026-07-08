---
id: plugins
title: Legacy Pawn-плагины
sidebar_position: 1
---

# Legacy Pawn-плагины

Плагины лежат в `plugins/*.dll` и подключаются через `pawn.legacy_plugins` в `config.json`.
Все они бандлятся в репозитории — считайте их **read-only**.

## Список плагинов

| Плагин | Версия | Назначение |
| --- | --- | --- |
| `crashdetect` | — | Бэктрейсы падений/ошибок AMX при разработке. |
| `jit` | — | JIT-компилятор Pawn для скорости выполнения. |
| `streamer` | v2.9.6 (Incognito) | Стриминг объектов/пикапов/лейблов/зон сверх лимитов. |
| `sscanf` | 2.13.8 | Парсинг строк/аргументов (`sscanf2`) для команд. |
| `mysql` | — | Доступ к MySQL (`a_mysql`); работает в cp1251. |
| `pawn-memory` | — | Низкоуровневые операции с памятью/кучей. |
| `rustext` | — | Серверный рендеринг русского текста (`SetDefaultRussifierType`). |

## Порядок подключения в config.json

```json
{
  "pawn": {
    "legacy_plugins": ["sscanf", "crashdetect", "streamer", "mysql", "rustext"]
  }
}
```

:::note
`pawnraknet` и `CRP` из старой SA-MP-сборки больше не загружаются (может оставаться устаревший
`plugins/pawnraknet.cfg`).
:::

## Где что используется

- **streamer** — все статичные [объекты и интерьеры](../systems/objects), пикапы, лейблы, зоны.
- **sscanf** — разбор аргументов во всех [командах](../systems/commands).
- **mysql** — вся работа с [базой данных](../database) через хелперы `core/mysql.inc`.
- **rustext** — включается в `OnGameModeInit()` через `SetDefaultRussifierType(RussifierType_SanLtd)`.
- **crashdetect** / **jit** — инструменты разработки и производительности.
