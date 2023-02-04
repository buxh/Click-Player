#include <iostream>
#include <Windows.h>

#include "utils.hpp"
#include "..\lazy_importer.hpp"
#include "..\xorstr.h"
#include "..\clicker\clicker.hpp"
#include "..\clicker\csf.h"
#include "..\cmds\commands.hpp"

auto utils::initialize_console() -> void
{
	HWND console_hwnd{ LFN_(GetConsoleWindow)() };

	SetWindowPos(console_hwnd, 0, 0, 0, 0, 0, SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
	LFN(SetLayeredWindowAttributes, console_hwnd, 0, 230, LWA_ALPHA);
	LFN(SetWindowLong, console_hwnd, GWL_STYLE, GetWindowLong(console_hwnd, GWL_STYLE) | WS_BORDER);
	LFN(SetWindowLong, console_hwnd, GWL_EXSTYLE, GetWindowLong(console_hwnd, GWL_STYLE) | WS_EX_LAYERED);
	LFN(ShowScrollBar, console_hwnd, SB_VERT, false);
	SetWindowLong(console_hwnd, GWL_STYLE, GetWindowLong(console_hwnd, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
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

	utils::show_logo();
	utils::set_priority_class();
	utils::initialize_console();
	utils::title();
	commands::help_response();
	std::cout << xorstr("================================================================================================================\n") << std::endl;

	std::thread clicker_thread(clicker::thread);
	clicker_thread.detach();
}