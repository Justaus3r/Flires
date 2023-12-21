
#include <iostream>
#include <Windows.h>
#include "ui_utils.h"


HANDLE getStdOutHndl() {
	// reference: https://learn.microsoft.com/en-us/windows/console/getstdhandle

	return GetStdHandle(STD_OUTPUT_HANDLE);
}

void writeToStdout() {
	;
}

void clearScreen() {
	// ANSI Escape sequence for clearing the terminal
	// reference: https://en.wikipedia.org/wiki/ANSI_escape_code
	std::cout<<"\x1b[2J";
}



bool moveToPos(COORD conCoords) {
	// reference: https://learn.microsoft.com/en-us/windows/console/setconsolecursorposition

	HANDLE stdOutHndl = getStdOutHndl();
	BOOL status = SetConsoleCursorPosition(stdOutHndl, conCoords);
	if (status > 0) {
		return true;
	}
	return false;
}

TerminalPosition get_terminal_size() {
	//reference:  https://learn.microsoft.com/en-us/windows/console/getconsolescreenbufferinfo
	TerminalPosition tP;
	HANDLE stdOutHndl = getStdOutHndl();
	CONSOLE_SCREEN_BUFFER_INFO bufInfo;
	BOOL fncCallStatus = GetConsoleScreenBufferInfo(stdOutHndl, &bufInfo);
	if (fncCallStatus == 0) {
		tP.x = 0;
		tP.y = 0;	
		return tP;
	}
	
	/* As done by some MS - Docs that i have forgotten about
	basically srWindow.Right has the total number of columns in console
	and srWindow.Left is probably 0 or 1. doing the arithematics below
	we get the X -> columns in our console. Similarly srWindow.Bottom has 
	total number of rows in the console with .Left being the same.
	Don't know about + 1 tho
	*/
	tP.x = bufInfo.srWindow.Right - bufInfo.srWindow.Left + 1;
	tP.y = bufInfo.srWindow.Bottom - bufInfo.srWindow.Left + 1;
	
	return tP;
}

class PromptCreator {

};
