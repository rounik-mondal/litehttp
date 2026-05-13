#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h>
#include <unistd.h>

#include "../include/litehttp.h"

#define BUFFER_SIZE 4096

static void handle_client(App *app, int client_socket, char *buffer) {

  Request req;
  Response res;

  // keep track of the socket so we can send the response back
  res.client = client_socket;

  // turn the raw string into something we can work with
  parse_request(&req, buffer);

  // log what came in for debugging
  printf("[%s] %s\n", req.method, req.path);

  // loop through all our registered routes to find a match
  for (int i = 0; i < app->route_count; i++) {

    Route *route = &app->routes[i];

    // check if both method and path match perfectly
    if (

        strcmp(route->method, req.method) == 0

        &&

        strcmp(route->path, req.path) == 0

    ) {

      // we found a match! call the user's function
      route->handler(&req, &res);

      return; // done handling this request
    }
  }

  // if we get here, it means we looped through everything and found nothing
  res_send(&res, "<h1>404 Not Found</h1>");
}

void app_listen(App *app) {

  struct sockaddr_in address;

  int addrlen = sizeof(address);

  char buffer[BUFFER_SIZE];

  // grab a TCP socket from the OS
  app->server_fd = socket(AF_INET, SOCK_STREAM, 0);

  // panic if we couldn't get one
  if (app->server_fd == 0) {

    perror("socket failed");

    exit(EXIT_FAILURE);
  }

  // set up the address structure
  address.sin_family = AF_INET;

  // listen on all interfaces
  address.sin_addr.s_addr = INADDR_ANY;

  address.sin_port = htons(app->port);

  // tie our socket to the port
  if (

      bind(app->server_fd,

           (struct sockaddr *)&address,

           sizeof(address))

      < 0

  ) {

    perror("bind failed");

    exit(EXIT_FAILURE);
  }

  // start actively listening for incoming connections
  if (

      // 10 is the backlog queue size
      listen(app->server_fd, 10)

      < 0

  ) {

    perror("listen failed");

    exit(EXIT_FAILURE);
  }

  // tell the user we're good to go
  printf("LiteHTTP running on "
         "http://localhost:%d\n",

         app->port);

  // the main server loop
  while (1) {

    // block and wait for a client to connect
    int client_socket = accept(

        app->server_fd,

        (struct sockaddr *)&address,

        (socklen_t *)&addrlen);

    if (client_socket < 0) {

      perror("accept failed");

      continue; // don't crash, just try the next one
    }

    // clear out the buffer so old data doesn't mess us up
    memset(buffer, 0, BUFFER_SIZE);

    // read what the browser/client sent us
    read(client_socket, buffer, BUFFER_SIZE);

    // process the request
    handle_client(app, client_socket, buffer);

    // we're done, hang up the phone
    close(client_socket);
  }
}