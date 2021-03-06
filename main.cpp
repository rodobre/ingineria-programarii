/**
* @file main.cpp
* @brief Driver program for the project, exposes an HTTP server on port 8080 to handle API requests.
 */

#include <cstdio>
#include <string>
#include "device.hpp"
#include "include/httplib/httplib.h"
#include "include/nlohmann/json.hpp"

// TODO: Create a separate file for enums, constants etc...
const std::string BAD_REQUEST_JSON = "{error:request format isn't correct}";

/**
 * @brief Main driver function of the program, runs an HTTP server on port 8080 to process incoming requests (blocking!)
 * 
 * @return int - status code
 */
int main(void) {
    using namespace httplib;
    using json = nlohmann::json;
    
    Server svr;

    /* Application context instate */
    auto& ctx = AppContext::getInstance();
    /* Static folder handling */
    auto ret = svr.set_mount_point("/static", "./static");
    
    svr.Post("/iot", [&](const Request& req, Response& res) {
        json requestJson = json::parse(req.body);
        
        try {
            json response;
            std::vector<int> values;

            /* Parsing each value*/
            for (auto value : requestJson["input"]) {
                values.push_back(value);
            }
            response["result"] = values;

            /* Currently returing the 
            values back to the requester*/
            res.set_content(response.dump(), "text/json");
            
        } catch (std::exception& error) {
            res.set_content(BAD_REQUEST_JSON, "text/json");
        }
    });

    svr.Get("/hi", [](const Request& req, Response& res) {
        res.set_content("Hello World!", "text/plain");
    });

    printf("start server...\n");
    svr.listen("0.0.0.0", 8080);
}


/*
Example request:
    curl --header "Content-Type: application/json" \
         --request POST \
         --data '{"input_type":"music","input":"[12, 43, 1, 43, 54]"}' \
         http://localhost:8080/iot
*/