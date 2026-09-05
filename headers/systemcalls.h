#ifndef SYSTEMCALLS_H
#define SYSTEMCALLS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

bool start_system(void);    // start checking for pipewire, system calls, synchronization with AMP panel

void power_off(void);        // will power off the server

#ifdef __cplusplus
}
#endif

#endif