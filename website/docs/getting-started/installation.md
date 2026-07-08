---
id: installation
title: Установка и запуск
sidebar_position: 2
---

# Установка и запуск

Пошаговый запуск сервера Flame Project на Windows.

## 1. Получите репозиторий

```bash
git clone https://github.com/alexdedyura/flameproject.git
cd flameproject
```

Либо скачайте готовую Windows-сборку из [GitHub Releases](https://github.com/alexdedyura/flameproject/releases) —
в архиве уже лежит собранный сервер (без dev-инструментов).

## 2. Установите MySQL и импортируйте схему

Создайте базу `flame` и залейте в неё дамп схемы:

```bash
mysql -u root -p flame < database/flame.sql
```

Дамп содержит только конфигурационные данные (`bank_settings`, `bus_stops`, `pickups`);
пользовательских записей в репозитории нет. Подробнее о таблицах — в разделе [База данных](../database).

## 3. Укажите параметры подключения к БД

Пропишите доступы к MySQL в `sources/core/mysql.inc`:

```c
#define MYSQL_HOST   "localhost"
#define MYSQL_USER   "root"
#define MYSQL_PASS   ""
#define MYSQL_BASE   "flame"
```

После изменения доступов гейммод нужно **пересобрать** (см. [Сборка](building)).

## 4. Задайте RCON-пароль

В `config.json` установите свой пароль администратора сервера:

```json
{
  "rcon": {
    "enable": true,
    "password": "ваш-надёжный-пароль"
  }
}
```

## 5. Запустите сервер

```bat
omp-server.exe
```

Сервер читает `config.json` (он заменяет старый `server.cfg`), из которого берёт главный скрипт
(`pawn.main_scripts: ["flame"]`), список legacy-плагинов и все настройки open.mp.

:::warning Перед публичным запуском
Обязательно задайте **RCON-пароль** и **реальные учётные данные MySQL**. В репозитории они намеренно
пустые/дефолтные (`localhost` / `root` / без пароля) и не годятся для продакшена.
:::

## Следующий шаг

Если вы меняли исходники — соберите гейммод: [Сборка](building).
Разбор всех ключевых настроек — в разделе [Конфигурация](configuration).
