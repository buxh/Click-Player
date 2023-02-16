#include <iostream>
#include <map>
#include <string>
#include <thread>
#include <chrono>
#include <functional>

#include "cmds\commands.hpp"
#include "xorstr.h"
#include "utilities\utils.hpp"

int main() {
    utils::init();

    const std::unordered_map<std::string, std::function<void()>> commands = {
        {xorstr("toggle"), commands::toggle_response},
        {xorstr("upscale"), commands::upscale_response},
        {xorstr("clickdata"), commands::clickdata_response},
        {xorstr("inventory"), commands::inventory_response},
        {xorstr("help"), commands::help_response},
        {xorstr("cps"), commands::cps_response},
        {xorstr("keybind"), commands::keybind_response},
        {xorstr("rmblock"), commands::rmb_lock_response}
    };

    for (;; std::this_thread::sleep_for(std::chrono::milliseconds(1))) {

        std::cout << xorstr("> ") << std::flush;
        std::cin >> commands::input;

        std::cout << std::endl;

        std::transform(commands::input.begin(), commands::input.end(), commands::input.begin(),
            [](unsigned char c) { return std::tolower(c, std::locale()); });


        const auto it = commands.find(commands::input);

        if (it != commands.end()) { it->second(); }
        else { commands::invalid_response(); }

    }

    return 0;
}
