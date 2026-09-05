// Headers
#include "../headers/systemcalls.h"
#include "../headers/writelogs.h"

// Libs
#include <iostream>
#include "../libs/writelogs.c"
#include "../libs/systemcalls.c"

int main() {
    if (!start_system()) {
        std::cout << "error with starting system" << std::endl;
    }
    
    // Checking of all system dependeces like pipewire, nodes of sound, modules (remote controller, AMP)
    
    // system("sh ../scripts/startterminalscript.sh");

    // start the processes like (guitarix --nogui, listener for RC, AMP declaration and listener by uart usb)

    // main cycle of guitarix conf

    // handlers for any cases

    return 0;
}