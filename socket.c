#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

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

unsigned int get_network_addr(unsigned int num1, unsigned int num2, unsigned int num3, unsigned int num4) {
    unsigned int addr = swap_endianness(num4);
    addr += swap_endianness(num3) << 8;
    addr += swap_endianness(num2) << 16;
    addr += swap_endianness(num1) << 24;
    return addr;
}

struct sokaddr {
    sa_family_t sa_family;
    char sa_data[14];
};

struct sockaddr_in {
    short int sin_family;
    unsigned short int sin_port;
    struct in_addr sin_addr;
    unsigned char sin_zero[8];
};

struct in_addr {
    unsigned long s_addr;
};

int main (int argc, char **argv) {
    int socket_fd = socket(AF_INET, SOCK_DGRAM, 17);

    struct sokaddr addr;
    memset(&addr, 0, sizeof(struct sokaddr));

    addr->sa_family = AF_INET;

    /* addr->sa_data = ; */

    if (bind(socket_fd, (const struct sokaddr *) addr, sizeof(struct sokaddr)) == -1) {
	printf("Failed to bind to the socket!");
    	return 1;
    }
}
