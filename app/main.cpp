#include <windows.h>
#include <iostream>

#include "listener.h"

bool enabled = false;

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::cout << "Deromanize started\n";

    set_enabled_ref(&enabled);
    start_listener();

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}