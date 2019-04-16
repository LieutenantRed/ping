#include "status.h"

void do_ping(int sock, char *ip) {
        u_char buffer[2];
        buffer[0] = 0x08;
        buffer[1] = 0x00;

        struct sockaddr_in addr;
        memset(&addr, 0, sizeof(addr));
        addr.sin_family = AF_INET;
        if (inet_aton(ip, &addr.sin_addr) != 1)
                handle_error("invalid arg");

        sendto(sock, buffer, 2, 0, (struct sockaddr*)&addr, sizeof(addr));
        status.req++;
}