#include "Header.h"

int main()
{
	SerialPort port = SerialPort("COM2", 19200);
	/*
	STARTUPINFO si;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	PROCESS_INFORMATION procInfo;
	ZeroMemory(&procInfo, sizeof(PROCESS_INFORMATION));
	if (!CreateProcess(NULL, (char*)"D:\\5 sem\\TOKS\\Lab1\\client\\Debug\\client.exe", NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &procInfo))
	{
		cout << "CreateProcess failed " << GetLastError() << endl; ;
		return 0;
	}
	*/
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