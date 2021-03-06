/**
* @file main.cpp
* @brief Driver program for the project, exposes an HTTP server on port 8080 to handle API requests.
 */

#include <cstdio>
#include <string>
#include "include/httplib/httplib.h"
#include "include/nlohmann/json.hpp"

/**
 * @brief Main driver function of the program, runs an HTTP server on port 8080 to process incoming requests (blocking!)
 * 
 * @return int - status code
 */
int main(void) {
  using namespace httplib;

  Server svr;
  auto ret = svr.set_mount_point("/static", "./static");

  svr.Get("/hi", [](const Request& req, Response& res) {
    res.set_content("Hello World!", "text/plain");
  });

  printf("start server...\n");
  svr.listen("0.0.0.0", 8080);
}