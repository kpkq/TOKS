#pragma once

#include <string>
#include <iostream>
#include <bitset>

using namespace std;

class Package
{
public:
	static string encodeMsg(string);
	static string decodeMsg(string);
	void showPckg(string);
	string pack(string);
	string unpack(string);
	Package();

private:
	const string beginFlag = "01111110";
	const string bitStuffed = "011111110";
};

