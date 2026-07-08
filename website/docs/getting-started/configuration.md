---
id: configuration
title: Конфигурация
sidebar_position: 4
---

# Конфигурация

Основная конфигурация сервера живёт в `config.json` (заменяет старый `server.cfg`).
Здесь — ключевые блоки, которые важно понимать при запуске.

## Главный скрипт и плагины

```json
{
  "pawn": {
    "legacy_plugins": ["sscanf", "crashdetect", "streamer", "mysql", "rustext"],
    "main_scripts": ["flame"],
    "side_scripts": []
  }
}
```

- `main_scripts: ["flame"]` — загружает `gamemodes/flame.amx`;
- `legacy_plugins` — список подключаемых Pawn-плагинов из `plugins/` (см. [Библиотеки → Плагины](../libraries/plugins)).

## Сеть и игроки

```json
{
  "max_players": 500,
  "max_bots": 500,
  "network": { "port": 7777, "stream_radius": 200.0 }
}
```

## Игровые настройки

```json
{
  "game": {
    "map": "San Fierro",
    "chat_radius": 100.0,
    "use_chat_radius": true,
    "use_manual_engine_and_lights": true,
    "vehicle_respawn_time": 10000
  },
  "language": "Russian",
  "name": "Flame Project | Open.MP"
}
```

Обратите внимание на `use_manual_engine_and_lights` — гейммод сам управляет двигателем/фарами
(см. [Транспорт](../systems/vehicles)), и `use_chat_radius` — RP-чат работает по радиусу.

## RCON

```json
{
  "rcon": {
    "enable": true,
    "allow_teleport": false,
    "password": ""
  }
}
```

:::warning
`password` по умолчанию пустой — обязательно задайте свой перед публичным запуском.
:::

## Параметры подключения к БД

Доступы к MySQL задаются **не** в `config.json`, а в исходнике `sources/core/mysql.inc`
(`MYSQL_HOST` / `MYSQL_USER` / `MYSQL_PASS` / `MYSQL_BASE`) — после изменения гейммод нужно пересобрать.

## Что не стоит трогать без причины

- Бинарники движка: `omp-server.exe`, компоненты в `components/`, плагины в `plugins/`;
- бандл `qawno/` (компилятор и инклюды);
- массовые изменения `config.json`, `database/flame.sql`, runtime-данных в `scriptfiles/`.
