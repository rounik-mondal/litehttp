#include <string.h>

#include "../include/litehttp.h"

void app_get(App *app,
             const char *path,
             RouteHandler handler) {

    // get a pointer to the next available route slot and bump the count
    Route *route =
        &app->routes[app->route_count++];

    // register it as a GET request
    strcpy(route->method, "GET");
    strcpy(route->path, path);

    // store the function pointer so we can call it later
    route->handler = handler;
}

void app_post(App *app,
              const char *path,
              RouteHandler handler) {

    // do the exact same thing but for POST
    Route *route =
        &app->routes[app->route_count++];

    strcpy(route->method, "POST");
    strcpy(route->path, path);

    route->handler = handler;
}