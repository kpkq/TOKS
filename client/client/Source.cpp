#include "..\..\Laba1\Laba1\Header.h"

int main()
{
	SerialPort port = SerialPort("COM3", 19200);

	port.setBaudrate();
	char tmp = '\0';
	while (1)
	{
		cout << "1. Write\n2. Read\n3. Set baudrate" << endl;
		if (tmp == '4')
			break;
		char tmp = _getch();
		system("cls");
		if (tmp == '1')
		{
			string tmp;
			getline(cin, tmp);
			tmp += '\n';
			port.write(tmp.c_str());
		}
		if (tmp == '2')
			cout << port.read();
		if (tmp == '3')
			port.setBaudrate();
	}
	system("pause");
}
