#include <cstring>          // for memset()
#include <iostream>
#include <string>           // for std::string
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>         // for close()



int main() {
    struct addrinfo hints{};
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    struct addrinfo* res{nullptr};
    int err = getaddrinfo(nullptr, "30000", &hints, &res);
    if (err != 0) {
        std::cerr << "[Server] getaddrinfo: " << gai_strerror(err) << "\n";
        return 1;
    }

    int sockfd = -1;
    for (auto p = res; p != nullptr; p = p->ai_next) {
        if (p) {
            sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
            if (sockfd != -1 && bind(sockfd, p->ai_addr, p->ai_addrlen) == 0) {
                break;
            }

            if (sockfd != -1) {
                ::close(sockfd);
                sockfd = -1;
            }
        }
    }

    freeaddrinfo(res);

    if (sockfd == -1) {
        std::cerr << "[Server] Failed to bind to any socket\n";
        return 1;
    }

    if (listen(sockfd, 3) == -1) {
        std::cerr << "[Server] Listen Failed";
        ::close(sockfd);
        return 1;
    }

    std::cout << "[Server] Listening on port 30000...\n";


    struct sockaddr_storage theirAddr;
    socklen_t addrSize = sizeof(theirAddr);
    int new_fd = accept(sockfd, (struct sockaddr*)&theirAddr, &addrSize);
    if (new_fd == -1) {
        std::cerr << "[Server] Accept failed\n";
        ::close(sockfd);
        return 1;
    } else {
        std::cout << "[Sever] Starting chat app" <<'\n';
    }
    
    auto exitMessage = "/q";
    size_t BUFFSIZE = 50;

    char buff[BUFFSIZE];
    
    std::string buffSizeStr = std::to_string(BUFFSIZE);

    send(new_fd, buffSizeStr.c_str(), buffSizeStr.size(), 0);

    while (true) {
        std::cin.getline(buff, BUFFSIZE);
        send(new_fd, buff, BUFFSIZE, 0);
        if (strcmp(buff, exitMessage) == 0)  {break;}
        recv(new_fd, buff, BUFFSIZE, 0);
        std::cout << "[Client]"  << buff <<'\n';
        if (strcmp(buff, exitMessage) == 0)  {break;}

    }
    ::close(new_fd);
    ::close(sockfd);



    



}