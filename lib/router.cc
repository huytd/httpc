#include "router.h"

Router::Router() {

}

void Router::run(const char * request_header) {
  printf("\nRouter is triggered with header:\n%s\n", request_header);
}
