#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define PORT 88000
#define BUF_LENGTH 64
#define SRV_IP "0.0.0.0"
