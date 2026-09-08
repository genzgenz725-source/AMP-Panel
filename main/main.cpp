// Headers
#include "../headers/systemcalls.h"
#include "../headers/writelogs.h"

// Libs
#include <iostream>
#include <boost/process.hpp>
#include <thread>
#include "../libs/writelogs.c"
#include "../libs/systemcalls.c"
#include <ctime>

#define HOME getenv("HOME")

enum error_type {
    OK = '0',
    PIPEWIRE = '1',
    GUITARIX = '2',
    AUDIOCARD = '3'
};
enum choice_type {
    DZEN = 1,
    JUSTLISTEN = 2,
    PLAYTOGETHER = 3
};
volatile bool flag = true;  // only for menu_background

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

bool startDE() {
    namespace bp = boost::process;

    try {
        bp::child DE("/usr/bin/DE", bp::args({"&"}));
        DE.detach();
    } catch (const std::exception& e) {
        return 0;
    }
    return 1;
}

void mpv() {
    namespace bp = boost::process;
    std::string path = static_cast<std::string>(HOME) + ".amp_data/intro.MP4";

    try {
        bp::child mpv("/usr/bin/mpv", bp::args({path}));
        mpv.join();
    } catch (const std::exception& e) {
        write_log("error with mpv exec");
        return;
    }
}

void menu_background() {
    namespace bp = boost::process;
    
    char path[128];
    char tmp_str[3];
    strcpy(path, getenv("HOME"));
    strcat(path, "/.amp_data/BG_music/music");

    char path_to_menu[128];
    strcat(path_to_menu, HOME);
    strcat(HOME, ".amp_data/bin/menu");
    bp::child menu("/usr/bin/kitty", bp::args({path_to_menu}));

    while (flag) {
        sprintf(tmp_str, "%02d", rand() % 15 + 1);
        strcat(path, tmp_str);
        strcat(path, ".mp3");
        try {
            bp::child mpv("/usr/bin/mpv", bp::args({path}));
            mpv.join();
        } catch (const std::exception& e) {
            write_log("error with mpv exec");
            return;
        }
        memset(path, 0, 128);
    }
    
    return;
}

int cmd_from_menu() {
    unsigned int num;
    while (!num) {
        void* addr = reinterpret_cast<void*>(0x40000000);
        num = *reinterpret_cast<int*>(addr);
        sleep(1);
    }
    return num;
}

void guitarix_conf() {
    while (true) {
        // read address and change profile
    }
}

void open_browser_client() {}

int main() {
    srand(time(NULL));

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

    if (!startDE()) {
        write_log("error with DE exec");
    }

    std::thread menu(menu_background); menu.detach();
    std::thread listener(listen_for_remote_control); listener.detach();

    switch (static_cast<choice_type>(cmd_from_menu())) {
        case DZEN: {
            // choice from amp panel
        }
        case JUSTLISTEN: {
            // open youtube music and control by remote control
        }
        case PLAYTOGETHER: {
            // browser + guitarix settings
        }
        default: {
            std::cout << "\033[33m[ERROR]\033[0m " << "cmd_from_menu return wrong value" << std::endl;
            sleep(3);
            write_log("cmd_from_menu return wrong value");
            power_off();
            return 0;
        }
    }
}