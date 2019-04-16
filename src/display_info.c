#include "status.h"

void display_info(char *ip, ssize_t n, u_char ttl, struct timespec sendtime) {
        struct timespec current_time;
        clock_gettime(CLOCK_REALTIME, &current_time);

        time_t sec = current_time.tv_sec - sendtime.tv_sec;
        long nsec = current_time.tv_nsec - sendtime.tv_nsec;
        nsec = nsec / 1000; //from nano to ms
        if (sec > 0) {
                nsec = nsec / 1000;
        }
        double time = sec + nsec;
        printf("from %s: seq = %d ttl = %d time = %f (m)s", ip, n, ttl, time);
}