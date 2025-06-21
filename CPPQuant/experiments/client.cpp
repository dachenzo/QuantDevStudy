#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>


int main() {
    struct sockaddr_storage their_addr;
    struct addrinfo *res{nullptr}, hints{};
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    int result = getaddrinfo("localhost", "30000", &hints, &res);
    if (result == -1) {
        printf("[Client] Failed to get addrinfo");
        return 1;
    }

    int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    while (res && sockfd == -1) {
        res = res->ai_next;
        sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    }

    if (sockfd == -1) {
        printf("[Client] Failed to get socket");
        return 1;
    }
    result = -1;
    result = connect(sockfd, res->ai_addr, res->ai_addrlen);
    if (result == -1) {
        printf("[Client] Failed to bind Server");
        return 1;
    }
    

    char msg[] = "Hello Amy";
    result = -1;
    result = send(sockfd, msg, 10, 0);
    if (result == -1) {
        printf("Failed to get message");
    
    } 
    

    close(sockfd);

}