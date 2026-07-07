#if defined PHONE_CLOCK_INCLUDED
	#endinput
#endif
#define PHONE_CLOCK_INCLUDED

// Russian month names (genitive) and weekday names for the smartphone clock.
// IMPORTANT: keep this file saved in Windows-1251 (cp1251) encoding, otherwise
// the Cyrillic below turns into mojibake on the phone screen.
static const PhoneMonthNames[12][16] =
{
	"января", "февраля", "марта", "апреля", "мая", "июня",
	"июля", "августа", "сентября", "октября", "ноября", "декабря"
};

static const PhoneWeekDayNames[7][16] =
{
	"Воскресенье", "Понедельник", "Вторник", "Среда",
	"Четверг", "Пятница", "Суббота"
};

// Refreshes the smartphone status-bar/lock-screen clock with the real date/time.
// iPhone[12]/[32] = time, iPhone[33] = weekday, iPhone[34] = day + month.
PhoneUpdateClock()
{
	new hour, minute, second, year, month, day;
	gettime(hour, minute, second);
	getdate(year, month, day);

	new buf[32];
	format(buf, sizeof(buf), "%02d:%02d", hour, minute);
	TextDrawSetString(iPhone[12], buf);
	TextDrawSetString(iPhone[32], buf);

	new wd = GetWeekDayNum(day, month, year);
	if(wd < 0 || wd > 6)
		wd = 0;
	TextDrawSetString(iPhone[33], RusText(PhoneWeekDayNames[wd]));

	if(month < 1 || month > 12)
		month = 1;
	format(buf, sizeof(buf), "%d %s", day, PhoneMonthNames[month - 1]);
	TextDrawSetString(iPhone[34], RusText(buf));
	return true;
}