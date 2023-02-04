#include "commands.hpp"
#include "..\clicker\clicker.hpp"
#include "..\xorstr.h"
#include "..\lazy_importer.hpp"
#include "..\utilities\utils.hpp"

void commands::toggle_response() {
	clicker::enable = !clicker::enable; 
    
    if (clicker::enable == true) {

    std::cout << xorstr("done! clicker is now enabled.\n\n"); 
    LFN(SetConsoleTitleA, xorstr("clicker: enabled")); }

    if (clicker::enable == false) { 

    std::cout << xorstr("done! clicker is now disabled.\n\n"); 
    LFN(SetConsoleTitleA, xorstr("clicker: disabled")); }

}

void commands::upscale_response() {
    std::cout << xorstr("enter upscale value: ");

    std::cin >> commands::input2;
    try
    {
        clicker::upscale = atoi(commands::input2.c_str());
        if (clicker::upscale > 20) { std::cout << xorstr("error: keep value between -20 to 20\n\n"); clicker::upscale = 0; } if (clicker::upscale < -20) { std::cout << xorstr("error: keep value between -20 to 20\n\n"); clicker::upscale = 0; }
        std::cout << xorstr("\n\ncurrent upscale value: ") << clicker::upscale;
        std::cout << xorstr("\n\n");
    }
    catch (const std::exception& e)
    {
        std::cout << xorstr("invalid value entered, enter a number\n\n");
    }
}

void commands::clickdata_response() {
    std::cout << xorstr("recorded by: {your name}\naverage cps: {99.999}\nclicks in file: {123}\nclick type: butterfly\nfile name: example_clicks_123k.txt\nfile type: .txt\nlast updated: 1/1/23\n\n");
}

void commands::inventory_response() {
    clicker::inventory = !clicker::inventory; if (clicker::inventory == true) { std::cout << xorstr("done! inventory is now enabled.\n\n"); } if (clicker::inventory == false) { std::cout << xorstr("done! inventory is now disabled.\n\n"); }
}

void commands::help_response() {
    std::cout << xorstr("'toggle' - toggles clicker on and off\n'upscale' - increase or decrease the speed of the clicker (the higher the number the higher the cps)\n'clickdata' - displays the click information\n'inventory' - toggles inventory on and off\n\n");
}

void commands::invalid_response() {
    std::cout << xorstr("please enter a valid command. if you're unsure please use the 'help' command\n\n");
}