#include "status.h"

void display_info(char *ip, ssize_t n, u_char ttl, struct timespec sendtime) {
        struct timespec current_time;
        clock_gettime(CLOCK_REALTIME, &current_time);

        long nsec = current_time.tv_nsec - sendtime.tv_nsec;
        nsec = nsec / 1000000; //from nano to ms
        printf("from %s: seq = %d ttl = %d time = %d ms\n", ip, n, ttl, nsec);
}