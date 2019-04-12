#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <time.h>

void stat(int sig) {
	if (sig == SIGINT) {
		display_total();
		raise(SIGTERM);
	}
	return;
}

int main(int argc, char* argv) {
	char addr[15];
	memset(&addr, 0, 15);
	if (argc < 1) 
		handle_error("host ip required");
	else 
		memcpy(addr, argv[1], strlen(argv[1]));

	int ping = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (ping == -1)
		handle_error("Cannot create socket");

	signal(SIGINT, stat); //display total values on ctrl+c

	struct timespec start_time;
	clock_gettime(CLOCK_REALTIME, &start_time);
	struct timespec snd_time;
	
	for (int i = 0; 1; ++i) {
		if (do_ping(ping, addr)  != 0) 
			handle_error("no ping");
		clock_gettime(CLOCK_REALTIME, &snd_time);
		
		char buffer[BUFFER_SIZE];
		memset(buffer, 0, BUFFER_SIZE);
		
		if (rcv_ping(ping, addr, buffer) != 0)
			handle error("no answer");
		
		u_char *ttl_ptr = buffer + 64;

		display_info(addr, i, *ttl_ptr, snd_time);
	}	
	return 0;
}