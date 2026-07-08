---
id: objects
title: Объекты и интерьеры
sidebar_position: 10
---

# Объекты и интерьеры

Статичные объекты карты и интерьеры по локациям. Агрегатор — `sources/objects/object.inc`.
Каждая локация вынесена в свой `.inc`-файл.

## Локации

| Файл | Локация |
| --- | --- |
| `bank.inc` | Банк. |
| `hospital_interior.inc` | Госпиталь (интерьер). |
| `pd_interior.inc`, `pd_exterior.inc` | Полиция (PD) — интерьер и экстерьер. |
| `dmv.inc` | DMV (выдача водительских прав). |
| `airport.inc` | Аэропорт. |
| `government.inc` | Правительство. |
| `horizon_apartments.inc`, `horizon_mobile.inc` | Апартаменты Horizon. |
| `business_bar.inc` | Бизнес: бар. |
| `business_cafe.inc` | Бизнес: кафе. |
| `business_clothing.inc` | Бизнес: магазин одежды. |
| `autoshow.inc` | Автосалон. |
| `sf_building.inc` | Здания San Fierro. |
| `alcatraz.inc` | Алькатрас. |
| `national_park.inc` | Национальный парк. |
| `silicon_valley.inc` | «Silicon Valley». |
| `at-t_arena.inc` | Арена AT-T. |
| `chilliad_road.inc` | Дорога на Chilliad. |
| `bus_station.inc`, `bus_interior.inc` | Автовокзал и его интерьер. |

## Как связано с остальным

- Входы/выходы интерьеров реализованы через **пикапы** (см. [Мир и системы](world)).
- Интерьеры используют игровые системы: банк → [Банк](bank), DMV → [Документы](documents),
  автосалон → [Транспорт](vehicles).
- Стриминг объектов сверх лимитов обеспечивает плагин `streamer` (см. [Библиотеки → Плагины](../libraries/plugins)).

## Данные маппинга

Часть данных маппинга хранится в таблице `mapping` (см. [База данных](../database)).
