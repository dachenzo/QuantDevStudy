#include <cstring>          // for memset()
#include <iostream>
#include <string>           // for std::string
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>         // for close()

int main() {
    // 1) Prepare hints
    struct addrinfo hints{};
    hints.ai_family   = AF_UNSPEC;      // IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM;    // TCP
    hints.ai_flags    = AI_PASSIVE;     // wildcard IP (0.0.0.0 or ::)

    struct addrinfo* res = nullptr;
    int err = getaddrinfo(nullptr, "30000", &hints, &res);
    if (err != 0) {
        std::cerr << "[Server] getaddrinfo: " << gai_strerror(err) << "\n";
        return 1;
    }

    // 2) Try sockets until one succeeds
    int sockfd = -1;
    for (auto p = res; p != nullptr; p = p->ai_next) {
        sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (sockfd != -1) {
            if (bind(sockfd, p->ai_addr, p->ai_addrlen) == 0) {
                // Success!
                break;
            }
            ::close(sockfd);
            sockfd = -1;
        }
    }
    freeaddrinfo(res);

    if (sockfd == -1) {
        std::cerr << "[Server] Failed to bind any socket\n";
        return 1;
    }

    // 3) Listen
    if (listen(sockfd, 3) == -1) {
        std::cerr << "[Server] listen failed\n";
        ::close(sockfd);
        return 1;
    }
    std::cout << "[Server] Listening on port 30000...\n";

    // 4) Accept one connection
    struct sockaddr_storage their_addr;
    socklen_t addr_size = sizeof(their_addr);
    int new_fd = accept(sockfd, (struct sockaddr*)&their_addr, &addr_size);
    if (new_fd == -1) {
        std::cerr << "[Server] accept failed\n";
        ::close(sockfd);
        return 1;
    }

    // 5) Receive up to 9 bytes (plus a null terminator)
    char buf[10] = {0};
    ssize_t n = recv(new_fd, buf, sizeof(buf)-1, 0);
    if (n <= 0) {
        std::cerr << "[Server] recv error or connection closed\n";
    } else {
        std::cout << "[Server] Received: " << buf << "\n";
    }

    ::close(new_fd);
    ::close(sockfd);
    return 0;
}
 