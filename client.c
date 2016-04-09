#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
 
 
#define DEST_IP "127.0.0.1"
#define DEST_PORT 9999
 
int main(int argc, char** argv)
{
        int sockfd = 0;
	int len = 0;
        struct sockaddr_in dest_addr;

	char* msg = "hello"; 

        sockfd = socket(AF_INET, SOCK_STREAM, 0);
 
        dest_addr.sin_family = AF_INET;
        dest_addr.sin_port = htons(DEST_PORT);
        dest_addr.sin_addr.s_addr = inet_addr(DEST_IP);
 
 
        memset(dest_addr.sin_zero, 0, sizeof(dest_addr.sin_zero));
 
        connect(sockfd, (struct sockaddr*)&dest_addr, sizeof(struct sockaddr_in));
 	len = strlen(msg);
        while(1)
        {
                sleep(2);
 		send(sockfd, msg, len, 0);
        }
 
       return 0;
}

