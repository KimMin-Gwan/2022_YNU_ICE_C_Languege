#include <stdio.h>
#include "ConsoleDisplay.h"
HANDLE consoleHandler; HANDLE initConsoleHandler()
{
	HANDLE stdCnslHndlr;
	stdCnslHndlr = GetStdHandle(STD_OUTPUT_HANDLE); //½ºÅÙ´Ùµå ¾Æ¿ôÇ²
	consoleHandler = stdCnslHndlr; 
	return consoleHandler;
}
void closeConsoleHandler(HANDLE hndlr)
{
	CloseHandle(hndlr); //Çîµé Á¾·á
}
int gotoxy(HANDLE consHndlr, int x, int y)
{
	if (consHndlr == INVALID_HANDLE_VALUE) return 0; COORD coords = { static_cast<short>(x), static_cast<short>(y) }; //Ä¿¼­ À§Ä¡ Á¶Á¤
	SetConsoleCursorPosition(consHndlr, coords);
}