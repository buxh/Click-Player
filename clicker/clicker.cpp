#include <chrono>
#include <thread>

#include "clicker.hpp"
#include "clicks\clicks.hpp"
#include "csf.h"
#include "..\xorstr.h"

void clicker::thread() {
    for (;; std::this_thread::sleep_for(std::chrono::milliseconds(1))) {

        for (const auto& delay : clicks::clickdata) {

            if (clicker::inventory == false) {
                    auto isCursorVisible { [&]() {
                            CURSORINFO mouseInfo { sizeof(CURSORINFO) };

                            if (GetCursorInfo(&mouseInfo)) { HCURSOR handle { mouseInfo.hCursor };

                            if ((int(handle) > 50000) & (int(handle) < 100000))
                                return true;
                            else
                                return false; }
                        }
                    };

                    while (isCursorVisible()) { nt::sleep(10); }
                }

                if (clicker::enable && GetAsyncKeyState(VK_LBUTTON) & 0x8000) {

                    HWND window = GetForegroundWindow();

                    if (window == FindWindowA(xorstr("LWJGL"), nullptr)) {

                        PostMessageA(window, WM_LBUTTONDOWN, MK_LBUTTON, 0);
                        nt::sleep(delay - upscale);
                        PostMessageA(window, WM_LBUTTONUP, MK_LBUTTON, 0);
                        nt::sleep(delay - upscale);

                        // some recordings may have saved delays differently so you may need to replace the code above with this
                        //
                        // PostMessageA(window, WM_LBUTTONDOWN, MK_LBUTTON, 0);
                        // nt::sleep(delay / 2 - upscale);
                        // PostMessageA(window, WM_LBUTTONUP, MK_LBUTTON, 0);
                        // nt::sleep(delay / 2 - upscale);

                    }
                }
                else { nt::sleep(10); }
        }
    }
}