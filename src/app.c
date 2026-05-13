#include <stdlib.h>

#include "../include/litehttp.h"

App *app_create(int port) {

    // grab some memory for our app structure
    App *app = malloc(sizeof(App));

    // set the port we want to listen on
    app->port = port;

    // start with zero routes registered
    app->route_count = 0;

    return app;
}