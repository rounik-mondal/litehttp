# LiteHTTP

A simple, lightweight, and easy-to-use HTTP framework written in C.

`litehttp` is designed to provide a minimalistic Express-like API for building web servers in C. It allows you to easily define routes and handle HTTP GET and POST requests.

## Features

- **Simple Routing**: Easily map URLs to C functions.
- **JSON & HTML Responses**: Built-in helper functions to send JSON or HTML.
- **Lightweight**: Zero external dependencies—relies only on standard C libraries.
- **Static Library**: Can be compiled into a static library (`liblitehttp.a`) to easily link with your own projects.

## Installation & Build

To compile the framework into a static library and build the example application:

```bash
git clone https://github.com/yourusername/litehttp.git
cd litehttp
make
```

This will produce two files:
1. `liblitehttp.a` - The static library you can link to your own programs.
2. `example_app` - A compiled binary of the example application.

Run the example application to see it in action:
```bash
./example_app
```

## Quick Start Example

Here is a simple example of how to create a web server using `litehttp`.

```c
#include <stdio.h>
#include "litehttp.h"

void home(Request *req, Response *res) {
    res_send(res, "<h1>Home Page</h1>");
}

void users(Request *req, Response *res) {
    res_json(res, "{\"users\": 10}");
}

void login(Request *req, Response *res) {
    printf("Received Body: %s\n", req->body);
    res_send(res, "<h1>Login Success</h1>");
}

int main() {
    // 1. Create the App listening on port 8080
    App *app = app_create(8080);

    // 2. Define GET routes
    app_get(app, "/", home);
    app_get(app, "/users", users);

    // 3. Define POST routes
    app_post(app, "/login", login);

    // 4. Start the server
    printf("Server running on http://localhost:8080\n");
    app_listen(app);

    return 0;
}
```

### Compiling Your Own Project

Assuming your C code is in `main.c` and you have `liblitehttp.a` and `include/litehttp.h`:

```bash
gcc -Wall -Wextra main.c -I./include -L. -llitehttp -o my_server
./my_server
```

## API Reference

### `App` Management

- `App *app_create(int port)`: Initializes the application to listen on the specified port.
- `void app_listen(App *app)`: Starts the server. This function blocks indefinitely.

### Routing

- `void app_get(App *app, const char *path, RouteHandler handler)`: Registers a GET route.
- `void app_post(App *app, const char *path, RouteHandler handler)`: Registers a POST route.

### Request & Response

- `void res_send(Response *res, const char *body)`: Sends a basic HTTP response (e.g. text/html).
- `void res_json(Response *res, const char *json)`: Sends a JSON HTTP response with `Content-Type: application/json`.

## License

This project is licensed under the MIT License - see the LICENSE file for details.
