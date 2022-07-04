/* ConsoleDisplay.h */
#ifndef CONSOLE_DISPLAY_H
#define CONSOLE_DISPLAY_H
#include <Windows.h>
HANDLE initConsoleHandler(); //초기화
void closeConsoleHandler(HANDLE hndlr); //종료
int gotoxy(HANDLE consoleHandler, int x, int y);//콘솔에서 커서 옮기기
#endif

