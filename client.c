#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>  
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include<errno.h>

#define MSG_LEN	100

char recv_buf[MSG_LEN];
char send_buf[MSG_LEN];

void handler_recv_msg(int *socket_fd)
{
	while(1)
	{
		memset(recv_buf, 0, sizeof(recv_buf));
		if(-1 == read(*socket_fd, recv_buf, MSG_LEN))
		{
			printf("read data from socket failed:%d\n", errno);
			return;
		}
		else
		{
			printf("%s\n", recv_buf);
		}
	}
}

int main(int argc, char **argv)
{
        int socket_fd;
        struct sockaddr_in server_listen_addr;
        unsigned short port_num = 8888;
		pthread_t pid;

	printf("client is runing!\n");
	if(argc != 2)
	{
		printf("please input service ip address!\n");
		return -1;
	}

	//socket create
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == socket_fd)
	{
		printf("socket failed!\n");
		return -1;
	}
	printf("socket ok!\n");

	//connect service
        bzero(&server_listen_addr, sizeof(struct sockaddr_in));
        server_listen_addr.sin_family = AF_INET;
        server_listen_addr.sin_addr.s_addr = inet_addr(argv[1]);
        server_listen_addr.sin_port = htons(port_num);
	if(-1 == connect(socket_fd, (struct sockaddr *)(&server_listen_addr), sizeof(struct sockaddr)))
        {
                printf("connect failed!\n");
                return -1;
        }
        printf("connect ok!\n");
	
	pthread_create(&pid, NULL, (void*)handler_recv_msg, (void*)&socket_fd);
	
	while(1)
	{
		memset(send_buf, 0, sizeof(send_buf));
		fgets(send_buf, MSG_LEN, stdin);
		if(-1 == write(socket_fd, send_buf, MSG_LEN))
		{
			printf("read data from socket failed!\n");
			return -1;
		}
	}
}

