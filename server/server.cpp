#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <vector>

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
    bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

    if(bn == -1)
    {
        printf("Bind socket error.\n");
        return 0;
    }

    int ln = -1;
    listen(listenfd, 50);

    if(ln == -1)
    {
        printf("Listen function fail.\n");
        return 0;
    }

    printf("\n======waiting for client's request======\n");

    
}