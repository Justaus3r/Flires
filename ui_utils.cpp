#include <iostream>
#include <windows.h>
#include "ui_utils.h"


HANDLE getStdOutHndl() {
	// reference: https://learn.microsoft.com/en-us/windows/console/getstdhandle

	return GetStdHandle(STD_OUTPUT_HANDLE);
}


void setWindowTitle(LPCSTR winTitle) {
	//reference: https://learn.microsoft.com/en-us/windows/console/setconsoletitle
	BOOL _ = SetConsoleTitle(winTitle);
}


void setWindowSize(COORD winSize) {
	//reference: https://learn.microsoft.com/en-us/windows/console/setconsoledisplaymode
	HANDLE stdOutHndl = getStdOutHndl();
	BOOL _ = SetConsoleDisplayMode(stdOutHndl, CONSOLE_WINDOWED_MODE, &winSize);
}

void centerWindowPos() {
	//reference: https://learn.microsoft.com/en-us/windows/console/setconsolewindowinfo
	HANDLE stdOutHndl = getStdOutHndl();

}

void clearStdOut() {
	// reference: https://learn.microsoft.com/en-us/windows/console/clearing-the-screen
	// emulating the behaviour of cls.exe on cmd.exe
	
	HANDLE stdOutHndl = getStdOutHndl();
	SMALL_RECT screenScrollRectngl;
	COORD targetScroll;
	CONSOLE_SCREEN_BUFFER_INFO bInfo;
	CHAR_INFO cInfo;
	if (!GetConsoleScreenBufferInfo(stdOutHndl, &bInfo))
	{
		return;
	}

	//get the entire screen buffer into SMALL_RECT datatype to scroll off
	screenScrollRectngl.Left = 0;
	screenScrollRectngl.Top = 0;
	screenScrollRectngl.Bottom = bInfo.dwSize.Y;
	screenScrollRectngl.Right = bInfo.dwSize.X;
	
	// we only want to scroll vertically(Y), so scroll upwards to top with val of Y
	targetScroll.X = 0;
	targetScroll.Y = (SHORT)(0 - bInfo.dwSize.Y);


	// fill the buffer with empty spaces
	cInfo.Char.UnicodeChar = TEXT(' ');
	cInfo.Attributes = bInfo.wAttributes;

	ScrollConsoleScreenBuffer(stdOutHndl, &screenScrollRectngl, NULL, targetScroll, &cInfo);

	bInfo.dwCursorPosition.X = 0;
	bInfo.dwCursorPosition.X = 0;
}



bool moveToPos(COORD conCoords) {
	// reference: https://learn.microsoft.com/en-us/windows/console/setconsolecursorposition

	HANDLE stdOutHndl = getStdOutHndl();
	BOOL status = SetConsoleCursorPosition(stdOutHndl, conCoords);
	if (status > 0) 
	{
		return true;
	}
	return false;
}

void writeToStdout(COORD pos, std::string writable, WORD wAttr) {
	//reference: 
	// 1:https://learn.microsoft.com/en-us/windows/console/writeconsole
	// 2: https://learn.microsoft.com/en-us/windows/console/setconsoletextattribute
	// 3:https://learn.microsoft.com/en-us/windows/console/console-screen-buffers#character-attributes

	HANDLE stdOutHndl = getStdOutHndl();
	bool status = moveToPos(pos);
	if (status < 1)
	{
		return;
	}
	DWORD sizeBytes = (DWORD)writable.size();
	const char* writableCType = writable.c_str();
	BOOL writeConStat = WriteConsole(stdOutHndl, writableCType, sizeBytes, NULL ,NULL);
	BOOL setTxtAttrStat = SetConsoleTextAttribute(stdOutHndl, wAttr);
}


TerminalCoords get_terminal_size() {
	//reference:  https://learn.microsoft.com/en-us/windows/console/getconsolescreenbufferinfo
	TerminalCoords tP;
	HANDLE stdOutHndl = getStdOutHndl();
	CONSOLE_SCREEN_BUFFER_INFO bufInfo;
	BOOL fncCallStatus = GetConsoleScreenBufferInfo(stdOutHndl, &bufInfo);
	if (fncCallStatus == 0) 
	{
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

PromptCreator::PromptCreator(){
}

bool PromptCreator::attachToCommunicator() {
	;
}

COORD PromptCreator::createPrompt() {
	
	
}

void PromptCreator::addRow(std::string row, WORD rowWAttr, bool isTitle=false) {
	this->isTitle = isTitle;
	this->rows.push_back(row);
	this->rowWAttrs.push_back(rowWAttr);
}
