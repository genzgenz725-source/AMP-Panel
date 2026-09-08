// Headers
#include "../headers/systemcalls.h"
#include "../headers/writelogs.h"

// Libs
#include <iostream>
#include <boost/process.hpp>
#include "../libs/writelogs.c"
#include "../libs/systemcalls.c"

enum error_type {
    OK = '0',
    PIPEWIRE = '1',
    GUITARIX = '2',
    AUDIOCARD = '3'
};

bool start_AMP() {
    namespace bp = boost::process;

    try {
        bp::child guitarix("/usr/bin/guitarix", bp::args({"--nogui", "--rpcport=7000"}));        
        guitarix.detach();
    } catch (const std::exception& e) {
        write_log("error with starting()");
        return false;
    }

    return true;
}

int main() {
    switch (static_cast<error_type>(check_system())) {
        case PIPEWIRE: {
            std::cout << "\033[33m[ERROR]\033[0m " << "pipewire does not exists" << std::endl;
            sleep(3);
            write_log("pipewire does not exists");
            power_off();
            break;
            return 0;
        }
        case GUITARIX: {
            std::cout << "\033[33m[ERROR]\033[0m " << "guitarix does not exists" << std::endl;
            sleep(3);
            write_log("guitarix does not exists");
            power_off();
            break;
            return 0;
        }
        case AUDIOCARD: {
            std::cout << "\033[33m[ERROR]\033[0m " << "audiocard does not turned on" << std::endl;
            sleep(3);
            write_log("audiocard does not turned on");
            power_off();
            break;
            return 0;
        }
        case OK: {
            break;
        }
        default: {
            std::cout << "\033[33m[ERROR]\033[0m " << "start_system return wrong value" << std::endl;
            sleep(3);
            write_log("start_system return wrong value");
            power_off();
            return 0;
        }
    }

    if (!start_AMP()) {
        std::cout << "\033[33m[ERROR]\033[0m " << "audiocard does not turned on" << std::endl;
        sleep(3);
        write_log("audiocard does not turned on");
        power_off();
        return 0;
    }

    if (!set_sound()) {
        std::cout << "\033[33m[ERROR]\033[0m " << "audiocard does not turned on" << std::endl;
        sleep(3);
        write_log("audiocard does not turned on");
        power_off();
        return 0;
    }

    /*
    start DE,
    mpv intro,
    first package with panel for auth and syn in other thread, 
    main manu,
    separate thread for listen remote control
    */
}