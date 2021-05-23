/**
 * @file main.cpp
 * @brief Driver program for the project, exposes an HTTP server on port 8080 to handle API requests.
 */

#include <set>
#include <cstdio>
#include <string>
#include <stdexcept>
#include "device.hpp"
#include "include/httplib/httplib.h"
// #include "include/nlohmann/json.hpp"

// TODO: Create a separate file for enums, constants etc...
const std::string INPUT_KEY = "input";
const std::string INPUT_TYPE_KEY = "input_type";
const std::string INPUT_SETTINGS_KEY = "input_settings";

const std::string OUTPUT_ERROR_KEY = "error";
const std::string OUTPUT_VALID_KEY = "valid_request";
const std::string INVALID_REQUEST_BODY = "invalid_request"; 
const std::string BAD_REQUEST_JSON = "request format isn't correct";

const std::set< std::string > InputType = { 
    "UserManualInput", 
    "UserProgrammableInput", 
    "DisplayInput", 
    "MusicInput", 
    "WeatherInput", 
    "BrightnessInput", 
    "RandomInput"
};

/**
 * @brief Main driver function of the program, runs an HTTP 
 * server on port 8080 to process incoming requests (blocking!)
 * @return int - status code
 */
int main(void) {
    using namespace httplib;
    using json = nlohmann::json;
    
    Server svr;

    /* Application context instate */
    auto& ctx = AppContext::getInstance();
    ctx->StartProcessingInputs();

    /* Static folder handling */
    svr.set_mount_point("/static", "./static");

    /* Route to get reached by the IoT device */

    svr.Post("/start", [&](const Request& req, Response& res) {
        ctx->StartProcessingInputs();
    });

    svr.Post("/stop", [&](const Request& req, Response& res) {
        ctx->Stop();
    });

    svr.Post("/previous-setting", [&](const Request& req, Response& res) {
        ctx->PopInput();
    });

    svr.Post("/iot", [&](const Request& req, Response& res) {
        
        json response;
        json requestJson = json::parse(req.body);
        
        try {
            /* Validating all mandatory keys from the JSON */
            if (requestJson.contains(INPUT_KEY) &&
                requestJson.contains(INPUT_TYPE_KEY) &&
                requestJson.contains(INPUT_SETTINGS_KEY)) {
                
                /* Parsing the values from each key */
                const std::string requestType = requestJson[INPUT_TYPE_KEY];
                const json requestSettings = requestJson[INPUT_SETTINGS_KEY];
                
                if (InputType.find(requestType) != InputType.end()) {
                    // Pushing json to the context instance                    
                    ctx->AddInput(buildContext(requestJson[INPUT_KEY], requestType));

                    response[OUTPUT_VALID_KEY] = requestJson[INPUT_KEY];
                } else {
                    throw std::runtime_error(INVALID_REQUEST_BODY);
                }
            }
        } catch (std::runtime_error& error) {
            response[OUTPUT_ERROR_KEY] = BAD_REQUEST_JSON;
        } 
        
        /* Return response to user */
        res.set_content(response.dump(), "text/json");
    });

    svr.Get("/hi", [](const Request& req, Response& res) {
        res.set_content("Hello World!", "text/plain");
    });

    printf("Listening on port 8080...\n");
    svr.listen("0.0.0.0", 8080);
}

/*
Example request:
    Example /iot
    curl --header "Content-Type: application/json" \
         --request POST \
         --data '{"input_type":"MusicInput","input":[{"r":12,"g":34,"b":123,"intensity":1},{"r":43,"g":2,"b":123,"intensity":1},{"r":15,"g":14,"b":39,"intensity":1},{"r":96,"g":54,"b":90,"intensity":1}],"input_settings":"{}"}' \
         http://localhost:8080/iot

    curl --header "Content-Type: application/json" \
         --request POST \
         --data '{"input_type":"DisplayInput","input":[{"r":1,"g":1,"b":1,"intensity":1},{"r":2,"g":2,"b":2,"intensity":1},{"r":3,"g":3,"b":3,"intensity":1},{"r":4,"g":4,"b":4,"intensity":1}],"input_settings":"{}"}' \
         http://localhost:8080/iot

    curl --header "Content-Type: application/json" \
         --request POST \
         --data '{"input_type":"WeatherInput","input":{"temperature":12.5},"input_settings":"{}"}' \
         http://localhost:8080/iot

    Example /start
    curl --header "Content-Type: application/json" \
         --request POST \
         --data '{}' \
         http://localhost:8080/start

    Example /stop
    curl --header "Content-Type: application/json" \
         --request POST \
         --data '{}' \
         http://localhost:8080/stop

    Example /previous-setting
    curl --header "Content-Type: application/json" \
         --request POST \
         --data '{}' \
         http://localhost:8080/previous-setting

*/