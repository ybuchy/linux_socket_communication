#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

char *get_ip_str(char *hostname) {
    struct hostent *host_entry = gethostbyname(hostname);
    if (host_entry == NULL) {
	printf("Failed to get infos about host: %s\n", hostname);
	return NULL;
    }
    char *ip = (char *) calloc(16, sizeof(char));
    strncpy(ip, inet_ntoa(*((struct in_addr *) host_entry->h_addr)), 16);
    return ip;
}

int main (void) {
    char hostname[256] = { 0 };
    if (gethostname(hostname, sizeof(hostname)) == -1) {
	printf("Failed to get hostname");
	return 1;
    }

    char *host_ip = get_ip_str(hostname);
    if (host_ip == NULL) {
	printf("Failed to get ip addr of: %s", hostname);
	return 1;
    }
    printf("ip: %s\n", host_ip);

    printf("Enter hostname of communication partner: ");
    char comm_hostname[256] = { 0 };
    fgets(comm_hostname, sizeof(comm_hostname), stdin);
    char *newline = strchr(comm_hostname, '\n');
    if (newline != NULL) *newline = '\0';

    char *comm_ip = get_ip_str(comm_hostname);
    if (comm_ip == NULL) {
	printf("Failed to get ip addr of: %s", comm_hostname);
	return 1;
    }
    printf("ip: %s\n", comm_ip);

    int socket_fd = socket(AF_INET, SOCK_DGRAM, 17);
    if (socket_fd == -1) {
	printf("Failed to create socketfd %d", errno);
	return 1;
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(host_ip);
    addr.sin_port = htons(12345);
    if (bind(socket_fd, (struct sockaddr *) &addr, sizeof(struct sockaddr)) == -1) {
    	printf("Failed to bind to the socket for host: %s! %d", host_ip, errno);
    	return 1;
    }
}
