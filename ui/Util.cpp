#include "Util.h"

#ifdef _WIN32
#include <windows.h>
#endif

void Util::SetDPIAware()
{
#ifdef _WIN32
    HINSTANCE lib = LoadLibrary("user32.dll");
    void (*SetProcessDPIAware)() = (void (*)())GetProcAddress(lib, "SetProcessDPIAware");
    SetProcessDPIAware();
#endif

}
