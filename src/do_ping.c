#include "status.h"

static uint16_t icmp_checksum(void* icmp_p) {
    // Cast the data pointer to one that can be indexed.
    char* data = (char*) icmp_p;
    size_t length = 16;

    // Initialise the accumulator.
    uint32_t acc = 0;

    // Handle complete 16-bit blocks.
    for (size_t i = 0; i + 1 < length; i += 2) {
        uint16_t word;
        memcpy(&word, data + i, 2);
        acc += htons(word);
        while (acc > 0xffff) {
            acc -= 0xffff;
        }
    }

    // Return the checksum in network byte order.
    return htons(~acc);
}

void do_ping(int sock, char *ip) {
        u_char buffer[16];
        memset(buffer, 0, 16);
        buffer[0] = 0x08;
        buffer[1] = 0x00;
        uint16_t csum = icmp_checksum(buffer);
        memcpy(buffer + 2, &csum, 2);

        struct sockaddr_in addr;
        memset(&addr, 0, sizeof(addr));
        addr.sin_family = AF_INET;
        if (inet_aton(ip, &addr.sin_addr) != 1)
                handle_error("invalid arg");

        sendto(sock, buffer, 16, 0, (struct sockaddr*)&addr, sizeof(addr));
        status.req++;
}