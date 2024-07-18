#include <stdio.h>
#include <windows.h>
#include "./lib/op2p.h"

int main(int argc, char *argv[])
{
	// 检查是否提供了命令行参数
	if (argc < 1)
	{
		printf("Usage: %s <config>\n", argv[0]);
		return 1;
	}

	// Load the DLL : HANDLE 代表句柄
	HMODULE hLib = LoadLibrary("./lib/op2p.dll");
	if (hLib == NULL)
	{
		printf("Failed to load the DLL\n");
		return 1;
	}

	// Define the function pointer type
	typedef int (*CNewClientFunc)(char *);

	// Get the function address
	CNewClientFunc CNewClient = (CNewClientFunc)GetProcAddress(hLib, "CNewClient");
	if (CNewClient == NULL)
	{
		printf("Failed to get the function address\n");
		FreeLibrary(hLib);
		return 1;
	}

	// Call the function with the command line argument
	int res = CNewClient(argv[1]);
	printf("CNewClient Result: %d\n", res);


	typedef int (*CStartFunc)(int);
	CStartFunc CStart = (CStartFunc)GetProcAddress(hLib, "CStart");
	int sd = CStart(res);
	printf("CStart Result: %d\n", sd);


	Sleep(100000000);
	// Free the DLL
	FreeLibrary(hLib);

	return 0;
}