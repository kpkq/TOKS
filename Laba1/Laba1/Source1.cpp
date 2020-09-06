#include "Header.h"

SerialPort::SerialPort(string port_name, int baudrate)
{
	this->port_handle = CreateFile(
		port_name.c_str(), //наименование порта, например COM1
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, 
		NULL);

	if (this->port_handle == (HANDLE)-1) 
	{
		this->port_handle = 0;
		exit(-1);
	}

	SetupComm(this->port_handle, 1500, 1500);
	COMMTIMEOUTS CommTimeOuts;
	CommTimeOuts.ReadIntervalTimeout = 0xFFFFFFFF;
	CommTimeOuts.ReadTotalTimeoutMultiplier = 0;
	CommTimeOuts.ReadTotalTimeoutConstant = 5;
	CommTimeOuts.WriteTotalTimeoutMultiplier = 0;
	CommTimeOuts.WriteTotalTimeoutConstant = 5;
	if (!SetCommTimeouts(this->port_handle, &CommTimeOuts)) {
		this->port_handle = 0;
		exit(-1);
	}
	//настраиваем параметры работы для текущего устройства
	DCB ComDCM;
	memset(&ComDCM, 0, sizeof(ComDCM));
	ComDCM.DCBlength = sizeof(DCB);
	GetCommState(this->port_handle, &ComDCM); // текущие значения
	ComDCM.BaudRate = DWORD(baudrate); // скорость в бодах
	ComDCM.ByteSize = 8; // размер байта
	ComDCM.Parity = NOPARITY; // паритет
	ComDCM.StopBits = ONESTOPBIT; // количество стоп бит
	ComDCM.fAbortOnError = TRUE;
	ComDCM.fDtrControl = DTR_CONTROL_DISABLE; // сброс DTR бита

	// автоустановка RTS бита
	ComDCM.fRtsControl = RTS_CONTROL_TOGGLE;
	ComDCM.fBinary = TRUE; //бинарный режим всегда
	ComDCM.fParity = FALSE; //паритет
	ComDCM.fInX = ComDCM.fOutX = FALSE;
	ComDCM.XonChar = 0;
	ComDCM.XoffChar = uint8_t(0xff);
	ComDCM.fErrorChar = FALSE;
	ComDCM.fNull = FALSE;
	ComDCM.fOutxCtsFlow = FALSE;
	ComDCM.fOutxDsrFlow = FALSE;
	ComDCM.XonLim = 128;
	ComDCM.XoffLim = 128;

	//установка параметров работы для текущего устройства
	if (!SetCommState(this->port_handle, &ComDCM)) 
	{
		CloseHandle(this->port_handle);
		this->port_handle = 0;
		exit(-1);
	}
}

SerialPort::~SerialPort()
{
	if (this->port_handle != 0) 
	{
		CloseHandle(this->port_handle);
		this->port_handle = 0;
	}
}

void SerialPort::write(string msg)
{
	int i = 0;
	while (i < msg.size())
	{
		WriteFile(this->port_handle , &(msg[i++]), 1, NULL, NULL);
	}
}

string SerialPort::read()
{
	char buf = '\0';
	string msg;
	DWORD bytesReaded;
	do 
	{
		ReadFile(this->port_handle, &buf, 1, &bytesReaded, NULL);
		msg += buf;
		if (buf == '\n') break;
	} while (1);
	return msg;
}

void SerialPort::setBaudrate() 
{
	DWORD baudRate;

	cout << "Select baudrate:" << endl << "0. 110" << endl << "1. 9600" << endl << "2. 14400" << endl << "3. 19200" << endl << "4. 38400" << endl << "5. 56000" << endl << "6. 256000" << endl;
	switch (_getch()) {

	case('0'):
		system("cls");
		baudRate = CBR_110;
		break;

	case('1'):
		system("cls");
		baudRate = CBR_9600;
		break;

	case('2'):
		system("cls");
		baudRate = CBR_14400;
		break;

	case('3'):
		system("cls");
		baudRate = CBR_19200;
		break;

	case('4'):
		system("cls");
		baudRate = CBR_38400;
		break;

	case('5'):
		system("cls");
		baudRate = CBR_56000;
		break;

	case('6'):
		system("cls");
		baudRate = CBR_256000;
		break;

	default:
		system("cls");
		baudRate = CBR_19200;
		cout << "Wrong input. Default 19200 baudrate is set" << endl;
		break;

	}
	setRate(baudRate);
}


void SerialPort::setRate(DWORD baudRate) {

	//Настройка порта
	DCB ComDCM;
	memset(&ComDCM, 0, sizeof(ComDCM));
	ComDCM.DCBlength = sizeof(DCB);
	GetCommState(this->port_handle, &ComDCM);

	ComDCM.BaudRate = baudRate;

	//Установка новых параметров
	if (!SetCommState(this->port_handle, &ComDCM))
	{
		CloseHandle(this->port_handle);
		cout << "Failed to set DCB!" << endl;
		exit(0);
	}
}