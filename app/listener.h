#pragma once
#include <windows.h>

void set_enabled_ref(bool* ref);
void start_listener();
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);