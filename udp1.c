#include "udp.h"

int sock;


int main() {
    struct sockaddr_in addr;
    char buf[BUF_LENGTH];
    char* msg = "Hello from client!";
    int alen = sizeof(addr);
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    memset((char *) &addr, 0, alen);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    if (inet_aton(SRV_IP, &addr.sin_addr)==0) {
        printf("inet_aton() failed\n");
        exit(1);
    }
    sendto(sock, msg, BUF_LENGTH, 0, &addr, alen);
    memset(buf, 0, BUF_LENGTH);    
    if (recvfrom(sock, buf, BUF_LENGTH, 0, &addr, &alen) == -1){
        printf("Error on socket!\n");
        return;
    }
    printf("%s\n", buf);
    close(sock);
}

