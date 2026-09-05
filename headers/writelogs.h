#ifndef LOGS
#define LOGS

#ifdef __cplusplus
extern "C" {
#endif

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h> 
#include <arpa/inet.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <net/ethernet.h>
#include <errno.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/stat.h>

#define PORT 7252
#define BUFFER 1024
#define HOME getenv("HOME")

bool write_log(const char* logs);   // writing logs

bool send_logs(const char* ip);       // sending logs to ip by raw socket

#ifdef __cplusplus
}
#endif

#endif