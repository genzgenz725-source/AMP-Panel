#include "../headers/systemcalls.h"

unsigned char check_system(void) {
    if (access("/usr/bin/pipewire", F_OK) != 0) {
        return '1';     // pipewire does not exists
    }
    if (access("/usr/bin/guitarix", F_OK) != 0) {
        return '2';     // guitarix does not exists
    }
    if (access("/dev/snd/pcmC0D0c", F_OK) != 0) {
        return '3';     // audiocard does not exists
    }
    // !!! check usb panel stm32
    return '0';         // everything ok
}

void power_off(void) {
    system("poweroff");
}

bool set_sound() {
    pid_t pid1 = fork();
    if (pid1 == 0) {
        execlp("pw-link", "pw-link", "PCM2902...capture_FR", "gx_head_amp:in_0", NULL);
        exit(1);
    }

    pid_t pid2 = fork();
    if (pid2 == 0) {
        execlp("pw-link", "pw-link", "gx_head_fx:out_0", "speakers:in_0", NULL);
        exit(1);
    }

    pid_t pid3 = fork();
    if (pid3 == 0) {
        execlp("pw-link", "pw-link", "gx_head_fx:out_1", "speakers:in_1", NULL);
        exit(1);
    }
    return 1;
}

void listen_for_remote_control() {
    // logic of listen by nRF24L01+
}