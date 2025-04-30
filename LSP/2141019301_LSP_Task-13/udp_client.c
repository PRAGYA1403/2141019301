#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 9000
#define SERVER_IP "127.0.0.1"  // Change if server is on different machine

int main() {
    int sockfd;
    char buffer[1024];
    struct sockaddr_in servaddr;
    socklen_t addr_len = sizeof(servaddr);

    // Create socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Allow address reuse (optional but consistent with server)
    int opt = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Set server address
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Send message
    const char *message = "Hello from Client";
    sendto(sockfd, message, strlen(message), 0, (const struct sockaddr *)&servaddr, sizeof(servaddr));
    printf("[CLIENT] Message sent to server: %s\n", message);

    // Receive server reply
    int n = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0, (struct sockaddr *)&servaddr, &addr_len);
    buffer[n] = '\0';
    printf("[CLIENT] Server says: %s\n", buffer);

    close(sockfd);
    return 0;
}

