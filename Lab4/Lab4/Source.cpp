#include <Windows.h>
#include <iostream>
#include <string>
#include <thread>
#define COLLISION_WINDOW 350
#define JAM_SYMBOL '-'

using namespace std;

char chanel = ' ';

void transmitter(string data) {

	int attempts;
	int k;

	for(auto msg: data) {

		attempts = 0;

		while (1) {
			while (chanel != ' ');	// ожидание освобождения канала
			chanel = msg;	// передача кадра
			Sleep(COLLISION_WINDOW);	// выжидание окна коллизии
			if (chanel == msg)	// проверка коллизии
			{
				chanel = ' ';	// очищаем канал
				break;	// выход
			}
			chanel = (char)JAM_SYMBOL;	// отправка Jam сигнала
			attempts++;
			if (attempts == 10) // выход при превышении числа попыток
			{
				cout << "ERROR" << endl;
				return;
			}
			Sleep((rand() % ((int)pow(2, attempts) - 1)) * 25);    // случайная задержка
		}
	}

	chanel = ' ';
}

int main(int argc, char* argv[]) {
	thread transmitter1(transmitter, "1234567890~");
	thread transmitter2(transmitter, "!@#$%^&*()~");
	thread transmitter3(transmitter, "qwertyuiop~");
	while (1) {

		Sleep(100);
		cout << chanel;
		if (chanel == (char)JAM_SYMBOL)
		{
			chanel = ' ';
			continue;
		}

	}

	transmitter1.join();
	transmitter2.join();
	transmitter3.join();
	return 0;
}