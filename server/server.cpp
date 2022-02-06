#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <vector>

#include "server.hpp"

#define QQ_PORT 51000

int main()
{
    int listenfd = -1;
    listenfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(listenfd == -1)
    {
        printf("Server create fail.\n");
        return 0;
    }

    sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(QQ_PORT);

    int bn = -1;
    bn = bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

    if(bn == -1)
    {
        printf("Bind socket error.\n");
        return 0;
    }

    int ln = -1;
    ln = listen(listenfd, 50);

    if(ln == -1)
    {
        printf("Listen function fail.\n");
        return 0;
    }

    printf("\n======waiting for client's request======\n");

    /***      Select      */
    fd_set tmpfd;
    int max_fd = listenfd;

    std::vector<int> array_fd;

    pthread_t thread;
    pthread_create(&thread, NULL, SendNull, (void*)&array_fd);

    while(true)
    {
        FD_ZERO(&tmpfd);
        FD_SET(listenfd, &tmpfd);

        for(int i = 0; i < array_fd.size(); i++)
        {
            if(array_fd[i] > 0)
            {
                FD_SET(array_fd[i], &tmpfd); 
                if (max_fd < array_fd[i])
                {
                    max_fd = array_fd[i];
                }
            }
        }

        int ret = select(max_fd + 1, &tmpfd, NULL, NULL, NULL);

        if(ret < 0)
        {
            printf("Select failed.\n");
            return 0;
        }

        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);

        if (FD_ISSET(listenfd, &tmpfd))
        {
            int m_connfd = accept(listenfd, (struct sockaddr *)&client_addr, &client_len);

            if(m_connfd == -1)
            {
                printf("Child socket accept connection failed.\n");
                continue;
            }
            
            else 
            {
                printf("we got a new connection, client_socket=%d, ip=%s, port=%d\n", 
                m_connfd, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
                array_fd.push_back(m_connfd);
            }
        }

        for(auto it = array_fd.begin(); it < array_fd.end(); it++)
        {
            if (*it < 0)
            {
                continue;
            }

            if (FD_ISSET(*it, &tmpfd))
            {
                char buffer[256];
                int recv_len = recv(*it, buffer, sizeof(buffer) - 1, 0);

                if(recv_len < 0)
                {
                    printf("Receive data fail.\n");
                    continue;
                }
                else if(recv_len == 0)      // socket disconnect.
                {
                    printf("client_socket=[%d] close, ip=%s, port=%d\n\n", 
                    *it, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
                    close(*it);
                    FD_CLR(*it, &tmpfd);
                    array_fd.erase(it);
                }
                else
                {
                    buffer[recv_len] = '\0';
                    printf("server recv:%s\n", buffer);
                    /***      Edit server function here.      */



                }
            }
        }
    }
}

void* SendNull(void* args)
{
    return 0;
}