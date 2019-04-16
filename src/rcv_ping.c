#include "status.h"

int rcv_ping(int sock, char *ip, char *buf) {
		struct timeval timeout;
		memset(&timeout, 0, sizeof(struct timeval));
		timeout.tv_sec = 3;

		fd_set set;
		FD_ZERO(&set);

        while (1) {
                FD_SET(sock, &set);
                select(FD_SETSIZE, &set, NULL, NULL, &timeout);
                recvfrom(sock, buf, BUFFER_SIZE, 0, 0, 0);
                u_char pack[2];
                memcpy(buf + 20, pack, 2);
                if ((pack[1] == 0) && (pack[0] == 0))
                        return 0;
        }
        status.resp++;       
}