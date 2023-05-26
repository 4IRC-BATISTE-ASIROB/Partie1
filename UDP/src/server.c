#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdbool.h>

#define PORT 8080
#define MAXLINE 1024

#define ON 1
#define OFF 0

int main()
{
    int sockfd;
    char buffer[MAXLINE];
    bool state = OFF;
    struct sockaddr_in servaddr, cliaddr;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    socklen_t len;
    int n;
    len = sizeof(cliaddr);

    while (1)
    {
        n = recvfrom(sockfd, (char *)&state, sizeof(state), MSG_WAITALL, (struct sockaddr *)&cliaddr, &len);
        if (n > 0 && state == ON)
        {
            char *message = "Connected to server.";
            sendto(sockfd, (const char *)message, strlen(message), MSG_CONFIRM, (const struct sockaddr *)&cliaddr, len);
            printf("Client connected.\n");
            while (state == ON)
            {
                // On récupère le message du client
                n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *)&cliaddr, &len);
                buffer[n] = '\0';

                // Si le message est "DISCONNECT", le client se déconnecte
                if (n > 0 && strcmp(buffer, "DISCONNECT") == 0)
                {
                    state = OFF;
                    printf("Client disconnected.\n");
                }
                else
                {
                    printf("Client : %s\n", buffer);
                }
            }
        }
    }

    return 0;
}
