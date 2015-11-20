#include "router.h"

Router::Router() {

}

void Router::run(Request* request) {
    printf("> Router: %s\n", request->getUrl().c_str());
}
