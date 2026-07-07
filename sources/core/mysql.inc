#include <YSI_Coding\y_hooks>


new ConnectMySQL;

#define MYSQL_HOST		"localhost"
#define MYSQL_USER 		"root"
#define MYSQL_PASS		""
#define MYSQL_BASE		"flame"

hook OnGameModeInit()
{
	ConnectMySQL = mysql_connect(MYSQL_HOST, MYSQL_USER, MYSQL_BASE, MYSQL_PASS);
	mysql_log(LOG_ERROR | LOG_WARNING, LOG_TYPE_HTML);
	if(mysql_errno(ConnectMySQL) == 0) print("Подключение к базе данных успешно установлено!");
	else printf("Подключение к базе данных не установлено! Ошибка: %i", mysql_errno(ConnectMySQL));

    new __ms8[] = !"SET CHARACTER SET 'utf8'";
    mysql_tquery(ConnectMySQL, __ms8);
    new __ms7[] = !"SET NAMES 'utf8'";
    mysql_tquery(ConnectMySQL, __ms7);
    new __ms6[] = !"SET character_set_client = 'cp1251'";
    mysql_tquery(ConnectMySQL, __ms6);
    new __ms5[] = !"SET character_set_connection = 'cp1251'";
    mysql_tquery(ConnectMySQL, __ms5);
    new __ms4[] = !"SET character_set_results = 'cp1251'";
    mysql_tquery(ConnectMySQL, __ms4);
    new __ms3[] = !"SET SESSION collation_connection = 'utf8_general_ci'";
    mysql_tquery(ConnectMySQL, __ms3);
}

UpdateBaseInt(const table[], const field[], amount, id)
{
	new ms_string[256];
	new __ms2[] = "UPDATE `%s` SET `%s` = '%i' WHERE `ID` = '%i'";
	mysql_format(ConnectMySQL, ms_string, sizeof(ms_string), __ms2, table, field, amount, id);
	mysql_tquery(ConnectMySQL, ms_string);
	return true;
}

UpdateBaseStr(const table[], const field[], const amount[], id)
{
	new ms_string[256];
	new __ms1[] = "UPDATE `%s` SET `%s` = '%s' WHERE `ID` = '%i'";
	mysql_format(ConnectMySQL, ms_string, sizeof(ms_string), __ms1, table, field, amount, id);
	mysql_tquery(ConnectMySQL, ms_string);
	return true;
}

stock UpdateBaseFloat(const table[], const field[], const amount[], id)
{
	new ms_string[256];
	new __ms0[] = "UPDATE `%s` SET `%s` = '%f' WHERE `ID` = '%i'";
	mysql_format(ConnectMySQL, ms_string, sizeof(ms_string), __ms0, table, field, amount, id);
	mysql_tquery(ConnectMySQL, ms_string);
	return true;
}
