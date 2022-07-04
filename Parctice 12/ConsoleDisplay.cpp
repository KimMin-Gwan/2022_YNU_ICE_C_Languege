/* ConsoleDisplay.cpp */
#include <stdio.h>
#include "ConsoleDisplay.h"
HANDLE consoleHandler;
HANDLE initConsoleHandler()
{
	HANDLE stdCnslHndlr;
	stdCnslHndlr = GetStdHandle(STD_OUTPUT_HANDLE); //스텐다드 아웃풋
	consoleHandler = stdCnslHndlr;
	return consoleHandler;
}

void closeConsoleHandler(HANDLE hndlr) //핸들러 작동 중기
{
	CloseHandle(hndlr);
}

int gotoxy(HANDLE consHndlr, int x, int y) //콘솔에서 커서 위치 바꾸기
{
	if (consHndlr == INVALID_HANDLE_VALUE)
		return 0;
	COORD coords = { static_cast<short>(x), static_cast<short>(y) };
	SetConsoleCursorPosition(consHndlr, coords);
}

