#pragma once
#include "Header.h"

class Package {
private:

	byte control = 0;
	byte destination = 0;
	byte source = 0;
	string data;
	byte status = 0;
	byte monitor = 0; 

public:
	Package();
	Package(byte, byte, string);

	friend ostream& operator<< (ostream& out, const Package& package);

	byte getControl();
	void setControl(byte);
	byte getDestination();
	void setDestination(byte);
	byte getSource();
	void setSource(byte);
	string getData();
	void setData(string);
	byte getStatus();
	void setStatus(byte);
	byte getMonitor();
	void setMonitor(byte);
};


