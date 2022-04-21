#pragma once
#include <Windows.h>
class Zelle
{
public:
	Zelle(COORD pos, bool start);

	bool zustand;
	bool next;
	static int checked;

	void checknext(int nachbarn);
	void executeChange();

	COORD pos;

};

