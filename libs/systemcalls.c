#include "../headers/systemcalls.h"

bool start_system(void) {
    return 1;
}

void power_off(void) {
    system("poweroff");
}