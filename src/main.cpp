#include "game.h"
#include <TlHelp32.h>
#include <fstream>
#include <string>
#include <iostream>
#include <ctime>
#include <wtypes.h>
#include "macroConfig.h"
#include "fsfml.h"



int main() {
    try {
        HWND hwnd = GetConsoleWindow();
        ShowWindow(hwnd, SW_SHOW);
        macroConfig mc;
        game gm;
        sysCommands sys;
        gm.sys.bringWindowToFront(hwnd);
        SetFocus(hwnd);
        gm.startMacro();
        gm.macroLoop();
        return 0;
    }
    catch (EndMacroException e) {
        std::cout << "End of Macro" << std::endl;
    }
    return 0;

}