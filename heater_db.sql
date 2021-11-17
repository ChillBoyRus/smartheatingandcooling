-- phpMyAdmin SQL Dump
-- version 4.9.7
-- https://www.phpmyadmin.net/
--
-- Хост: localhost
-- Время создания: Ноя 17 2021 г., 16:54
-- Версия сервера: 5.7.21-20-beget-5.7.21-20-1-log
-- Версия PHP: 5.6.40

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- База данных: `davideqc_heater`
--

-- --------------------------------------------------------

--
-- Структура таблицы `heater`
--
-- Создание: Ноя 16 2021 г., 07:33
-- Последнее обновление: Ноя 16 2021 г., 12:02
--

DROP TABLE IF EXISTS `heater`;
CREATE TABLE `heater` (
  `id` int(11) NOT NULL,
  `temp` int(11) NOT NULL,
  `realtemp` int(11) NOT NULL,
  `mode` int(11) NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Дамп данных таблицы `heater`
--

INSERT INTO `heater` (`id`, `temp`, `realtemp`, `mode`) VALUES
(1, 29, 22, 2);

--
-- Индексы сохранённых таблиц
--

--
-- Индексы таблицы `heater`
--
ALTER TABLE `heater`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT для сохранённых таблиц
--

--
-- AUTO_INCREMENT для таблицы `heater`
--
ALTER TABLE `heater`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
