#ifndef LITEHTTP_H
#define LITEHTTP_H

#define MAX_ROUTES 100

/**
 * @brief Represents an HTTP Request
 */
typedef struct {
    char method[16];   // e.g., "GET", "POST"
    char path[256];    // e.g., "/", "/users"
    char version[16];  // e.g., "HTTP/1.1"

    char body[2048];   // The request payload/body

} Request;

/**
 * @brief Represents an HTTP Response
 */
typedef struct {
    int client;        // The client socket file descriptor
} Response;

/**
 * @brief A function pointer type for route handlers.
 * 
 * Example:
 * void my_handler(Request *req, Response *res) {
 *     res_send(res, "Hello, World!");
 * }
 */
typedef void (*RouteHandler)(
    Request *,
    Response *
);

/**
 * @brief Internal representation of a route mapping
 */
typedef struct {
    char method[16];
    char path[256];
    RouteHandler handler;
} Route;

/**
 * @brief The main application context holding the server state and routes
 */
typedef struct {
    int port;
    int server_fd;

    Route routes[MAX_ROUTES];
    int route_count;

} App;

/* --- App Management --- */

/**
 * @brief Creates a new LiteHTTP App instance.
 * 
 * @param port The port number to listen on (e.g., 8080).
 * @return A pointer to the newly allocated App.
 */
App *app_create(int port);

/* --- Router --- */

/**
 * @brief Registers a GET route.
 * 
 * @param app The app instance.
 * @param path The URL path (e.g., "/").
 * @param handler The function to handle the request.
 */
void app_get(App *app, const char *path, RouteHandler handler);

/**
 * @brief Registers a POST route.
 * 
 * @param app The app instance.
 * @param path The URL path (e.g., "/login").
 * @param handler The function to handle the request.
 */
void app_post(App *app, const char *path, RouteHandler handler);

/* --- Request Parsing --- */

/**
 * @brief Parses an HTTP raw string buffer into a Request struct.
 * 
 * @param req The Request struct to populate.
 * @param buffer The raw HTTP request string.
 */
void parse_request(Request *req, const char *buffer);

/* --- Response Helpers --- */

/**
 * @brief Sends an HTML or plain text response.
 * 
 * @param res The Response struct.
 * @param body The content to send.
 */
void res_send(Response *res, const char *body);

/**
 * @brief Sends a JSON response with the correct Content-Type header.
 * 
 * @param res The Response struct.
 * @param json The JSON string to send.
 */
void res_json(Response *res, const char *json);

/* --- Server --- */

/**
 * @brief Starts the HTTP server loop. This function blocks indefinitely.
 * 
 * @param app The app instance to run.
 */
void app_listen(App *app);

#endif