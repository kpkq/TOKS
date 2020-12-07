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
			while (chanel != ' ');	// �������� ������������ ������
			chanel = msg;	// �������� �����
			Sleep(COLLISION_WINDOW);	// ��������� ���� ��������
			if (chanel == msg)	// �������� ��������
			{
				chanel = ' ';	// ������� �����
				break;	// �����
			}
			chanel = (char)JAM_SYMBOL;	// �������� Jam �������
			attempts++;
			if (attempts == 10) // ����� ��� ���������� ����� �������
			{
				cout << "ERROR" << endl;
				return;
			}
			Sleep((rand() % ((int)pow(2, attempts) - 1)) * 25);    // ��������� ��������
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