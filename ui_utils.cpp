#include <iostream>
#include <Windows.h>
#include <WinUser.h>
#include <string>
#include <cstring>
#include <math.h>
#include <conio.h>
#include <ctype.h>
#include "ui_utils.h"


HANDLE getStdOutHndl() {
	// reference: https://learn.microsoft.com/en-us/windows/console/getstdhandle

	return GetStdHandle(STD_OUTPUT_HANDLE);
}


BOOL setWindowTitle(LPCTSTR winTitle) {
	//reference: https://learn.microsoft.com/en-us/windows/console/setconsoletitle
	BOOL _ = SetConsoleTitle(winTitle);
	return _;
}



BOOL setWindowPosNSize(COORD winSize) {
	//reference: https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-movewindow

		int asciiCharPixHeight = 16;
		int asciiCharPixWidth = 8;

		// the normal formula i got from gpt to convert
		// characters to pixels was:
		// pixSize = characters * (font height * fontwidth)
		// which calculated the pixel count for the grid,
		// but since we want pixel count in 1D, we will only multiply with the specific axis

		int pixWinSizeX = winSize.X * (asciiCharPixWidth);
		int pixWinSizeY = winSize.Y * (asciiCharPixHeight);

		int scrResX = GetSystemMetrics(SM_CXSCREEN); 
		int scrResY = GetSystemMetrics(SM_CYSCREEN); 

		// the usual formula for centering:
		// half of the window - half of the width of thing 
		int centerPosPixX = scrResX / 2 - pixWinSizeX / 2;
		int centerPosPixY = scrResY / 2 - pixWinSizeY / 2;

		BOOL _ = MoveWindow(GetConsoleWindow(), centerPosPixX, centerPosPixY, pixWinSizeX,	pixWinSizeY, TRUE);
		return _;
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
	bInfo.dwCursorPosition.Y = 0;
	SetConsoleCursorPosition(stdOutHndl, bInfo.dwCursorPosition);
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
	if (!status)
	{
		return;
	}
	DWORD sizeBytes = (DWORD)writable.size();
	const char* writableCType = writable.c_str();

	BOOL setTxtAttrStat = SetConsoleTextAttribute(stdOutHndl, wAttr);
	BOOL writeConStat = WriteConsole(stdOutHndl, writableCType, sizeBytes, NULL, NULL);	
	// doing bitwise OR of FOREGROUND_INTENSITY, foreground red, blue and green to get forground white
	// reference: https://stackoverflow.com/a/17125539
	BOOL resetTxtAttrStat = SetConsoleTextAttribute(stdOutHndl, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}


COORD getTerminalSize() {
	//reference:  https://learn.microsoft.com/en-us/windows/console/getconsolescreenbufferinfo
	COORD tS;
	HANDLE stdOutHndl = getStdOutHndl();
	CONSOLE_SCREEN_BUFFER_INFO bufInfo;
	BOOL fncCallStatus = GetConsoleScreenBufferInfo(stdOutHndl, &bufInfo);
	if (fncCallStatus == 0)
	{
		tS.X = 0;
		tS.Y = 0;
		return tS;
	}

	/* As done by some MS - Docs that i have forgotten about
	basically srWindow.Right has the total number of columns in console
	and srWindow.Left is probably 0 or 1. doing the arithematics below
	we get the X -> columns in our console. Similarly srWindow.Bottom has
	total number of rows in the console with .Left being the same.
	Don't know about + 1 tho
	*/
	tS.X = bufInfo.srWindow.Right - bufInfo.srWindow.Left + 1;
	tS.Y = bufInfo.srWindow.Bottom - bufInfo.srWindow.Left + 1;

	return tS;
}

SHORT generateErrorMsg(const char* errMsg, int afterSleep = 0) {
	int msgLen = std::strlen(errMsg);
	COORD termSize = getTerminalSize();
	termSize.X = termSize.X / 2 - msgLen / 2;
	writeToStdout(termSize, errMsg, BACKGROUND_RED | FOREGROUND_INTENSITY);
	Sleep(afterSleep);
	return termSize.X;
}

void clearMsg(int msgLen, int startX, int Y) {
	std::string whiteSpaceStr = "";
	for (int i = 0; i < msgLen; i++)
	{
		whiteSpaceStr += " ";
	}
	COORD termPos = {startX, Y};//getTerminalSize();
	writeToStdout(termPos, whiteSpaceStr, WHITE);	
}

void clearErrorMsg(int msgLen, int startX)
{
    // for some reason calling getTerminalSize() at pos other than {0,0}
	// results in a Y+1
	moveToPos({ 0,0 });
	COORD termSz = getTerminalSize();

	clearMsg(msgLen, startX, termSz.Y);

}

PromptCreator::PromptCreator(const char *promptName, char const* promptTitle, \
		WORD titleTxtAttrs) 
{
	this->promptName = promptName;
	this->promptTitle = promptTitle;
	this->titleTxtAttrs = titleTxtAttrs;
}

COORD PromptCreator::createPrompt() {
	COORD afterPromptCoords;
	COORD termSize = getTerminalSize();	
	SHORT centerX = termSize.X / 2 - this->maxRowSize / 2;
	SHORT centerY = termSize.Y / 2 - ceil(this->rows.size() / 2.0);
	//std::cout << centerX << " " << centerY << std::endl;	
	COORD rowPos = { centerX, centerY };
	if (this->promptTitle)
	{
		COORD titlePos = { termSize.X / 2 - (std::strlen(this->promptTitle) / 2), centerY - 2 };
		writeToStdout(titlePos, this->promptTitle, this->titleTxtAttrs);
	}
	int _counter = 0;
	int rowSize = rows.size();
	while (_counter < rowSize)
	{
		std::string queueTopElement = this->rows[_counter];
		WORD rowTxtAttr = this->rowWAttrs[_counter];
		writeToStdout(rowPos, queueTopElement, rowTxtAttr);
		rowPos.Y++;
		_counter++;
	}
	afterPromptCoords = { centerX + this->rowsSize.back(), --rowPos.Y};
	return afterPromptCoords;
}

void PromptCreator::addRow(std::string row, WORD rowWAttr) {
	this->rows.push_back(row);
	this->rowWAttrs.push_back(rowWAttr);
	if (this->maxRowSize < row.size())
	{
		this->maxRowSize = (SHORT)row.size();
	}
	this->rowsSize.push_back(row.size());
	this->maxRowSize = maxRowSize;
}

void PromptCreator::promptInput(void *dataPtr , enum Datatype dTyp, COORD afterPromptCoords) {
	switch (dTyp)
	{
		case(INT_TYPE):
		{
			int* dtaPtrI = (int*)dataPtr;
			std::cin >> *dtaPtrI;
			break;
		}
		case(FLOAT_TYPE):
		{
			float* dtaPtrF = (float*)dataPtr;
			std::cin >> *dtaPtrF;
			break;
		}

		case(STRING_TYPE):
		{
			std::string* dtaPtrS = (std::string*)dataPtr;
			getline(std::cin, *dtaPtrS);
			break;
		}

		case(DATE_TYPE):
		{
			const int DATE_SIZE = 10;
			std::string* dtaPtrD = (std::string*)dataPtr;
			
			while (true)
			{	
				bool success = true;
				getline(std::cin, *dtaPtrD);
				if (dtaPtrD->size() != 10)
				{
					success = false;
				}
				
				if (dtaPtrD->at(2) != '/' || dtaPtrD->at(5) != '/')
				{
					success = false;
				}
			
				for (int i = 0; i < dtaPtrD->size(); i++)
				{
					if (i == 2 || i == 5) continue;
					if (!isdigit(dtaPtrD->at(i))) {
						success = false;
						break;
					}
				}

				if (!success)

				{
					const char* errMsg = "Invalid Date Format!, Re-input in 2s..";
					int msgSize = std::strlen(errMsg);
					SHORT startX = generateErrorMsg(errMsg, 2000);
					//int startX = trmSz.X / 2 - msgSize / 2;
					clearErrorMsg(msgSize, startX);
					moveToPos(afterPromptCoords);
					clearMsg(dtaPtrD->size(), afterPromptCoords.X, afterPromptCoords.Y);
					moveToPos(afterPromptCoords);
					continue;
				}
				break;
			}
		}

		case(SELECTION_TYPE):
		{
			char* dataPtrC = (char*)dataPtr;
			*dataPtrC = _getch();
			break;
		}

	}
}

void PromptCreator::addChild(PromptCreator* child) {
	this->children.push_back(child);
}

void PromptCreator::setPromptActionDriver(void (*actionCallback)(callbackArgs* cA)) {
	this->actionCallback = actionCallback;
}

void PromptCreator::execpromptActionDriver(callbackArgs* cA) {
	this->actionCallback(cA);
}
