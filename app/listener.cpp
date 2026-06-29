#include <windows.h>
#include <string>
#include <iostream>
#include <cctype>

#include "listener.h"
#include "transliterator.h"

static std::string buffer = "";
static bool* enabled_ref = nullptr;
static HHOOK hook;
static bool injecting = false;

// ---------------- ENABLE
void set_enabled_ref(bool* ref) {
    enabled_ref = ref;
}

// ---------------- SENDS UNICODE TEXT
void type_text(const std::wstring& text) {
    injecting = true;

    for (wchar_t c : text) {

        INPUT input = {0};
        input.type = INPUT_KEYBOARD;
        input.ki.wScan = c;
        input.ki.dwFlags = KEYEVENTF_UNICODE;

        SendInput(1, &input, sizeof(INPUT));

        input.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &input, sizeof(INPUT));
    }

    injecting = false;
}

// ---------------- DELETES WORD
void delete_word(int len) {
    for (int i = 0; i < len; i++) {

        INPUT input = {0};
        input.type = INPUT_KEYBOARD;
        input.ki.wVk = VK_BACK;

        SendInput(1, &input, sizeof(INPUT));

        input.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &input, sizeof(INPUT));
    }
}

// ---------------- PROCESSES WORD
void process_word() {
    if (buffer.empty()) return;

    Transliterator t;
    std::wstring result = t.transliterate(buffer);

    std::cout << "-> " << buffer << " => ";
    std::wcout << result << std::endl;

    delete_word((int)buffer.size());
    type_text(result);

    buffer.clear();
}

// ---------------- HOOK
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {

    if (injecting)
        return CallNextHookEx(hook, nCode, wParam, lParam);

    if (nCode == HC_ACTION && wParam == WM_KEYDOWN) {

        KBDLLHOOKSTRUCT* kbd = (KBDLLHOOKSTRUCT*)lParam;
        DWORD vk = kbd->vkCode;

        // F8 toggle
        if (vk == VK_F8) {
            if (enabled_ref) {
                *enabled_ref = !(*enabled_ref);
                std::cout << "Enabled = " << *enabled_ref << std::endl;
            }
            return CallNextHookEx(hook, nCode, wParam, lParam);
        }

        if (!enabled_ref || !(*enabled_ref)) {
            return CallNextHookEx(hook, nCode, wParam, lParam);
        }

        // BACKSPACE
        if (vk == VK_BACK) {
            if (!buffer.empty())
                buffer.pop_back();

            return CallNextHookEx(hook, nCode, wParam, lParam);
        }

        // END WORD
        if (vk == VK_SPACE || vk == VK_RETURN) {
            process_word();
            return CallNextHookEx(hook, nCode, wParam, lParam);
        }

        // SIMPLE INPUT
        if (vk >= 'A' && vk <= 'Z') {
            buffer += (char)tolower(vk);
        }
    }

    return CallNextHookEx(hook, nCode, wParam, lParam);
}

// ---------------- START
void start_listener() {
    hook = SetWindowsHookEx(
        WH_KEYBOARD_LL,
        KeyboardProc,
        NULL,
        0
    );

    if (!hook) {
        std::cout << "Hook failed\n";
        return;
    }

    std::cout << "Deromanize IME running\n";
}