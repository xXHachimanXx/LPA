#include <windows.h>
#include <iostream>
#include <wingdi.h>

// #define DM_DISPLAYORIENTATION			0x00000080
// #define DMDO_180				0x00000002
#define DMDO_DEFAULT    0
#define DMDO_90         1
#define DMDO_180        2
#define DMDO_270        3

using namespace std;

int main() 
{
    DEVMODE mode;

    //first get setting for "current" screen
    EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, & mode);

    if (mode.dmFields | DMDO_DEFAULT) 
    {
        mode.dmDisplayOrientation = DMDO_DEFAULT;
        LONG r;
        r = ChangeDisplaySettings( & mode, 1 );
        cout << "result: " << r;
    }
}