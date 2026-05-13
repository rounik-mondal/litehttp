#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "../include/litehttp.h"

void res_send(
    Response *res,
    const char *body
) {

    // buffer to hold the full http response
    char response[4096];

    // build the http headers and glue the body at the end
    sprintf(response,

        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: %ld\r\n"
        "Connection: close\r\n"
        "\r\n"
        "%s",

        strlen(body),
        body
    );

    // blast it over the socket back to the client
    write(res->client,
          response,
          strlen(response));
}

void res_json(
    Response *res,
    const char *json
) {

    // buffer for the response string
    char response[4096];

    // same as above but set the content-type to json
    sprintf(response,

        "HTTP/1.1 200 OK\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: %ld\r\n"
        "Connection: close\r\n"
        "\r\n"
        "%s",

        strlen(json),
        json
    );

    // send it down the pipe
    write(res->client,
          response,
          strlen(response));
}