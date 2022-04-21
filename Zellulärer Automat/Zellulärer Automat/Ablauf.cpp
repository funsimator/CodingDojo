#include "Ablauf.h"
#include <iostream>
#include <conio.h>
#include <thread>
#include <iostream>

void Ablauf::pauseInput()
{
	int iterations = 0;
	if (_kbhit() == true)
	{
		GetConsoleScreenBufferInfo(h, &sbuffer);
		switch (_getch())
		{
		case'w':
			if (sbuffer.dwCursorPosition.Y > 0)SetConsoleCursorPosition(h, { sbuffer.dwCursorPosition.X, sbuffer.dwCursorPosition.Y - 1 });
			break;
		case'a':
			if (sbuffer.dwCursorPosition.X > 0)SetConsoleCursorPosition(h, { sbuffer.dwCursorPosition.X - 2, sbuffer.dwCursorPosition.Y });
			break;
		case's':
			if (sbuffer.dwCursorPosition.Y < aut.grY - 1)SetConsoleCursorPosition(h, { sbuffer.dwCursorPosition.X, sbuffer.dwCursorPosition.Y + 1 });
			break;
		case'd':
			if (sbuffer.dwCursorPosition.Y < aut.grY * 2 - 2)SetConsoleCursorPosition(h, { sbuffer.dwCursorPosition.X + 2, sbuffer.dwCursorPosition.Y });
			break;
		case't':
			swapPause();
			break;
		case'q':
			std::cout << "Please enter name of savefile:";
			std::getline(std::cin, inputString);
			aut.saveLayout(inputString);
			break;
		case'o':
			std::cout << "Please enter filename to load:";
			std::getline(std::cin, inputString);
			aut.loadLayout(inputString);
			break;
		case' ':
			aut.feld[sbuffer.dwCursorPosition.Y][sbuffer.dwCursorPosition.X / 2]->zustand = !(aut.feld[sbuffer.dwCursorPosition.Y][sbuffer.dwCursorPosition.X / 2]->zustand);
			if (aut.feld[sbuffer.dwCursorPosition.Y][sbuffer.dwCursorPosition.X / 2]->zustand)std::cout << char(235) << char(235);
			else std::cout << "  ";
			break;
			case'9': iterations++; case'8':iterations++; case'7':iterations++; case'6':iterations++; case'5': iterations++; case'4':iterations++; case'3':iterations++; case'2':iterations++; case'1':iterations++;

			for(int i = 0; i < iterations; i++) {
				Sleep(200);
				aut.prepareNextStep();
				aut.executeNextStep();
			}

				break;
		default:break;
		}
	}
}

void Ablauf::regularInput()
{
	if (_kbhit() == true)
	{
		switch (_getch())
		{
		case 's':
			stop = true;
			break;
		case't':
			swapPause();
			break;
		default:
			break;
		}
	}
	Sleep(500);
	aut.prepareNextStep();
	aut.executeNextStep();
}

Ablauf::Ablauf(): aut(4,0)
{
	tryagain:
	std::string percent = "100";
	std::cout << "1.Load from file\n2.Random\n3.Custom\n";

	std::getline(std::cin, inputString);
	try {
		if (stoi(inputString) == 2)
		{
			std::cout << "Enter percentage for cell to be active:";
			std::getline(std::cin, percent);
		}
	}
	catch (...)
	{
		std::cout << "\nInvalid Input\n";
		goto tryagain;
	}

	aut = Automat(stoi(inputString), stoi(percent));
	cursor.dwSize = 100;
	cursor.bVisible = 1;
	SetConsoleCursorInfo(h, &cursor);
	swapPause();
	SetConsoleCursorPosition(h, { 0,0 });
}

void Ablauf::swapPause()
{
	SetConsoleCursorPosition(h, { aut.grX *2 + 2,0 });
		if (pause)
			std::cout<<"           ";
		else
			std::cout << "Pause";

		pause = !pause;
}

