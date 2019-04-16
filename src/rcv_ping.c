#include "status.h"

int rcv_ping(int sock, char *ip, char *buf) {
        while (1) {
                recvfrom(sock, buf, BUFFER_SIZE, 0, 0, 0);
                u_char pack[2];
                memcpy(buf + 20, pack, 2);
                if ((pack[1] == 0) && (pack[0] == 0))
                        return 0;
        }
        status.resp++;       
}