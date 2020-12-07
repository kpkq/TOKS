#include "Station.h"

Station::Station(byte id) {
	srand(time(NULL));
	this->id = id;
}

void Station::setMaxDest(byte max) {
	this->maxDest = max + 1;
}

void Station::setNext(Station* next) {
	this->nextStation = next;
}

byte Station::generateDestination() {
	byte tmp = byte(rand() % maxDest);
	return tmp == id ? (id+1)%maxDest : tmp;
}

string Station::generateData() 
{
	string msg;
	for (int i = 0; i < 8; i++)
	{
		msg.push_back('a' + (rand() % 26));
	}
	return msg.c_str();
}

void Station::sendPackage() {
	cout << "Station " << (int)this->id << " sent " << package << endl;
	nextStation->receivePackage(package);
}

void Station::receivePackage(Package package) {
	this->package = package;
	Sleep(200);
	cout << "Station " << (int)this->id << " received " << package << endl;
	flag = 1;
}

void Station::routine() 
{
	while (active) 
	{	
		if(flag) 
		{
			if (package.getControl() == 1) 
			{

				if (rand() % 2) { sendPackage(); flag = 0; continue; }
				cout << "Station " << (int)this->id <<  " sending message" << endl;
				package = Package(generateDestination(), id, generateData());
				sendPackage();
				flag = 0;
				while (!flag);
				if (package.getSource() == id) 
				{
					if (package.getStatus() == 1) 
					{
						cout << "_____________________________________________________" << endl;
						cout << "Station " << (int)this->id << " successfull delivery" << endl;
						cout << "_____________________________________________________" << endl;
						flag = 0;
						package = Package();
						sendPackage();
						continue;
					}
				}
				package = Package();
				sendPackage();
			}
			else {

				if (package.getDestination() == id)
				{
					cout << "_____________________________________________________" << endl;
					cout << "Station " << (int)this->id << " received message: " << package.getData() << endl;
					cout << "_____________________________________________________" << endl;
					package.setStatus(1);
					cout << "Station " << (int)this->id << " sending response" << endl;
				}
				else cout << "skip message" << endl;
				
				sendPackage();
			}
			flag = 0;
		}
		Sleep(2000);
	}
}


void Station::deactivate() {

	this->active = 0;
}

