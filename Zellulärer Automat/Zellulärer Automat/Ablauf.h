#pragma once
#include "Automat.h"
class Ablauf
{
private:
	bool stop = false, pause = false;
	_CONSOLE_CURSOR_INFO cursor;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	_CONSOLE_SCREEN_BUFFER_INFO sbuffer;
	std::string inputString;
	Automat aut;
public:
	//Input options while paused
	void pauseInput();
	//Input options during regular mode
	void regularInput();
	//Prompts you with the different options to start the automaton
	Ablauf();

	void swapPause();

	bool getPause() { return pause; }
	bool getStop() { return stop; }
};

