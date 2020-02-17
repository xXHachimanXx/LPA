#include <windows.h>
#include <iostream>

using namespace std;

typedef MCIERROR WINAPI (*CDROM)(const char *, char *, unsigned, HWND);

CDROM pCD;

void AbrirCD()
{
    pCD("Set CDAudio Door Open", NULL, 0, NULL);
}

void FecharCD()
{
    pCD("Set CDAudio Door Closed", NULL, 0, NULL);
}


int main()
{
    HINSTANCE dll = LoadLibrary("winmm.dll");

    if (!dll)

        return 1;

    pCD = (CDROM)GetProcAddress(dll, "mciSendStringA");

    if (!pCD)

        return 1;

    cout << "ABRA-TE SEZAMOOOOOOO";
    AbrirCD();
    exit(0);

    return 0;
}