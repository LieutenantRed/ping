#ifndef __STATUS__
#define __STATUS__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <time.h>


#define BUFFER_SIZE 100

#define handle_error(msg) \
	do { fprintf(stderr, msg); exit(EXIT_FAILURE); } while (0)

struct {
	ssize_t req;
	ssize_t resp;
} status;

void do_ping(int sock, char *ip);
int rcv_ping(int sock, char *ip, char *buf);

void display_info(char *ip, ssize_t n, u_char ttl, struct timespec sendtime);
void display_total();

#endif