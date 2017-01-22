#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main(int argc, char **argv)
{
        int socket_fd;
        struct sockaddr_in server_listen_addr;
        unsigned short port_num = 0x8888;
        char recv_buf[100];

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

	while(1)
	{
		memset(recv_buf, 0, sizeof(recv_buf));
		if(-1 == read(socket_fd, recv_buf, 100))
		{
			printf("read data from socket failed!\n");
			return -1;
		}
		printf("%s\n", recv_buf);
	}
}

