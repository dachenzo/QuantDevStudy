#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <charconv>


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
        ::close(sockfd);
        return 1;
    }
    
    char buffSize[13];
    recv(sockfd, buffSize, 13, 0);
    size_t BUFFSIZE;
    auto [ptr, ec] = std::from_chars(buffSize, buffSize+sizeof(buffSize), BUFFSIZE);
    if (ec != std::errc()) {
        std::cout << "[Client] Failed to start chat APP, exiting";
        send(sockfd, "/q", 3, 0);
        ::close(sockfd);
        return 1;
    }
    auto exitMessage = "/q";
    char buff[BUFFSIZE];
    std::cout << "[Client] starting chat APP\n";

    while (true) {
        recv(sockfd, buff, BUFFSIZE, 0);
        std::cout << "[Server]"  << buff <<'\n';
        if (strcmp(buff, exitMessage) == 0)  {break;}
        std::cin.getline(buff, BUFFSIZE);
        send(sockfd, buff, BUFFSIZE, 0);
        if (strcmp(buff, exitMessage) == 0)  {break;}
        
    }




    ::close(sockfd);

}