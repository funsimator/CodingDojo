#pragma once
#include <string>
#include <vector>
using namespace std;

class SchemaParser
{
private:
	bool CheckFlagName(string name);
	bool CheckFlagValue(string name);
	vector<string> flagVector;
	vector<char> nullFlags;

public:
	void ParseSchema(string filePath);
	 const vector<string>& GetFlagVectorCopy() {
		return flagVector;
	}
	bool HasSchema() { return !flagVector.empty(); }
	bool CheckIfNullFlag(char flag);
};

