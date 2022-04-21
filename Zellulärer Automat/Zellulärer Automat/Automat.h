#pragma once
#include "Zelle.h"
#include <Windows.h>
#include <string>
#include <fstream>
class Automat
{
public:
	//Größe des Feldes
	static const int grX = 30;
	static const int grY = 27;
	//Used while loading from a file
	std::string inputString;
	/// <summary>
	/// 
	/// </summary>
	/// <param name="mode:"> 1 = Open File, 2 = Zufällig, 3 = Edit Mode</param>
	/// <param name="prob:"> Percentage with which each cells spawns alive, if mode is 2</param>
	Automat(int mode, int prob = 10);

	Zelle* feld[grY][grX];

	//Merkt den nächsten Zustands 
	void prepareNextStep();

	//Überträgt die vorgemerkten Änderungen auf den Automaten
	void executeNextStep();

	/// <summary>
	/// 
	/// </summary>
	/// <param name="pos"></param>
	/// <returns>Anzahl der "lebenden" Nachbarn. </returns>
	int getNeighbors(COORD pos);

	//Saves the current state into <filename>
	void saveLayout(std::string filename);

	//Loads a state out of <filename>
	bool loadLayout(std::string filename);

	//Draws all cells at once
	void drawEverything();

	//Sets all cells and their next status to 0
	void ResetField();


};

