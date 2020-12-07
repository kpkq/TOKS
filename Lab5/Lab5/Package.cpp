#include "Package.h"

Package::Package() {

	this->control = 1;
}

Package::Package(byte destination, byte source, string data) {

	this->destination = destination;
	this->source = source;
	this->data = data;
}

ostream& operator<< (ostream& out, const Package& package) {

	out << std::endl << " Control: " << (int)package.control << std::endl << " Source: " << (int)package.source 
		<< " Destination: " << (int)package.destination << std::endl << " Message: " << package.data << " Status: " << (int)package.status << std::endl;
	return out;
}

byte Package::getControl() {
	return this->control;
}

void Package::setControl(byte byte) {
	this->control = byte;
}

byte Package::getDestination() {
	return this->destination;
}

void Package::setDestination(byte byte) {
	this->destination = byte;
}

byte Package::getSource() {
	return this->source;
}

void Package::setSource(byte byte) {
	this->source = byte;
}

string Package::getData() {
	return this->data;
}

void Package::setData(string data) {
	this->data = data;
}

byte Package::getStatus() {
	return this->status;
}

void Package::setStatus(byte byte) {
	this->status = byte;
}

byte Package::getMonitor() {
	return this->monitor;
}

void Package::setMonitor(byte byte) {
	this->monitor = byte;
}
