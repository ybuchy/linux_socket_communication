#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

unsigned int swap_endianness(unsigned int num) {
    unsigned int reversed = num;
    int num_bits = sizeof(num) * 8 - 1;

    for (num >>= 1; num; num >>= 1) {
	reversed <<= 1;
	reversed |= num & 1;
	num_bits--;
    }

    reversed <<= num_bits;
    
    return reversed;
}

int main (void) {
    char hostname[256];

    if (gethostname(hostname, sizeof(hostname)) == -1) {
	printf("Failed to get hostname\n");
	return 1;
    }

    struct hostent *host_entry = gethostbyname(hostname);
    if (host_entry == NULL) {
	printf("Failed to get infos about host\n");
	return 1;
    }

    char *host_ip = inet_ntoa(*((struct in_addr *) host_entry->h_addr));
    printf("ip: %s\n", host_ip);

    printf("Enter hostname of communication partner: ");
    char comm_hostname[256];
    fgets(comm_hostname, sizeof(comm_hostname), stdin);
    char *newline = strchr(comm_hostname, '\n');
    if (newline != NULL) *newline = '\0';

    printf("%s\n", comm_hostname);
    host_entry = gethostbyname(comm_hostname);
    if (host_entry == NULL) {
	printf("Failed to get infos about host\n");
	return 1;
    }

    char *comm_ip = inet_ntoa(*((struct in_addr *) host_entry->h_addr));
    printf("ip: %s\n", comm_ip);

    
    /* int socket_fd = socket(AF_INET, SOCK_RAW, ); */

    /* struct sockaddr_in addr; */
    /* addr.sin_family = AF_INET; */
    /* addr.sin_addr.s_addr = inet_addr("192.168.188.23"); */
    /* addr.sin_port = htons(12345); */

    /* if (bind(socket_fd, (struct sockaddr *) &addr, sizeof(struct sockaddr)) == -1) { */
    /* 	printf("Failed to bind to the socket! %d", errno); */
    /* 	return 1; */
    /* } */

    /* struct sockaddr_in out_addr; */
    /* out_addr.sin_family = AF_INET; */
    /* out_addr.sin_addr.s_addr = inet_addr("192.168.188.22"); */
    /* addr.sin_port = htons(21345); */

    /* int conn_fd = ( */

}
