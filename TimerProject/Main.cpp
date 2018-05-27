#pragma comment (lib, "Winmm.lib")
#include <iostream>
#include <Windows.h>
#include <string>
#include <intrin.h>
#include <conio.h>
#include <fstream>
#include <time.h>
#include "Processor.h"
using namespace std;
#define title "Хохлов Е.С. КИз-16"

enum TimerType { user, multimedia }type;

clock_t start, endd;
int temp = 500;
double real[11];
char c;
int col = 0;
int x = 21;
int y = 6;

HDC hDC;
HWND hWnd;
HANDLE Handle;
Processor CP;
UINT uTimerID;

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

void CALLBACK Print(HWND hwnd, UINT uMsg, UINT timerId, DWORD dwTime)
{
	cout << "A";
}

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
			CP.ProcessorName();
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

	if (type == user)
	{
		if (temp == 165) { name = "Results/User165.txt"; }
		if (temp == 500) { name = "Results/User500.txt"; }
		if (temp == 1065) { name = "Results/User1065.txt"; }
	}
	else
	{
		if (temp == 165) { name = "Results/Media165.txt"; }
		if (temp == 500) { name = "Results/Media500.txt"; }
		if (temp == 1065) { name = "Results/Media1065.txt"; }
	}

	f.open(name);

	for (int i = 1; i < col; i++)
	{
		f << i << ") " << mas[i] << endl;
	}

	f.close();

}

void RunUserTimer()
{
	MSG msg;
	unsigned count = 0;

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
	CP.ProcessorName();
	WriteFile(count, real);
}

void SetTimerType()
{
	cout << "Выберете тип таймера" << endl;
	cout << "1)Таймер пользователя" << endl;
	cout << "2)Мультимедийный таймер" << endl;
	c = _getch();
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
	SetConsoleTextAttribute(Handle, FOREGROUND_GREEN );
	SetTimerType();
	SetInterval();

	if (c == '1')
	{
		type = user;
		RunUserTimer();
	}
	else
	{
		type = multimedia;
		uTimerID = timeSetEvent(temp, temp, PrintMultimedia, 0, TIME_PERIODIC);
	}

	system("pause");
	return 0;
}




