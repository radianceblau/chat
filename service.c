#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>


int main()
{
        int socket_fd, accept_socket_fd;
        struct sockaddr_in server_listen_addr, client_addr;
        unsigned short port_num = 0x8888;
        char send_buf[100];
	int addr_len;

        printf("server is runing!\n");
        //create socket. appoint protocal type and connection type
        socket_fd = socket(AF_INET, SOCK_STREAM, 0);
        if(-1 == socket_fd)
        {
                printf("socket failed!\n");
                return -1;
        }
        printf("socket ok!\n");

        //bind address for listen
        bzero(&server_listen_addr, sizeof(struct sockaddr_in));
        server_listen_addr.sin_family = AF_INET;
        server_listen_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        server_listen_addr.sin_port = htons(port_num);
        if(-1 == bind(socket_fd, (struct sockaddr *)(&server_listen_addr), sizeof(struct sockaddr_in)))
        {
                printf("bind failed!\n");
                return -1;
        }
        printf("bind ok!\n");

        //start listen specific port
        if(-1 == listen(socket_fd, 5))
        {
                printf("listen failed!\n");
                return -1;
        }
        printf("listen ok!\n");

        //accept client connect request
		addr_len = sizeof(struct sockaddr_in);
        if(-1 == (accept_socket_fd = accept(socket_fd, (struct sockaddr *)(&client_addr), &addr_len)))
        {
                printf("accept failed!\n");
                return -1;
        }
        printf("accept ok! server accept clent:%#x:%#x\n", ntohl(client_addr.sin_addr.s_addr), ntohs(client_addr.sin_port));

        while(1)
        {
                memset(send_buf, 0, sizeof(send_buf));
                sprintf(send_buf, "welcome to my server!");
                send(accept_socket_fd, send_buf, strlen(send_buf), 0);
                usleep(50000);
        }

        close(accept_socket_fd);
        close(socket_fd);

        return 0;
}