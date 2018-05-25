#include <iostream>
#include <Windows.h>
#include <string>
#include <intrin.h>
#include <conio.h>
using namespace std;

#define title "Хохлов Е.С. КИз-16"
int temp = 500;


HDC hDC;
HWND hWnd;
HANDLE Handle;

void GetHwnd(){ hWnd = GetConsoleWindow(); }
void GetHdc(){ hDC = GetDC(hWnd); }
void GetHandle() { Handle = GetStdHandle(STD_OUTPUT_HANDLE); }


void CALLBACK Print(HWND hwnd, UINT uMsg, UINT timerId, DWORD dwTime)
{
	cout << "A" << endl;
}

void SetPosition(int x, int y)
{
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
	int x = 21;
	int y = 6;
	bool down = false;
	bool right = false;
	bool up = false;
	unsigned count = 0;
	

	SetInterval();

	SetTimer(NULL, 0, temp, (TIMERPROC)&Print);
	SetConsoleTextAttribute(Handle, FOREGROUND_GREEN );
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

		count++; 
	}

	string name = GetCpuVendorString();
	cout << endl << endl << endl << endl << endl << endl;
	cout << "Название процессора:" << endl;
	cout << name << endl;
	_getch();
	return 0;
}




