#include "router.h"

Router::Router() {

}

void Router::run(int socket, Request* request) {
    printf("> Router for %d: %s\n", socket, request->getUrl().c_str());
}
