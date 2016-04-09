#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
 
#define BACKLOG 5
#define BUFF_SIZE 6
#define PORT 9999
 
int fd[BACKLOG];
int con_num;
 
void ha_ha(void)
{
        sleep(1);
}
 
int main(int argc, char** argv)
{
        int sock_fd, new_fd;
        struct sockaddr_in server_addr;
        struct sockaddr_in client_addr;
        socklen_t sin_size;
 
        fd_set fdsr;
        struct timeval tv;
        char buf[BUFF_SIZE+1];
 
        int ret = 0;
        int i = 0;
 
        sock_fd = socket(AF_INET, SOCK_STREAM, 0);
 
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(PORT);
        server_addr.sin_addr.s_addr = INADDR_ANY;
 
        memset(server_addr.sin_zero, 0, sizeof(server_addr.sin_zero));
 
        bind(sock_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
 
        listen(sock_fd, BACKLOG);
 
        printf("listening...\n");


        while(1)
	{
                FD_ZERO(&fdsr);
                FD_SET(sock_fd, &fdsr);
 
                tv.tv_sec = 1;
                tv.tv_usec = 0;
 
                for(i = 0; i < BACKLOG; i++)
                {
                        if(fd[i] != 0)
                        {
                                FD_SET(fd[i], &fdsr);
                        }
                }
 
                select(sock_fd+BACKLOG, &fdsr, NULL, NULL, &tv);
 
               if(FD_ISSET(sock_fd, &fdsr))
                {
                        new_fd = accept(sock_fd, (struct sockaddr*)&client_addr, &sin_size);
                        if(con_num < BACKLOG)
                        {
                                fd[con_num++] = new_fd;
			}
                }
 
                for(i = 0; i < con_num; i++)
                {
                        if(FD_ISSET(fd[i], &fdsr))
                        {
                                ret = recv(fd[i], buf, BUFF_SIZE*sizeof(char), 0);
                                memset(&buf[ret], '\0', 1);
				printf("%s\n", buf);
                                ha_ha();
                                send(fd[i], buf, BUFF_SIZE, 0);
                        }
                }
        }
 
        return 0;
 
 }
