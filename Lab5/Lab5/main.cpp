#include "Header.h"
#include "Package.h"
#include "Station.h"

void threadFun(Station* st) {
	srand(time(NULL));
	st->routine();
}

int main(int argc, char* argv[]) {
	srand(time(NULL));
	Station first(0);
	Station second(1);
	Station third(2);
	first.setMaxDest(2);
	second.setMaxDest(2);
	third.setMaxDest(2);
	first.setNext(&second);
	second.setNext(&third);
	third.setNext(&first);
	thread a(threadFun, &first);
	thread b(threadFun, &second);
	thread c(threadFun, &third);

	first.receivePackage(Package());

	_getch();

	first.deactivate();
	second.deactivate();
	third.deactivate();

	a.join();
	b.join();
	c.join();
	return 0;
}