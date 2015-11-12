#include "http.h"

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

    int current_plugin = 0;
    while (plugins[current_plugin]) {
      plugins[current_plugin]->run(request_header);
      current_plugin++;
    }

    response(request_header);

    close(client_socket);
  }
  close(http_socket);
}
