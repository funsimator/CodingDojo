#include "Zelle.h"
#include <Windows.h>
#include <iostream>

Zelle::Zelle(COORD pos, bool start): next(false)
{
	this->pos = pos;
	zustand = start;
}

//Legt den nächsten Zustand der Zelle, in Abhängigkeit zu ihren Nachbarn fest
void Zelle::checknext(int nachbarn)
{
	next = zustand;
	if (nachbarn + zustand == 3 || nachbarn == 3)
		next = 1;
	else
		next = 0;

		checked++;
}

void Zelle::executeChange()
{

	if (zustand != next)
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { pos.X * 2,pos.Y });
		if (next)std::cout << char(235) << char(235);
		else std::cout << "  ";
	}
	zustand = next;
}




