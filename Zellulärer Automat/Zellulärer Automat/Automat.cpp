#include "Automat.h"
#include <ctime>
#include <filesystem>
#include <stdexcept>
#include <string>
#include <errno.h>
#include <iostream>

namespace fs = std::filesystem;

Automat::Automat(int mode, int prob)
{
	std::string temp;
	for (int x = 0; x < grX; x++)
	{
		for (int y = 0; y < grY; y++)
		{
			feld[y][x] = new Zelle({ short(x),short(y) }, false);
		}
	}
	switch (mode)
	{
	case 2:	srand(std::time(nullptr));
		for (int x = 0; x < grX; x++)
		{
			for (int y = 0; y < grY; y++)
			{

				feld[y][x]->zustand = (rand() % 100 < prob);
			}
		}
		drawEverything();
		break;
	case 1:
		std::cout << "Please enter the filename:";

		std::getline(std::cin, temp);
		loadLayout(temp);
			break;
	case 3:
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0});
		std::cout << "                       \n";
		std::cout << "                       \n";
		std::cout << "                       \n  ";
		break;
	}

}


void Automat::prepareNextStep()
{
	for (int x = 0; x < grX; x++)
	{
		for (int y = 0; y < grY; y++)
		{
			feld[y][x]->checknext(getNeighbors({ short(x),short(y) }));
		}
	}

}
void Automat::executeNextStep()
{
	for (int x = 0; x < grX; x++)
	{
		for (int y = 0; y < grY; y++)
		{
			feld[y][x]->executeChange();
		}
	}
}

int Automat::getNeighbors(COORD pos)
{
	int temp = 0;
	for (int x = -1; x < 2; x++)
	{
		for (int y = -1; y < 2; y++)
		{
			//Wird benötigt im Übergänge am Rand darzustellen
			int realX = x + pos.X, realY = y + pos.Y;
			if (pos.X + x < 0)realX = grX - 1;
			else if ((pos.X + x > grX - 1)) realX = 0;
			if (pos.Y + y < 0)realY = grY - 1;
			else if ((pos.Y + y > grY - 1)) realY = 0;
			if (!(x == 0 && y == 0))
				temp += feld[realY][realX]->zustand;
		}
	}
	return temp;
}

void Automat::saveLayout(std::string filename)try
{
	std::fstream file;
	if (!fs::exists(filename))
		file.open(filename, std::ios::out);
	else throw std::runtime_error("The file: \"" + filename + "\" already exists.\n");

	for (int x = 0; x < grX; x++)
	{
		for (int y = 0; y < grY; y++)
		{
			if (feld[y][x]->zustand)
			{
				file << x << std::endl;
				file << y << std::endl;;
			}

		}
	}
	file.close();

}
catch (std::exception x)
{
	std::cout << x.what();
}
//Loads a Automaton Layout from a file
bool Automat::loadLayout(std::string filename)try
{
	ResetField();

	std::fstream file;
	if (fs::exists(filename))
		file.open(filename, std::ios::in);
	else
	{
		std::cout << "\nThe file: \"" + filename + "\" doesn't exists.\n";
		return false;
	}

	while (!file.eof())
	{
		int koord[2] = { 0 };

		getline(file, inputString);
		koord[0] = stoi(inputString);

		getline(file, inputString);
		koord[1] = stoi(inputString);

		feld[koord[1]][koord[0]]->zustand = true;
	}
	drawEverything();
	return true;

}
catch (...)
{
	std::cout << "\nFile is not a valid layout. Part \"" + inputString + "\" ist causing the error!";
}


void Automat::drawEverything()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	for (int x = 0; x < grX; x++)
	{
		for (int y = 0; y < grY; y++)
		{
			SetConsoleCursorPosition(h, { feld[y][x]->pos.X * 2, feld[y][x]->pos.Y });
			if (feld[y][x]->zustand)std::cout << char(235) << char(235);
			else std::cout << "  ";
		}
	}
}

void Automat::ResetField()
{
	for (int x = 0; x < grX; x++)
	{
		for (int y = 0; y < grY; y++)
		{
			feld[y][x]->zustand = 0;
			feld[y][x]->next = 0;
		}
	}
}
