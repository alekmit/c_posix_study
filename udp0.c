#include "udp.h"

int sock;


int main() {
    struct sockaddr_in addr, outer_addr;
    char buf[BUF_LENGTH];
    char* msg = "Hello from server!";
    int alen = sizeof(addr);
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    memset((char *) &addr, 0, alen);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(sock, &addr, alen)==-1){
        printf("Cannot bind socket!\n");
        return;    
    }
    printf("Socket is binded!\n");
    memset(buf, 0, BUF_LENGTH);
    if (recvfrom(sock, buf, BUF_LENGTH, 0, &outer_addr, &alen) == -1){
        printf("Error on socket!\n");
        return;
    }
    printf("%s\n", buf);
    sendto(sock, msg, BUF_LENGTH, 0, &outer_addr, alen);
    close(sock);
}

