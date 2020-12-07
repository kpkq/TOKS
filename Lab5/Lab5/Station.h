#pragma once
#include "Header.h"
#include "Package.h"

class Station{
private:
	byte id;
	byte maxDest;
	Station* nextStation;
	Package package;
	byte flag;
	byte active = 1;

public:
	Station(byte);

	void setMaxDest(byte);
	void setNext(Station*);
	byte generateDestination();
	string generateData();
	void sendPackage();
	void receivePackage(Package);
	void routine();
	void deactivate();
};

