#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <net/if.h>	// struct ifreq
#include <sys/ioctl.h>	// ioctl
#include <netinet/in.h>

#ifdef __LINUX__

#include <netinet/ether.h>
#include <netpacket/packet.h>	// struct sockaddr_ll
#define IFNAME "enp5s0f1"

#elif __APPLE__

/* different interfaces compared with Linux */
/* use bpf: a device */
#include <netinet/if_ether.h>
#include <net/bpf.h>
#include <netinet/ethernet.h>
#define IFNAME "en0"

#endif

void normally_exit(int signal)
{
	printf("\nexit!\n");
	exit(0);
}

// raw socket needs to be a administrator!
int main()
{
	// normally exit
	signal(SIGINT, &normally_exit);	
	unsigned char buf[1024];
	char output[1024];
	char msg[] = "";
	// work above the IP level
	//int fd = socket(PF_INET, SOCK_RAW, ...);
	// work from the link level, but not recommended!
	// fd = socket(PF_INET, SOCK_PACKET, ...);
	// PF_PACKET cluster : SOCK_RAW/SOCK_DGRAM
	int fd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

	// set the interface as promisc mode
	struct ifreq ethreq;

	strncpy(ethreq.ifr_name, IFNAME, IFNAMSIZ);
	// get net interface
	if((ioctl(fd, SIOCGIFINDEX, &ethreq)) == -1)
	{
		perror("ioctl error!\n");
		close(fd);
		exit(1);
	}

	// promisc
	//ethreq.ifr_flags |= IFF_PROMISC;
	// and need to set it with SIOCSIFFLAGS
	struct sockaddr_ll sll;
	memset(&sll, 0, sizeof(sll));
	sll.sll_ifindex = ethreq.ifr_ifindex;

	int len = sendto(fd, msg, sizeof(msg), 0, (struct sockaddr*)&sll, sizeof(sll));
	if(len == -1)
		perror("failed to send msg!\n");
	else
		printf("have send the msg: %s\n", msg);

	// buf[12:13] is to judge the protocol type, just like 0800 or 0806, and so on
	while(1)
	{	
		len = recvfrom(fd, buf, sizeof(buf), 0, NULL, NULL);
		int i = 0;
		for( ; i<len; i++)
		{	
			char temp[3] = "";
			sprintf(temp, "%02x ", buf[i]);
			strcat(output, temp);
		}
		if(buf[12] == 0x08 && buf[13] == 0x06)
			printf("ARP packet:");
		else if(buf[12] == 0x08 && buf[13] == 0x00)
		{
			printf("IP packet:");
			if(buf[23] == 0x06)
				printf(" TCP -- ");
			else if(buf[23] == 0x11)
				printf(" UDP -- ");
		}
		printf("data: %s, len: %d\n", output, len);
		memset(output, 0, sizeof(output));
	}
	// invoke the parse_sock_hex perl script to converse the hex data to ascii
	return 0;
}
