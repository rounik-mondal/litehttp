#include <stdio.h>
// include the litehttp framework header
#include "../include/litehttp.h"

// this is a basic route handler for a GET request. every route takes a pointer to the Request (what the client sent) and a pointer to the Response (what we will send back).
void home(Request *req, Response *res) {
  // we aren't using the request data for the home page, so we cast it to void to stop the compiler from complaining.
  (void)req;

  // res_send automatically wraps your string in proper HTTP headers and sends it as text/html.
  res_send(res, "<h1>Home Page</h1><p>Welcome to LiteHTTP!</p>");
}

// here's an example of an API endpoint returning JSON
void users(Request *req, Response *res) {
  (void)req;

  // res_json does the same as res_send, but sets the Content-Type to application/json so the browser/client parses it correctly.
  res_json(res, "{\"users\": 10, \"status\": \"active\"}");
}

// and here is how you handle a POST request with incoming data
void login(Request *req, Response *res) {
  // req->body contains whatever payload the client sent us. this is useful for forms, JSON payloads from fetch/axios, etc.
  printf("Received a POST request! BODY:\n%s\n", req->body);

  res_send(res, "<h1>Login Success</h1>");
}

int main() {
  // initialize the app and tell it which port to listen on.
  App *app = app_create(8080);

  // map our URL paths to the C functions we wrote above.

  // whenever someone visits http://localhost:8080/, call the home() function
  app_get(app, "/", home);

  // whenever someone visits http://localhost:8080/users, call the users()
  // function
  app_get(app, "/users", users);

  // map a POST request for handling form submissions or logins
  app_post(app, "/login", login);

  printf("Starting up! Try visiting http://localhost:8080 in your browser.\n");
  printf("You can also try: curl -X POST -d \"username=admin\" "
         "http://localhost:8080/login\n");

  // start the server loop. this will run forever, listening for connections!
  app_listen(app);

  // we should never actually reach here unless the server crashes
  return 0;
}