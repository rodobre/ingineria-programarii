/**
 * @file main.cpp
 * @brief Driver program for the project, exposes an HTTP server on port 8080 to handle API requests.
 */

#define INPUT_KEY "input"
#define INPUT_TYPE_KEY "input_type"
#define INPUT_SETTINGS_KEY "input_settings"

#define OUTPUT_ERROR_KEY "error"
#define OUTPUT_VALID_KEY "valid_request"
#define INVALID_REQUEST_BODY "invalid_request"
#define BAD_REQUEST_JSON "request format isn't correct"

#include <set>
#include <cstdio>
#include <string>
#include <stdexcept>
#include "device.hpp"
// #include "include/httplib/httplib.h"
// #include "include/nlohmann/json.hpp"

const std::set< std::string > InputType = { 
    "UserManualInput", 
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

    /* Create MQTT Subscriber */
    // TODO: Roberte sa moara mama ca nu merge sa dai detach la threadul de la mqttSubscriber asta :( )
    /* 
    MqttSubscriber mqttSubscriber;
    mqttSubscriber.StartProcessingInputs();
    */

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
         --data '{"input_type":"UserManualInput","input":{"r":1,"g":1,"b":1,"intensity":1},"input_settings":"{}"}' \
         http://localhost:8080/iot
         
    //MISSING: UserProgrammableInput

    curl --header "Content-Type: application/json" \
         --request POST \
         --data '{"input_type":"DisplayInput","input":[{"r":1,"g":1,"b":1,"intensity":1},{"r":2,"g":2,"b":2,"intensity":1},{"r":3,"g":3,"b":3,"intensity":1},{"r":4,"g":4,"b":4,"intensity":1}],"input_settings":"{}"}' \
         http://localhost:8080/iot

    curl --header "Content-Type: application/json" \
         --request POST \
         --data '{"input_type":"MusicInput","input":[{"frequency": 1},{"frequency": 1.25},{"frequency": 1.5},{"frequency": 2}],"input_settings":"{}"}' \
         http://localhost:8080/iot

    curl --header "Content-Type: application/json" \
         --request POST \
         --data '{"input_type":"WeatherInput","input":{"temperature":12.5},"input_settings":"{}"}' \
         http://localhost:8080/iot

    curl --header "Content-Type: application/json" \
         --request POST \
         --data '{"input_type":"BrightnessInput","input":[{"intensity": 1},{"intensity": 2},{"intensity": 3},{"intensity": 4}],"input_settings":"{}"}' \
         http://localhost:8080/iot

    curl --header "Content-Type: application/json" \
         --request POST \
         --data '{"input_type":"RandomInput","input":[],"input_settings":"{}"}' \
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

