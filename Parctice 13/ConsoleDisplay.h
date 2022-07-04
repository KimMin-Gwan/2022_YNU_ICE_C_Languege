#ifndef CONSOLE_DISPLAY_H
#define CONSOLE_DISPLAY_H
#include <Windows.h>
HANDLE initConsoleHandler(); // 콘솔 제어기 초기화
void closeConsoleHandler(HANDLE hndlr); 
int gotoxy(HANDLE consoleHandler, int x, int y); //콘솔 제어
#endif