static const LETTERS[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
static const NUMBERS[] = "0123456789";

GenerateVehicleNumbers(string[], length = sizeof string)
{
	for(new i = 0; i < 7; i++)
	{
		if(0 < i < 4)
			format(string, length, "%s%c", string, LETTERS[random(sizeof(LETTERS))]);
		else
			format(string, length, "%s%c", string, NUMBERS[random(sizeof(NUMBERS))]);
	}
	return true;
}