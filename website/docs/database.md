---
id: database
title: База данных
sidebar_position: 6
---

# База данных

Хранилище — **MySQL**, база `flame`. Схема и дамп — `database/flame.sql`.
Соединение работает в кодировке **cp1251** (см. `core/mysql.inc` и [Кодировка cp1251](architecture/encoding)).

## Таблицы

| Таблица | Назначение |
| --- | --- |
| `accounts` | Аккаунты: имя, пароль, почта, деньги, банк, IP регистрации/входа, admin-уровень, статистика, RP-опыт/уровень, настройки чата и др. |
| `inventory` | Предметы инвентаря игроков. |
| `bank_transactions` | История банковских транзакций. |
| `bank_settings` | Настройки банка (например, процентная ставка). |
| `documents` | Документы игроков. |
| `vehicles` | Транспорт (владение, параметры). |
| `phone_messages` | История SMS. |
| `actors` | Актёры / NPC. |
| `bus_stops` | Автобусные остановки (позиции, тип). |
| `pickups` | Пикапы входов/выходов интерьеров. |
| `mapping` | Данные маппинга. |

## Что в дампе

Дамп `flame.sql` содержит только **конфигурационные** данные (`bank_settings`, `bus_stops`, `pickups`) —
реальных пользовательских записей в репозитории нет.

## Импорт схемы

```bash
mysql -u root -p flame < database/flame.sql
```

## Работа с БД в коде

Только через хелперы из `sources/core/mysql.inc`:

- `UpdateBaseInt/Str/Float` — точечные обновления полей;
- `mysql_format` + `mysql_tquery` с callback-паттернами — запросы.

Подробнее — в [Соглашениях](architecture/conventions).

## Какая таблица какой системе принадлежит

| Система | Таблицы |
| --- | --- |
| [Авторизация](systems/authorization) / аккаунт | `accounts` |
| [Инвентарь](systems/inventory) | `inventory` |
| [Банк](systems/bank) | `bank_transactions`, `bank_settings` |
| [Документы](systems/documents) | `documents` |
| [Транспорт](systems/vehicles) | `vehicles` |
| [Смартфон](systems/phone) | `phone_messages` |
| [Мир](systems/world) | `bus_stops`, `pickups`, `actors` |
| [Объекты](systems/objects) | `mapping` |
