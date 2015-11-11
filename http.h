#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

class Middleware {
    
};

class HTTP {
    private:
        int http_socket;
        int client_socket;
        socklen_t http_address_len;
        int buffer_size;
        char * request_header;
        struct sockaddr_in http_address;

    public:
        HTTP();
        void init(int port);
        void start();
        void response(const char* msg);
};

HTTP::HTTP() {
    printf("Creating HTTP server socket... ");
    buffer_size = 1024;
    request_header = (char*)malloc(buffer_size);

    if ((http_socket = socket(AF_INET, SOCK_STREAM, 0)) > 0) {
        printf("OK\n");
    }
}

void HTTP::init(int port) {
    http_address.sin_family = AF_INET;
    http_address.sin_addr.s_addr = INADDR_ANY;
    http_address.sin_port = htons(port);

    printf("Binding HTTP socket to port %d... ", port);
    if (bind(http_socket, (struct sockaddr *) &http_address, sizeof(http_address)) == 0) {
        printf("OK\n");
    }
}

void HTTP::response(const char* msg) {
    if (client_socket) {
        write(client_socket, msg, strlen(msg));
    }
}

void HTTP::start() {
    while (true) {
        if (listen(http_socket, 10) < 0) {
            exit(1);
        }

        if ((client_socket = accept(http_socket, (struct sockaddr *) &http_address, &http_address_len)) < 0) {
            exit(1);
        }

        recv(client_socket, request_header, buffer_size, 0);
        printf("%s\n", request_header);

        response(request_header);

        close(client_socket);
    }
    close(http_socket);
}
