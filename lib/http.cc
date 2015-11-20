#include "http.h"

HTTP::HTTP() {
    printf("Creating HTTP server socket... ");
}

HTTP::~HTTP() {
    close(http_socket);
}

void HTTP::init(int port) {
    if ((http_socket = socket(AF_INET, SOCK_STREAM, 0)) > 0) {
        printf("OK\n");
    }

    http_address.sin_family = AF_INET;
    http_address.sin_addr.s_addr = INADDR_ANY;
    http_address.sin_port = htons(port);

    buffer_size = 1024*1024;
    setsockopt(http_socket, SOL_SOCKET, SO_RCVBUF, &buffer_size, sizeof(buffer_size));

    for (int i = 0; i < MIDDLEWARE_LIMIT; i++) {
        plugins[i] = 0;
    }

    router = new Router();
    this->use(router);

    printf("Binding HTTP socket to port %d... ", port);
    if (bind(http_socket, (struct sockaddr *) &http_address, sizeof(http_address)) == 0) {
        printf("OK\n");
    }
}

void HTTP::use(IMiddleware* middleware) {
    int lastIndex = 0;
    while (plugins[lastIndex]) {
        lastIndex++;
    }
    plugins[lastIndex] = middleware;
}

void HTTP::response(std::string msg) {
    if (client_socket) {
        write(client_socket, msg.c_str(), msg.length());
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

        char * request_header = (char*)malloc(buffer_size);
        recv(client_socket, request_header, buffer_size, 0);
        //response(request_header);

        Request* request = new Request();
        request->parseHeader(request_header);

        int current_plugin = 0;
        while (plugins[current_plugin]) {
            plugins[current_plugin]->run(request);
            current_plugin++;
        }

        response("OK!");

        close(client_socket);
    }
    close(http_socket);
}
