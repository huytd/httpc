#include "lib/http.h"

int main() {
    HTTP server;
    server.init(8080);
    server.start();
}
