#include <iostream>
#include <Windows.h>
using namespace std;

#define title "Хохлов Е.С. КИз-16"
#define temp 1000


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
	system("color F0");

	MSG msg;
	int x = 21;
	int y = 6;
	bool down = false;
	bool right = false;
	bool up = false;
	unsigned count = 0;
	
	SetTimer(NULL, 0, temp, (TIMERPROC)&Print);
	SetConsoleTextAttribute(Handle, FOREGROUND_GREEN 
		| BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
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

	cout <<endl<< "Ты вышел из таймера" << endl;
	system("pause");
	return 0;
}


