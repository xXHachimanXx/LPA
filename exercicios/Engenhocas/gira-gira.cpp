#include <windows.h>
#include <iostream>
#include <wingdi.h>

#define DM_DISPLAYORIENTATION			0x00000080
#define DMDO_180				0x00000002

using namespace std;

int main() {
    DEVMODE mode;
    //first get setting for "current" screen
    EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, & mode);

    if (mode.dmFields | DM_DISPLAYORIENTATION) {
        mode.dmDisplayOrientation = DMDO_180;
        LONG r;
        r = ChangeDisplaySettings( & mode, 0);
        std::cout << "result: " << r;
    }
}