#include <iostream>
#include <Windows.h>
#include <numeric>
#include <functional>

#include "utils.hpp"
#include "..\lazy_importer.hpp"
#include "..\xorstr.h"
#include "..\clicker\clicker.hpp"
#include "..\clicker\csf.h"
#include "..\cmds\commands.hpp"
#include "..\clicker\clicks\clicks.hpp"

double utils::calculate_cps() {

	if (clicks::clickdata.empty()) {
		std::cerr << xorstr("error: no click delays found") << std::endl;
		return 0.0;
	}

	int total_time = std::accumulate(clicks::clickdata.begin(), clicks::clickdata.end(), 0);

	double cps = static_cast<double>(clicks::clickdata.size()) / (total_time / 1000.0);

	return cps;

}

void utils::set_keybind() {
	std::cout << xorstr("enter a keybind: ") << std::flush;
	clicker::bind = 0;
	while (clicker::bind == 0) {
		for (int i = 3; i < 256; i++)
		{
			if (i == 13 | i == 89)
			{
				i += 1;
			}
			if (GetAsyncKeyState((i)&SHRT_MAX) && clicker::bind == 0)
			{
				clicker::bind = i;
			}
		}
	}
}

void utils::launch_threads() {
	std::thread clicker_thread(clicker::thread);
	clicker_thread.detach();

	std::thread binds_thread(clicker::binds);
	binds_thread.detach();
}

void utils::separator() {
	std::cout << xorstr("===============================================================================================================") << std::endl << std::endl;
}

auto utils::initialize_console() -> void
{
	HWND console_hwnd{ LFN_(GetConsoleWindow)() };

	SetWindowPos(console_hwnd, 0, 0, 0, 0, 0, SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
	LFN(SetLayeredWindowAttributes, console_hwnd, 0, 230, LWA_ALPHA);
	LFN(SetWindowLong, console_hwnd, GWL_STYLE, GetWindowLong(console_hwnd, GWL_STYLE) | WS_BORDER);
	LFN(SetWindowLong, console_hwnd, GWL_EXSTYLE, GetWindowLong(console_hwnd, GWL_STYLE) | WS_EX_LAYERED);
	LFN(ShowScrollBar, console_hwnd, SB_VERT, false);
	SetWindowLong(console_hwnd, GWL_STYLE, GetWindowLong(console_hwnd, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

	utils::title();
	utils::show_logo();
	commands::help_response();

	utils::separator();
}

void utils::title() {
	if (clicker::enable) {
		SetConsoleTitleA(xorstr("clicker: enabled"));
	}
	else {
		SetConsoleTitleA(xorstr("clicker: disabled"));
	}
}

int utils::set_priority_class() {
	HANDLE process = GetCurrentProcess();
	if (!SetPriorityClass(process, HIGH_PRIORITY_CLASS)) {
		std::cerr << xorstr("failed to set priority :( ") << std::endl;
		nt::sleep(1500);
		return 1;
	}
}

void utils::show_logo() {
	system(clicker::enable ? xorstr("color 0a") : xorstr("color 0c"));

	std::cout << xorstr("       _ _      _             ") << std::endl;
	std::cout << xorstr("   ___| (_) ___| | _____ _ __ ") << std::endl;
	std::cout << xorstr("  / __| | |/ __| |/ / _ \\ '__|") << std::endl;
	std::cout << xorstr(" | (__| | | (__|   <  __/ |   ") << std::endl;
	std::cout << xorstr("  \\___|_|_|\\___|_|\\_\\___|_|   \n") << std::endl;
	
}

void utils::init() {

	utils::initialize_console();

	utils::set_keybind();

	system(xorstr("cls"));

	utils::title();
	utils::show_logo();
	commands::help_response();

	utils::separator();

	utils::set_priority_class();
	utils::launch_threads();

	commands::keybind_response();

}

std::string utils::getkeyname(const int id)
{
	static std::unordered_map<int, std::string> key_names =
	{
		{ 0, "None" },
		{ VK_LBUTTON, "Mouse 1" },
		{ VK_RBUTTON, "Mouse 2" },
		{ VK_MBUTTON, "Mouse 3" },
		{ VK_XBUTTON1, "Mouse 4" },
		{ VK_XBUTTON2, "Mouse 5" },
		{ VK_BACK, "Back" },
		{ VK_TAB, "Tab" },
		{ VK_CLEAR, "Clear" },
		{ VK_RETURN, "Enter" },
		{ VK_SHIFT, "Shift" },
		{ VK_CONTROL, "Ctrl" },
		{ VK_MENU, "Alt" },
		{ VK_PAUSE, "Pause" },
		{ VK_CAPITAL, "Caps Lock" },
		{ VK_ESCAPE, "Escape" },
		{ VK_SPACE, "Space" },
		{ VK_PRIOR, "Page Up" },
		{ VK_NEXT, "Page Down" },
		{ VK_END, "End" },
		{ VK_HOME, "Home" },
		{ VK_LEFT, "Left Key" },
		{ VK_UP, "Up Key" },
		{ VK_RIGHT, "Right Key" },
		{ VK_DOWN, "Down Key" },
		{ VK_SELECT, "Select" },
		{ VK_PRINT, "Print Screen" },
		{ VK_INSERT, "Insert" },
		{ VK_DELETE, "Delete" },
		{ VK_HELP, "Help" },
		{ VK_SLEEP, "Sleep" },
		{ VK_MULTIPLY, "*" },
		{ VK_ADD, "+" },
		{ VK_SUBTRACT, "-" },
		{ VK_DECIMAL, "." },
		{ VK_DIVIDE, "/" },
		{ VK_NUMLOCK, "Num Lock" },
		{ VK_SCROLL, "Scroll" },
		{ VK_LSHIFT, "Left Shift" },
		{ VK_RSHIFT, "Right Shift" },
		{ VK_LCONTROL, "Left Ctrl" },
		{ VK_RCONTROL, "Right Ctrl" },
		{ VK_LMENU, "Left Alt" },
		{ VK_RMENU, "Right Alt" },
	};

	if (id >= 0x30 && id <= 0x5A)
		return std::string(1, (char)id);

	if (id >= 0x60 && id <= 0x69)
		return "Num " + std::to_string(id - 0x60);

	if (id >= 0x70 && id <= 0x87)
		return "F" + std::to_string((id - 0x70) + 1);

	return key_names[id];
}