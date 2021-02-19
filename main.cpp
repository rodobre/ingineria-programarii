/**
* @file main.cpp
* @brief This file is marvelous.
 */

#include <iostream>
#include "include/httplib/httplib.h"

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