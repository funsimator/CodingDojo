#include "SchemaParser.h"
#include "CommandParser.h"
#include <iostream>

void main() try
{
	CommandParser cmd;
	cmd.schemaParser.ParseSchema("Schema.txt");
	cmd.ParseCommand("-t -e 123 -r 13.45 -a -z d");
	std::cout << std::endl << "-t: " << cmd.GetFlag<bool>("-t");
	std::cout << std::endl << "-e: " << cmd.GetFlag<int>("-e");
	std::cout << std::endl << "-r: " << cmd.GetFlag<float>("-r");
	std::cout << std::endl << "-a: " << cmd.GetFlag<bool>("-a");
	std::cout << std::endl << "-z: " << cmd.GetFlag<string>("-z");
}
catch(std::exception ex)
{
	std::cout << ex.what();
}