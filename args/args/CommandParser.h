#pragma once
#include "SchemaParser.h"
class CommandParser
{
private:
	vector<string>FlagVector;
	auto CheckFlagName(const vector<string>&vec,string flag);
	bool CheckFlagValueType(string entry,string& value);
	bool CheckForBool(string flag);
	int CheckForInt(string flag);
	float CheckForFloat(string flag);
	string CheckForString(string reg,string flag);

public:
	SchemaParser schemaParser = SchemaParser();
	void ParseCommand(string flags);
	template<class Type>
	Type GetFlag(string flag);
};

