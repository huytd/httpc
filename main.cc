#include "http.h"

int main() {
    HTTP server;
    server.init(8800);
    server.start();
}
