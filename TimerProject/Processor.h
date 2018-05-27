#pragma once
#include <iostream>
#include <Windows.h>
#include <string>
#include <intrin.h>
#include <conio.h>
#include <fstream>
#include <time.h>

using namespace std;

class Processor
{
private:

struct cpuid_regs
{
	DWORD   Eax;
	DWORD   Ebx;
	DWORD   Ecx;
	DWORD   Edx;
};

public:

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

};



