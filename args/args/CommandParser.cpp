#include "CommandParser.h"
#include <stdexcept>
#include <iostream>
#include <regex>
//Überprüft, ob das Flag in dem gegebenen Vector vorkommt. Returnt den end() iterator falls nicht.
auto CommandParser::CheckFlagName(const vector<string>& vec,string flag)
{
	auto iter = vec.begin();
	while (iter != vec.end()) {
		if ((*iter).substr(0,2).compare(flag.substr(0,2)) == 0)
			break;
		iter++;
	}
	return iter;
}
//Überprüft ob nach dem Flag-Name ein Leerzeichen und der korrekte Buchstabe entsprechend dem Schema steht.
bool CommandParser::CheckFlagValueType(string entry, string& value)
{
	if (value.length() < 3)
		value.push_back(' ');
	//Kein Value angegeben, Default wert wird angehangen 
	if (value.length() < 4) {
		switch (entry[3]) {
		case 'B':case 'b': value.append("false"); break;
		case'I':case 'i': value.push_back('0'); break;
		case'F':case 'f': value.append("0.0"); break;
		case'N':case 'n': value.push_back('1'); break;
		case'S':case 's': value.append("NULL"); break;
		}
	}
	//Überprüfung ob der Value zu dem Flag-Type passt
	else {
		switch (entry[3]) {
		case 'B':case 'b': CheckForBool(value); break;
		case'I':case 'i': CheckForInt(value); break;
		case'F':case 'f': CheckForFloat(value); break;
		case'N':case 'n':	throw logic_error(value + " erwartet keine Wert!");
		case'S':case 's': CheckForString(entry,value); break;
	}
}
}
//Überprüft ob der Flag-Value Teil ein boolean ist.
bool CommandParser::CheckForBool(string flag)
{
	if (flag[3] == '0')
		return  false;
	else if (flag[3] == '1')
		return true;

	flag.erase(0, 3);

	if (regex_match(flag, regex("([tT])([rR])([uU])([eE])(\\s)?")))
		return true;
	else if (regex_match(flag, regex("([fF])([aA])([lL])([sS])([eE])(\\s)?")))
		return false;

	throw logic_error(flag + " ist nicht der passende Type für das Flag: Es wurde ein Boolean erwartet.");
}

int CommandParser::CheckForInt(string flag)
{
	flag.erase(0, 3);
	if (!regex_match(flag, regex("([0-9])+(\\s)?")))
		throw logic_error(flag + " ist kein Integer-Wert!");
	return stoi(flag);
}

float CommandParser::CheckForFloat(string flag)
{
	flag.erase(0, 3);
	if (!regex_match(flag, regex("(-)?([0-9])+((.)([0-9])+)?(\\s)?")))
		throw logic_error(flag + " ist kein Integer-Wert!");
	return stof(flag);
}


string CommandParser::CheckForString(string reg,string flag)
{
	if(!regex_match(flag.substr(3),regex(reg.substr(5))))
		throw logic_error(flag.substr(0,2) + " hat nicht das richtige Format! Es wurde Input der Form: "+ reg.substr(5) + " erwartet.");
	return flag.substr(3);
}


void CommandParser::ParseCommand(string flags)
{
	if (schemaParser.HasSchema()) {
		//Iterator über dem String mit den Flags
		auto iter = flags.begin();
		//Enthält den aktuelle zu prüfenden flag
		string flag;
		//Der Eintrag des aktuell ausgewählten Flags im Schema
		auto flagEntry= schemaParser.GetFlagVectorCopy().end();

		while (iter != flags.end())
		{
			flag.push_back(*iter);
			iter++;
			//Überprüft ob zwei Spaces eingelesen wurden. (Der erste steht zwischen Flag-Name und Flag-Value, der zweite markiert den Abstand zum nächsten Flag) oder das Ende des Commandos erreicht wurde.
			if (iter == flags.end()||(flag.length() > 1 && (*(iter))=='-'))
			{
				flagEntry = CheckFlagName(schemaParser.GetFlagVectorCopy(),flag);
				if (flagEntry == schemaParser.GetFlagVectorCopy().end())
					throw logic_error("Flag " + flag + " wurde im Schema nicht gefunden!");
				CheckFlagValueType(*flagEntry, flag);
				FlagVector.push_back(flag);
				flag.erase();
			}
		}
			std::cout << "Alle Flags Korrekt!";
	}
	else
		throw logic_error("Keine Schema geladen!");
}


template<>
int CommandParser::GetFlag(string flag)
{
	auto flagEntry = CheckFlagName(FlagVector,flag);
	if (flagEntry == FlagVector.end())
		throw runtime_error("Flag" + flag+  " wurde nicht gesetzt!");
	return CheckForInt(*flagEntry);
}
template<>
float CommandParser::GetFlag(string flag)
{
	auto flagEntry = CheckFlagName(FlagVector, flag);
	if (flagEntry == FlagVector.end())
		throw runtime_error("Flag" + flag + " wurde nicht gesetzt!");
	return CheckForFloat(*flagEntry);
}
template<>
bool CommandParser::GetFlag(string flag)
{
	auto flagEntry = CheckFlagName(FlagVector, flag);
	if (flagEntry == FlagVector.end())
		throw runtime_error("Flag" + flag + " wurde nicht gesetzt!");
	return CheckForBool(*flagEntry);
}
template<>
string CommandParser::GetFlag(string flag)
{
	auto flagEntry = CheckFlagName(FlagVector, flag);
	auto schemaEntry = CheckFlagName(schemaParser.GetFlagVectorCopy(),flag);
	if (flagEntry == FlagVector.end())
		throw runtime_error("Flag" + flag + " wurde nicht gesetzt!");
	return CheckForString(*schemaEntry, *flagEntry);
}