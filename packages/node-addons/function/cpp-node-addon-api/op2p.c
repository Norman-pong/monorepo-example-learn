// #include <stdio.h>
// #include "op2p.h"

// int main() {
//     int res = CNewClient("conf");
//     printf("res: %d\n", res);
//     return 0;
// }
#include <stdio.h>
#include <windows.h>
#include "op2p.h"

int main() {
    // Load the DLL : HANDLE 代表句柄
    HMODULE hLib = LoadLibrary("./lib/libop2p.dll");
    if (hLib == NULL) {
        printf("Failed to load the DLL\n");
        return 1;
    }

    // Define the function pointer type
    typedef int (*CNewClientFunc)(char*);

    // Get the function address
    CNewClientFunc CNewClient = (CNewClientFunc)GetProcAddress(hLib, "CNewClient");
    if (CNewClient == NULL) {
        printf("Failed to get the function address\n");
        FreeLibrary(hLib);
        return 1;
    }

    // Call the function
    int res = CNewClient("ss");
    printf("res: %d\n", res);

    // Free the DLL
    FreeLibrary(hLib);

    return 0;
}