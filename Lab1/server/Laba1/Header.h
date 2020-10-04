#pragma once
#include<Windows.h>
#include<iostream>
#include<conio.h>
#include<string>
#include"Package.h"
using namespace std;

class SerialPort
{
public:
	SerialPort(string, int);
	~SerialPort();
	void write(string);
	string read();
	void setBaudrate();
private:
	void setRate(DWORD);
	HANDLE port_handle;
};
