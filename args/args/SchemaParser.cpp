#include "SchemaParser.h"
#include <fstream>
#include <regex>
#include <iostream>

bool SchemaParser::CheckFlagName(string name)
{
	//Überprüft, ob der String ein "-" gefolgt von einem Buchstaben ist
	if (regex_match(name, regex("(-)([a-z])")))
		return true;
	return false;
}
//Überprüft, ob der String aus einem der identifier b(bool),i(int),f(float),n(null/nichts) oder s(string). Bei s muss noch überprüft werden, ob danach ein Leerzeichen gefolgt von einem regulären ausdruck kommt. Überprüft nicht ob der Reguläre Ausdruck tatsächlich gültig ist.
bool SchemaParser::CheckFlagValue(string value)
{

	switch (value[0])
	{
	case 'n': nullFlags.push_back(flagVector.back()[1]);
	case 'b':	case 'i': 	case 'f':
		return true;
	case 's':
		if (regex_match(value.substr(0,2), regex("(s)(\\s)")))
			if (regex_match(value, regex("(s)(\\s)([^[:space:]])*")))
				return true;
			else
				throw logic_error(value + " does not have a valid regular Expression!");

	}
	return false;
}

void SchemaParser::ParseSchema(string filePath)
{
	ifstream schemaFile(filePath);
	char* lineContent=new char[265];
	string lineContentAsString;
	//Represents the expected type of the next Content: Bool is a Flag, true is value type  
	bool ContentType = false;


	if (!schemaFile.is_open())
		throw runtime_error("Schema file " + filePath + " not found.");

	while (schemaFile.getline(lineContent, 265)) {
		lineContentAsString.clear();
		//gcount ist die Anzahl der gelesenen Chars
		for (int i = 0; i < schemaFile.gcount(); i++)
			lineContentAsString.push_back(lineContent[i]);
		//In manchen Fällen hängt getline ein \0 an
		if (lineContentAsString.back() == '\0')
			lineContentAsString.erase((--lineContentAsString.end()));

		if (ContentType) {
			if (!CheckFlagValue(lineContentAsString))
				throw logic_error(lineContentAsString + " hat keinen gültigen Value-Type!");
			//Den nächsten Input auf einen Flag-Name ändern
			ContentType = false;
			//Hängt an den letzten String des Vektors (der zuletzt eingelesene Name) den Value an, mit einem Space Abstand.
			flagVector.back().append(" " + lineContentAsString);
		}
		else {
			if (!CheckFlagName(lineContentAsString))
				throw logic_error(lineContentAsString + " ist kein gültiger Flag-Name. Gültig ist alles der Form \"-\" und eine Folge von Buchstaben, aber mindestens einer.");
			//Den nächsten Input auf einen Flag-Value ändern
			ContentType = true;
			flagVector.push_back(lineContentAsString);
		}
	}
	if (ContentType)
		throw logic_error("Last flag has no value associated!");

	std::cout << "Schema erfolgreich eingelesen!\n"<<"Schema:\n";
	for (auto i = flagVector.begin(); i < flagVector.end(); i++)
		std::cout<< *i << std::endl;
}

bool SchemaParser::CheckIfNullFlag(char flag)
{
	auto iter = nullFlags.begin();
	while (iter != nullFlags.end()) {
		if ((*iter) == flag)
			return true;
			iter++;
	}
	return false;
}
