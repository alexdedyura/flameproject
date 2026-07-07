-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Хост: 127.0.0.1
-- Время создания: Сен 17 2025 г., 17:22
-- Версия сервера: 10.4.32-MariaDB
-- Версия PHP: 8.2.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+03:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- База данных: `flame`
--

-- --------------------------------------------------------

--
-- Структура таблицы `accounts`
--

CREATE TABLE `accounts` (
  `id` int(11) NOT NULL,
  `name` varchar(24) NOT NULL,
  `password` varchar(32) NOT NULL,
  `mail` varchar(32) NOT NULL,
  `gender` int(11) NOT NULL,
  `default_skin` int(11) NOT NULL,
  `money` int(11) NOT NULL DEFAULT 200,
  `bank_money` int(11) NOT NULL DEFAULT 0,
  `bank_last_use` int(11) NOT NULL DEFAULT 0,
  `reg_ip` varchar(16) NOT NULL,
  `RegDate` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp(),
  `last_ip` varchar(16) NOT NULL DEFAULT '',
  `admin` int(11) NOT NULL DEFAULT 0,
  `ChatSettings` varchar(16) NOT NULL DEFAULT '1 1 1 1 1',
  `MappingSlotsNames` varchar(128) NOT NULL DEFAULT '---|---|---',
  `Kills` int(11) NOT NULL DEFAULT 0,
  `Deaths` int(11) NOT NULL DEFAULT 0,
  `Comment` varchar(256) NOT NULL DEFAULT '',
  `Warns` int(11) NOT NULL DEFAULT 0,
  `rp_exp` int(11) NOT NULL DEFAULT 0,
  `rp_level` int(11) NOT NULL DEFAULT 0,
  `desc_text` varchar(128) NOT NULL DEFAULT '',
  `desc_time` int(11) NOT NULL DEFAULT 0,
  `quest_progress` int(11) NOT NULL DEFAULT 0,
  `age` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `bank_transactions`
--

CREATE TABLE `bank_transactions` (
  `ID` int(11) NOT NULL,
  `AccountID` int(11) NOT NULL,
  `Type` tinyint(4) NOT NULL,
  `Amount` int(11) NOT NULL,
  `RelatedAccountID` int(11) NOT NULL DEFAULT 0,
  `RelatedName` varchar(24) NOT NULL DEFAULT '',
  `Date` int(11) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `bank_settings`
--

CREATE TABLE `bank_settings` (
  `ID` int(11) NOT NULL,
  `SettingName` varchar(32) NOT NULL DEFAULT '',
  `InterestRate` float NOT NULL DEFAULT 0
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;

--
-- Дамп данных таблицы `bank_settings`
--

INSERT INTO `bank_settings` (`ID`, `SettingName`, `InterestRate`) VALUES
(1, 'deposit_interest_rate', 0);

-- --------------------------------------------------------

--
-- Структура таблицы `actors`
--

-- --------------------------------------------------------

--
-- Smartphone SMS messages
--

CREATE TABLE `phone_messages` (
  `ID` int(11) NOT NULL,
  `SenderID` int(11) NOT NULL,
  `ReceiverID` int(11) NOT NULL,
  `DialogLowID` int(11) NOT NULL,
  `DialogHighID` int(11) NOT NULL,
  `Message` varchar(144) NOT NULL DEFAULT '',
  `Date` int(11) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
CREATE TABLE `actors` (
  `id` int(11) NOT NULL,
  `skin` int(11) NOT NULL,
  `name` varchar(32) NOT NULL,
  `inv` int(11) NOT NULL,
  `posX` float NOT NULL,
  `posY` float NOT NULL,
  `posZ` float NOT NULL,
  `posFA` float NOT NULL,
  `vw` int(11) NOT NULL,
  `int` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `bus_stops`
--

CREATE TABLE `bus_stops` (
  `id` int(11) NOT NULL,
  `name` varchar(64) NOT NULL,
  `pos_x` float NOT NULL,
  `pos_y` float NOT NULL,
  `pos_z` float NOT NULL,
  `pos_fa` float NOT NULL,
  `type` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;

--
-- Дамп данных таблицы `bus_stops`
--

INSERT INTO `bus_stops` (`id`, `name`, `pos_x`, `pos_y`, `pos_z`, `pos_fa`, `type`) VALUES
(1, 'Аэропорт Сан-Фиерро №1', -1466.71, -271.615, 14.15, 165.916, 0),
(2, 'Аэропорт Сан-Фиерро №2', -1386.82, -351.698, 14.1484, 103.708, 0),
(3, 'Правительство', -2754.93, 395.466, 4.3359, 273.47, 0),
(4, 'Департамент автотранспорта (DMV)', -2023.98, -76.0007, 35.3203, 354.752, 0),
(5, 'Национальный банк', -1603.43, 860.165, 7.6875, 182.035, 0),
(6, 'Центральный Департамент Полиции', -1625.49, 723.279, 14.6094, 4.391, 0),
(7, 'Центральный Госпиталь', -2589.55, 573.879, 14.6137, 181.244, 0),
(8, 'Военно-Морской Флот США', -1549.57, 529.159, 7.1797, 93.3741, 0),
(9, 'Телеканал CNN', -2408.03, -617.359, 132.554, 128.688, 0),
(10, 'Стадион \"San-Fierro Arena\"', -2120.22, -367.045, 35.2772, 98.3851, 0),
(11, 'Частный таксопарк \"Uber\"', -1995.36, -845.639, 32.1719, 274.64, 1),
(12, 'IT компания \"Apple\"', -1973.08, -865.15, 32.2266, 0.8654, 1),
(13, 'Завод по производству техники \"Foxconn\"', -2013.73, -1011.26, 32.1719, 2.9041, 1),
(14, 'Транспортная компания \"FedEX\"', -1959.19, -1011.71, 32.1719, 2.426, 1),
(15, 'Телекоммуникационная компания \"Verizon\"', -1766.76, 859.33, 24.8828, 180.363, 1),
(16, 'Автосалон \"Richmond Automotive\"', -1986.82, 280.58, 34.4277, 358.515, 6),
(17, 'Каршеринг \"Getaround\"', -2517.46, 2324.74, 4.9844, 354.35, 6);

-- --------------------------------------------------------

--
-- Структура таблицы `documents`
--

CREATE TABLE `documents` (
  `id` int(11) NOT NULL,
  `acc_id` int(11) NOT NULL,
  `type` int(11) NOT NULL,
  `issued` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp(),
  `expired` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  `param1` int(11) NOT NULL DEFAULT 0,
  `param2` int(11) NOT NULL DEFAULT 0,
  `param3` int(11) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `inventory`
--

CREATE TABLE `inventory` (
  `id` int(11) NOT NULL,
  `item_ids` varchar(128) NOT NULL DEFAULT '0',
  `item_nums` varchar(128) NOT NULL DEFAULT '0',
  `item_amount` varchar(128) NOT NULL DEFAULT '0',
  `item_info` varchar(128) DEFAULT ''
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `mapping`
--

CREATE TABLE `mapping` (
  `id` int(11) NOT NULL,
  `player_id` int(11) NOT NULL,
  `slot` int(11) NOT NULL,
  `modelid` int(11) NOT NULL,
  `pos_x` float NOT NULL,
  `pos_y` float NOT NULL,
  `pos_z` float NOT NULL,
  `rot_x` float NOT NULL,
  `rot_y` float NOT NULL,
  `rot_z` float NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `pickups`
--

CREATE TABLE `pickups` (
  `id` int(11) NOT NULL,
  `name` varchar(32) NOT NULL,
  `enter_pos_x` float NOT NULL,
  `enter_pos_y` float NOT NULL,
  `enter_pos_z` float NOT NULL,
  `enter_pos_fa` float NOT NULL,
  `enter_pos_vw` int(11) NOT NULL,
  `enter_pos_int` int(11) NOT NULL,
  `exit_pos_x` float NOT NULL,
  `exit_pos_y` float NOT NULL,
  `exit_pos_z` float NOT NULL,
  `exit_pos_fa` float NOT NULL,
  `exit_pos_vw` int(11) NOT NULL,
  `exit_pos_int` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;

--
-- Дамп данных таблицы `pickups`
--

INSERT INTO `pickups` (`id`, `name`, `enter_pos_x`, `enter_pos_y`, `enter_pos_z`, `enter_pos_fa`, `enter_pos_vw`, `enter_pos_int`, `exit_pos_x`, `exit_pos_y`, `exit_pos_z`, `exit_pos_fa`, `exit_pos_vw`, `exit_pos_int`) VALUES
(7, 'Стадион \"San Fierro Arena\"', -2109.66, -444.066, 38.7344, 272.324, 0, 0, -2055.34, -478.343, 516.7, 337.099, 7, 3),
(22, 'Национальный банк', -1600.16, 873.828, 9.2298, 359.287, 0, 0, -1672.82, 950.518, 693.449, 87.4577, 15, 3),
(33, 'Правительство', -2766.55, 375.56, 6.3347, 88.9063, 0, 0, 1466.85, -1744.32, 3910.09, 88.4302, 9, 3),
(34, 'Выход на парковку', 1493.25, -1740.07, 3910.09, 269.202, 9, 3, -2800.15, 375.578, 6.3359, 272.213, 0, 0),
(35, 'Лифт №1', 1476.56, -1756.06, 3910.09, 178.673, 9, 3, 1476.54, -1749.28, 4510.09, 180.761, 9, 3),
(36, 'Лифт №2', 1476.57, -1732.64, 3910.09, 358.423, 9, 3, 1476.54, -1737.15, 4510.09, 0.6164, 9, 3),
(37, 'Третий этаж', 1499.55, -1731.99, 4510.09, 267.323, 9, 3, 1487.03, -1750.22, 5010.09, 0.7442, 9, 3),
(44, 'Автосалон \"Richmond\"', -1966.58, 293.925, 35.4687, 271.42, 0, 0, -2078.03, 221.684, 827.243, 179.584, 44, 3),
(77, 'Департамент автотранспорта (DMV)', -2022.24, -105.032, 36.1177, 179.957, 0, 0, -2037.26, -171.115, 515.404, 181.614, 17, 3),
(78, 'Выход на парковку', -2037.56, -143.085, 515.404, 0.5167, 17, 3, -2020.47, -122.017, 35.1981, 358.352, 0, 0);

-- --------------------------------------------------------

--
-- Структура таблицы `vehicles`
--

CREATE TABLE `vehicles` (
  `id` int(11) NOT NULL,
  `model` int(11) NOT NULL,
  `type` int(11) NOT NULL DEFAULT 0,
  `owner_id` int(11) NOT NULL DEFAULT 0,
  `owner_name` varchar(16) NOT NULL,
  `spawn_pos_x` float NOT NULL DEFAULT 0,
  `spawn_pos_y` float NOT NULL DEFAULT 0,
  `spawn_pos_z` float NOT NULL DEFAULT 0,
  `spawn_pos_fa` float NOT NULL DEFAULT 0,
  `spawn_pos_int` int(11) NOT NULL DEFAULT 0,
  `spawn_pos_vw` int(11) NOT NULL DEFAULT 0,
  `numbers` varchar(16) NOT NULL DEFAULT '',
  `buy_time` int(11) NOT NULL DEFAULT 0,
  `mileage` float NOT NULL DEFAULT 0,
  `fuel` float NOT NULL DEFAULT 0,
  `color1` int(11) NOT NULL DEFAULT 1,
  `color2` int(11) NOT NULL DEFAULT 1,
  `complectation` int(11) NOT NULL DEFAULT 0,
  `tax_weeks` int(11) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;

--
-- Индексы сохранённых таблиц
--

--
-- Индексы таблицы `accounts`
--
ALTER TABLE `accounts`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `bank_transactions`
--
ALTER TABLE `bank_transactions`
  ADD PRIMARY KEY (`ID`),
  ADD KEY `account_date` (`AccountID`,`Date`);

--
-- Индексы таблицы `bank_settings`
--
ALTER TABLE `bank_settings`
  ADD PRIMARY KEY (`ID`),
  ADD UNIQUE KEY `setting_name` (`SettingName`);

--
-- Индексы таблицы `actors`
--
--
-- Indexes for table `phone_messages`
--
ALTER TABLE `phone_messages`
  ADD PRIMARY KEY (`ID`),
  ADD KEY `dialog_id` (`DialogLowID`,`DialogHighID`,`ID`),
  ADD KEY `receiver_date` (`ReceiverID`,`Date`);
ALTER TABLE `actors`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `id` (`id`);

--
-- Индексы таблицы `bus_stops`
--
ALTER TABLE `bus_stops`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `documents`
--
ALTER TABLE `documents`
  ADD UNIQUE KEY `id` (`id`);

--
-- Индексы таблицы `inventory`
--
ALTER TABLE `inventory`
  ADD UNIQUE KEY `id` (`id`);

--
-- Индексы таблицы `mapping`
--
ALTER TABLE `mapping`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `pickups`
--
ALTER TABLE `pickups`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `vehicles`
--
ALTER TABLE `vehicles`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT для сохранённых таблиц
--

--
-- AUTO_INCREMENT для таблицы `accounts`
--
ALTER TABLE `accounts`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `bank_transactions`
--
ALTER TABLE `bank_transactions`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `actors`
--

--
-- AUTO_INCREMENT for table `phone_messages`
--
ALTER TABLE `phone_messages`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT;
ALTER TABLE `actors`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `bus_stops`
--
ALTER TABLE `bus_stops`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `documents`
--
ALTER TABLE `documents`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `mapping`
--
ALTER TABLE `mapping`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `pickups`
--
ALTER TABLE `pickups`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=79;

--
-- AUTO_INCREMENT для таблицы `vehicles`
--
ALTER TABLE `vehicles`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
