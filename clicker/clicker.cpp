#include <chrono>
#include <thread>

#include "clicker.hpp"
#include "clicks\clicks.hpp"
#include "csf.h"
#include "..\utilities\utils.hpp"
#include "..\xorstr.h"

void clicker::thread() {
    for (;; std::this_thread::sleep_for(std::chrono::milliseconds(1))) {

        for (const auto& delay : clicks::clickdata) {

            if (delay > clicker::delayfilter) {
                continue; // skips to next delay
            }

            if (!clicker::inventory) {

                const auto isCursorVisible = []() -> bool {

                    CURSORINFO mouseInfo{ sizeof(CURSORINFO) };

                    if (GetCursorInfo(&mouseInfo))
                    {
                        HCURSOR handle{ mouseInfo.hCursor };

                        if ((int(handle) > 50000) & (int(handle) < 100000))
                            return true;
                    }
                    return false;
                };
                    while (isCursorVisible()) { nt::sleep(10); }
                }

            if (clicker::rmb_lock == true && GetAsyncKeyState(VK_RBUTTON) & 0x8000) 
                continue;

                if (clicker::enable && GetAsyncKeyState(VK_LBUTTON) & 0x8000) {

                    HWND window = GetForegroundWindow();

                    if (window == FindWindowA(utils::minecraft, nullptr)) {

                        PostMessageA(window, WM_LBUTTONDOWN, MK_LBUTTON, 0);
                        nt::sleep(delay / 2 - clicker::upscale * 2);
                        PostMessageA(window, WM_LBUTTONUP, MK_LBUTTON, 0);
                        nt::sleep(delay / 2 - clicker::upscale * 2);

                        // some recorders may have saved delays differently so you may need to replace the code above with this
                        //
                        // PostMessageA(window, WM_LBUTTONDOWN, MK_LBUTTON, 0);
                        // nt::sleep(delay - upscale * 2);
                        // PostMessageA(window, WM_LBUTTONUP, MK_LBUTTON, 0);
                        // nt::sleep(delay - upscale * 2);
                    }
                }
                else { nt::sleep(10); }
        }
    }
}

void clicker::binds() {
    for (;; std::this_thread::sleep_for(std::chrono::milliseconds(1))) {

        HWND window = GetForegroundWindow();

        if (window == FindWindowA(utils::minecraft, nullptr)) {

            if (GetAsyncKeyState(clicker::bind) & 1) {

                clicker::enable = !clicker::enable;
                if (clicker::enable) {

                    SetConsoleTitleA(xorstr("clicker: enabled"));
                }
                else {

                    SetConsoleTitleA(xorstr("clicker: disabled"));
                }
            }

            while (GetAsyncKeyState(clicker::bind)) {}
        }
    }
}
