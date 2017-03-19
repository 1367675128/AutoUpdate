/*
 * dll_lib.c
 */
#include <windows.h>
#include <stdio.h>
#include "libalg.h"

int WINAPI DllMain (HINSTANCE hInstance, DWORD fdwReason, PVOID pvReserved)
{
    switch (fdwReason)
    {
	case DLL_PROCESS_ATTACH:
		printf("> process attach of dll\n");
        break;       
    case DLL_THREAD_ATTACH:
		printf("> thread attach of dll\n");
        break;
	case DLL_THREAD_DETACH:
		printf("> thread detach of dll\n");
		break;
    case DLL_PROCESS_DETACH:
		printf("> process detach of dll\n");
		break;
	}
	return TRUE;
}

int WINAPI GetMax(int a, int b)
{
	return a > b ? a : b;
}
