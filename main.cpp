/**
* @file main.cpp
* @brief Driver program for the project, exposes an HTTP server on port 8080 to handle API requests.
 */

#include <iostream>
#include "include/httplib/httplib.h"
#include "include/nlohmann/json.hpp"

/**
 * @brief Main driver function of the program, runs an HTTP server on port 8080 to process incoming requests (blocking!)
 * 
 * @return int - status code
 */
int main(void) {
  httplib::Server svr;

  svr.Get("/hi", [](const auto &, auto &res) {
    res.set_content("Hello World!", "text/plain");
  });

  std::cout << "start server..." << std::endl;
  svr.listen("0.0.0.0", 8080);
}