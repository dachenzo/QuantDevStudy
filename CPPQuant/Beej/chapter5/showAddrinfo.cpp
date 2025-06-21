#include <netdb.h>
#include <iostream>
#include <arpa/inet.h>


void printAddrinfo(struct addrinfo* node) {
    std::cout << "ai_ddr: " << node->ai_addr << '\n';
    std::cout << "ai_socktype: " << node->ai_socktype << '\n'; 
    std::cout << "ai_protocol: " << node->ai_protocol << '\n'; 
    std::cout << "ai_family: " << node->ai_family << '\n'; 
    std::cout << "ai_flags: " << node->ai_flags << '\n'; 
    char ipstr[INET6_ADDRSTRLEN];
    void* addr;
    if (node->ai_family == AF_INET) {
        struct sockaddr_in *ipv4 = (struct sockaddr_in *)node->ai_addr;
         addr = &(ipv4->sin_addr);
    } else { // AF_INET6
        struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)node->ai_addr;
        addr = &(ipv6->sin6_addr);
    }

    inet_ntop(node->ai_family, addr, ipstr, sizeof ipstr);
    printf("IP address: %s\n", ipstr);
}

int main() {
    struct addrinfo hints{}, *res;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    int status = getaddrinfo("google.com", "80", &hints, &res);

    if (status != 0) {
        std::cerr << "getaddrinfo error: " << gai_strerror(status) << '\n';
        return 1;
    }

    while (res) {
        printAddrinfo(res);
        res = res->ai_next;
        std::cout << "\n\n";
    }
    freeaddrinfo(res);
}