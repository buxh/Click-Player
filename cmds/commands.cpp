#include <iostream>

#include "commands.hpp"
#include "..\clicker\clicker.hpp"
#include "..\clicker\clicks\clicks.hpp"
#include "..\xorstr.h"
#include "..\lazy_importer.hpp"
#include "..\utilities\utils.hpp"
#include "..\clicker\csf.h"

void commands::toggle_response() {

	clicker::enable = !clicker::enable; 
    
    if (clicker::enable) {
        std::cout << xorstr("done! clicker is now enabled.\n\n");
        SetConsoleTitleA(xorstr("clicker: enabled"));
    }
    else {
        std::cout << xorstr("done! clicker is now disabled.\n\n");
        SetConsoleTitleA(xorstr("clicker: disabled"));
    }

}

void commands::cps_response() {

    int cps = utils::calculate_cps();
    std::cout << xorstr("current cps: ") << cps << "\n\n";

}

void commands::upscale_response() {

    std::cout << xorstr("enter upscale value: ");

    std::cin >> commands::input2;
    try
    {
        clicker::upscale = atoi(commands::input2.c_str());
        if (clicker::upscale > 20 || clicker::upscale < -20) { std::cout << xorstr("error: keep value between -20 to 20\n\n"); clicker::upscale = 0; }
        
        std::cout << xorstr("\n\ncurrent upscale value: ") << clicker::upscale << xorstr("\n\n");
    }
    catch (const std::exception& e) 
    {
        std::cout << xorstr("invalid value entered, enter a number\n\n");
    }

}

void commands::clickdata_response() {

    utils::count = clicks::clickdata.size();
    utils::cps = utils::calculate_cps();
    utils::recdate = xorstr("1/1/23");
    utils::clicktype = (utils::cps > 16) ? xorstr("butterfly") : xorstr("jitter");
    utils::username = getenv(xorstr("USERNAME"));

    std::cout << xorstr("recorded by: ") << utils::username << 
        xorstr("\naverage cps: ") << utils::cps << 
        xorstr("\nclicks in file: ")<< utils::count << 
        xorstr("\nclick type: ") << utils::clicktype << 
        xorstr("\nstorage name: clickdata\nstorage type: vector\nlast updated:") << utils::recdate << std::endl << std::endl;

}

void commands::inventory_response() {

    clicker::inventory = !clicker::inventory;
    if (clicker::inventory) { std::cout << xorstr("done! inventory click is now enabled.\n\n"); }
    else { std::cout << xorstr("done! inventory click is now disabled.\n\n"); }

}

void commands::help_response() {

    std::cout << xorstr("'toggle' - toggles clicker on and off\n'upscale' - increase or decrease the speed of the clicker (the higher the number the higher the cps)\n'clickdata' - displays the click information\n'inventory' - toggles inventory on and off\n'cps' - shows the current cps\n'keybind' - view toggle keybind\n'rmblock' - toggles right mouse button lock\n'filter' - skip over delays exceeding the specified value in milliseconds that you have chosen\n\n");

}

void commands::invalid_response() {

    std::cout << xorstr("please enter a valid command. if you're unsure please use the 'help' command\n\n");

}

void commands::keybind_response() {

    std::cout << xorstr("your keybind: ") << utils::getkeyname(clicker::bind) << std::endl << std::endl;

}

void commands::rmb_lock_response() {

    clicker::rmb_lock = !clicker::rmb_lock;
    if (clicker::rmb_lock) { std::cout << xorstr("done! rmb lock is now enabled.\n\n"); }
    else { std::cout << xorstr("done! rmb lock is now disabled.\n\n"); }

}

void commands::filter_response() {

    std::cout << xorstr("enter delay to filter: ");
    std::cin >> clicker::delayfilter;
    std::cout << std::endl << std::endl;
    std::cout << xorstr("delay set to: ") << clicker::delayfilter << std::endl << std::endl;

}
