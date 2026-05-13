#include <stdio.h>
#include <string.h>

#include "../include/litehttp.h"

void parse_request(
    Request *req,
    const char *buffer
) {

    // extract the basic info like GET /path HTTP/1.1 from the first line
    sscanf(buffer,
           "%s %s %s",
           req->method,
           req->path,
           req->version);

    // look for the double newline that separates headers from the body
    const char *body_start =
        strstr(buffer, "\r\n\r\n");

    // if we found a body, copy it over safely
    if (body_start) {

        // skip past the \r\n\r\n (4 chars) to get to the actual content
        body_start += 4;

        strncpy(req->body,
                body_start,
                sizeof(req->body) - 1);

        // make sure it's null-terminated so we don't read garbage memory later
        req->body[
            sizeof(req->body) - 1
        ] = '\0';

    } else {

        // no body found, just leave it empty
        req->body[0] = '\0';
    }
}