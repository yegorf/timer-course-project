#pragma comment (lib, "Winmm.lib")
#include <iostream>
#include <Windows.h>
#include <string>
#include <intrin.h>
#include <conio.h>
#include <fstream>
#include <time.h>
using namespace std;
#define title "Хохлов Е.С. КИз-16"

clock_t start, endd;
int temp = 500;

HDC hDC;
HWND hWnd;
HANDLE Handle;

void GetHwnd(){ hWnd = GetConsoleWindow(); }
void GetHdc(){ hDC = GetDC(hWnd); }
void GetHandle() { Handle = GetStdHandle(STD_OUTPUT_HANDLE); }

void SetPosition(int x, int y)
{
	endd = start;
	start = clock();
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(Handle, coord);
}
struct cpuid_regs
{
	DWORD   Eax;
	DWORD   Ebx;
	DWORD   Ecx;
	DWORD   Edx;
};

string SplitIntoChars(DWORD Value)
{
	string Str;
	char const * pCursor = (char const *)&Value;
	for (int i = 0; i < sizeof(Value); ++i) {
		Str += pCursor[i];
	}
	return Str;
}

string GetCpuVendorSubstring(DWORD Eax)
{
	cpuid_regs Regs;
	__cpuid((int *)&Regs, Eax);
	string Str;
	Str += SplitIntoChars(Regs.Eax);
	Str += SplitIntoChars(Regs.Ebx);
	Str += SplitIntoChars(Regs.Ecx);
	Str += SplitIntoChars(Regs.Edx);
	return Str;
}

string GetCpuVendorString()
{
	string VendorString;
	cpuid_regs Regs;
	__cpuid((int *)&Regs, 0x80000000);
	if (Regs.Eax >= 0x80000004)
	{
		VendorString =
			GetCpuVendorSubstring(0x80000002) +
			GetCpuVendorSubstring(0x80000003) +
			GetCpuVendorSubstring(0x80000004)
			;
	}
	return VendorString;
}
void ProcessorName()
{
	string name = GetCpuVendorString();
	cout << endl << endl << endl << endl << endl << endl;
	cout << "Название процессора:" << endl;
	cout << name << endl;
}

void CALLBACK Print(HWND hwnd, UINT uMsg, UINT timerId, DWORD dwTime)
{
	cout << "A";
}

int col = 0;
int x = 21;
int y = 6;

void CALLBACK PrintMultimedia(UINT uTimerID, UINT uMsg,
	DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2)
{

		SetPosition(x, y);
		cout << "A";
		if (col < 3 || col > 6)
		{
			y += 1;
		}
		if (col >= 3 && col < 6)
		{
			x += 2;
		}
		if (col == 6)
		{
			y -= 1;
			x += 2;
		}
		
		if (col == 11)
		{
			timeKillEvent(uTimerID);
			ProcessorName();
		}
		col++;
}



void SetInterval()
{
	cout << "Выберите интервал таймера" << endl;
	cout << "1)165" << endl;
	cout << "2)500" << endl;
	cout << "3)1065" << endl;
	char c = _getch();

	switch (c)
	{
	case '1':
		temp = 165;
		break;
	case '2':
		temp = 500;
		break;
	case '3':
		temp = 1065;
		break;
	}
	system("cls");
}



void WriteFile(int col, double *mas)
{
	ofstream f;
	string name;
	if (temp == 165) { name = "Info165.txt"; }
	if (temp == 500) { name = "Info500.txt"; }
	if (temp == 1065) { name = "Info1065.txt"; }
	f.open(name);

	for (int i = 1; i < col; i++)
	{
		f << i << ") " << mas[i] << endl;
	}

	f.close();

}


UINT uTimerID;
//void Start()
//{
//	uTimerID = timeSetEvent(temp, temp, PrintMultimedia, 0, TIME_PERIODIC);
//	timeKillEvent(uTimerID);
//}

//void Kill()
//{
//	if(col==11)
//	
//}


int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	setlocale(LC_ALL, "Russian");
	SetConsoleTitle(title);
	GetHwnd();
	GetHdc();
	GetHandle();
	MoveWindow(hWnd, 300, 300, 400, 400, TRUE);

	MSG msg;
	char c;
	unsigned count = 0;
	double *real = new double[11];
	SetConsoleTextAttribute(Handle, FOREGROUND_GREEN );


	cout << "Выберете тип таймера" << endl;
	cout << "1)Таймер пользователя" << endl;
	cout << "2)Мультимедийный таймер" << endl;
	c = _getch();
	system("cls");

	SetInterval();

	if (c == '1')
	{
		SetTimer(NULL, 0, temp, (TIMERPROC)&Print);
		while (GetMessage(&msg, NULL, 0, 0))
		{

			SetPosition(x, y);
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (count < 3 || count > 6)
			{
				y += 1;
			}
			if (count >= 3 && count < 6)
			{
				x += 2;
			}
			if (count == 6)
			{
				y -= 1;
				x += 2;
			}
			if (count == 11)
				break;

			real[count] = (double)(start - endd);
			count++;
		}	
	ProcessorName();
	WriteFile(count, real);
	}

	else
	{
		uTimerID = timeSetEvent(temp, temp, PrintMultimedia, 0, TIME_PERIODIC);
	}

	system("pause");
	return 0;
}




