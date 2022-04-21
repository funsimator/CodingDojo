#include "Automat.h"
#include <conio.h>
#include <thread>
#include <iostream>
#include "Ablauf.h"

int Zelle::checked = 0;


void main()
{
	Ablauf central;
	while (!central.getStop()) {

		while (central.getPause())
		{
			central.pauseInput();
		}

		while (!central.getPause())
		{
			central.regularInput();
		}
	}
}