// Возвращает номер дня недели (0 = воскресенье, 1 = понедельник, ..., 6 = суббота)
// Если day, month, year равны 0, используется текущая дата
GetWeekDayNum(day = 0, month = 0, year = 0)
{
    // Проверка входных данных
    if (!day || !month || !year)
    {
        getdate(year, month, day);
    }

    // Проверка корректности даты
    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1)
    {
        return -1; // Возвращаем -1 в случае некорректной даты
    }

    // Корректировка для января и февраля
    if (month <= 2)
    {
        month += 12;
        year--;
    }

    // Вычисление компонентов года
    new century = year / 100; // Столетие
    new yearInCentury = year % 100; // Год в пределах столетия

    // Оптимизированная формула для вычисления дня недели
    new dayOfWeek = (day + ((month + 1) * 26) / 10 + yearInCentury + yearInCentury / 4 + century / 4 - 2 * century) % 7;

    // Обеспечение положительного результата (0-6)
    if (dayOfWeek < 0)
    {
        dayOfWeek += 7;
    }

    return dayOfWeek;
}