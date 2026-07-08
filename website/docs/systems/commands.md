---
id: commands
title: Команды
sidebar_position: 12
---

# Команды

В гейммоде **~287 команд**, реализованных через `izcmd` (`CMD:name(playerid, params[])`),
с разбором аргументов через `sscanf2`. Агрегатор — `sources/commands/commands.inc`.

## Группы команд

| Файл | Тема |
| --- | --- |
| `chat.inc` | RP-чат: `/me`, `/do`, `/s`, `/w`, `/b`, `/pm`, `/shout` и т.д. |
| `anim.inc` | Большая библиотека анимаций. |
| `main.inc` | Утилиты, role-play и админ-команды. |
| `fraction.inc` | Фракции. |
| `pame.inc` | Доп. механики. |

## RP-чат

Основные команды отыгрыша роли (`chat.inc`):

| Команда | Назначение |
| --- | --- |
| `/me` | Действие от третьего лица. |
| `/do` | Описание окружения/состояния. |
| `/s` (shout) | Крик. |
| `/w` (whisper) | Шёпот. |
| `/b` | OOC (не в роли) локально. |
| `/pm` | Личное сообщение. |

RP-чат работает по радиусу (`use_chat_radius`, `chat_radius` в `config.json`).

## Как добавить команду

```c
CMD:mycmd(playerid, params[])
{
    // разбор аргументов через sscanf2
    return 1;
}
```

Добавляйте команду в ближайший тематический файл в `sources/commands/`, а не отдельным include
из `flame.pwn` (см. [Соглашения](../architecture/conventions)).
