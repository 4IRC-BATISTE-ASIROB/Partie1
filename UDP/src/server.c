#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <netinet/in.h> 

#define PORT 8080 
#define MAXLINE 1024 

int main() { 
    int sockfd; 
    char buffer[MAXLINE]; 
    char *pong = "PONG"; 
    struct sockaddr_in servaddr, cliaddr; 
     
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
     
    memset(&servaddr, 0, sizeof(servaddr)); 
    memset(&cliaddr, 0, sizeof(cliaddr)); 
     
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
    servaddr.sin_port = htons(PORT); 
     
    if ( bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 ) { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
     
    socklen_t len;
    int n; 
    len = sizeof(cliaddr);

    while(1) {
        n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);
        buffer[n] = '\0';
        
        if(strcmp(buffer, "PING") == 0) {
            sendto(sockfd, (const char *)pong, strlen(pong), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len);
            printf("PONG message sent.\n");
        }
    }

    return 0; 
} 
