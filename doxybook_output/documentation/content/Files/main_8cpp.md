---
title: main.cpp
summary: Driver program for the project, exposes an HTTP server on port 8080 to handle API requests.  

---

**main.cpp File Reference**
Driver program for the project, exposes an HTTP server on port 8080 to handle API requests. ## Functions

|                | Name           |
| -------------- | -------------- |
| int | **[main](files/main_8cpp/#function-main)**(void )<br>Main driver function of the program, runs an HTTP server on port 8080 to process incoming requests (blocking!)  |

## Attributes

|                | Name           |
| -------------- | -------------- |
| const std::set< std::string > | **[InputType](files/main_8cpp/#variable-inputtype)**  |

## Defines

|                | Name           |
| -------------- | -------------- |
|  | **[INPUT_KEY](files/main_8cpp/#define-input_key)**  |
|  | **[INPUT_TYPE_KEY](files/main_8cpp/#define-input_type_key)**  |
|  | **[INPUT_SETTINGS_KEY](files/main_8cpp/#define-input_settings_key)**  |
|  | **[OUTPUT_ERROR_KEY](files/main_8cpp/#define-output_error_key)**  |
|  | **[OUTPUT_VALID_KEY](files/main_8cpp/#define-output_valid_key)**  |
|  | **[INVALID_REQUEST_BODY](files/main_8cpp/#define-invalid_request_body)**  |
|  | **[BAD_REQUEST_JSON](files/main_8cpp/#define-bad_request_json)**  |


## Functions Documentation

### function main

```cpp
int main(
    void 
)
```

Main driver function of the program, runs an HTTP server on port 8080 to process incoming requests (blocking!) 

**Return**: int - status code 


## Attributes Documentation

### variable InputType

```cpp
const std::set< std::string > InputType = {
    "UserManualInput",
    "DisplayInput",
    "MusicInput",
    "WeatherInput",
    "BrightnessInput",
    "RandomInput"};
```



## Macro Documentation

### define INPUT_KEY

```cpp
#define INPUT_KEY "input"
```


### define INPUT_TYPE_KEY

```cpp
#define INPUT_TYPE_KEY "input_type"
```


### define INPUT_SETTINGS_KEY

```cpp
#define INPUT_SETTINGS_KEY "input_settings"
```


### define OUTPUT_ERROR_KEY

```cpp
#define OUTPUT_ERROR_KEY "error"
```


### define OUTPUT_VALID_KEY

```cpp
#define OUTPUT_VALID_KEY "valid_request"
```


### define INVALID_REQUEST_BODY

```cpp
#define INVALID_REQUEST_BODY "invalid_request"
```


### define BAD_REQUEST_JSON

```cpp
#define BAD_REQUEST_JSON "request format isn't correct"
```


## Source code

```cpp

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
#include "mqtt_subscriber.hpp"

const std::set<std::string> InputType = {
    "UserManualInput",
    "DisplayInput",
    "MusicInput",
    "WeatherInput",
    "BrightnessInput",
    "RandomInput"};

int main(void)
{
    using namespace httplib;
    using json = nlohmann::json;

    Server svr;

    /* Application context instate */
    auto &ctx = AppContext::getInstance();
    ctx->StartProcessingInputs();

    /* Create MQTT Subscriber */
    MqttSubscriber mqttSubscriber;
    mqttSubscriber.StartProcessingInputs();

    /* Static folder handling */
    svr.set_mount_point("/static", "./static");

    /* Route to get reached by the IoT device */

    svr.Post("/start", [&](const Request &req, Response &res) {
        ctx->StartProcessingInputs();
    });

    svr.Post("/stop", [&](const Request &req, Response &res) {
        ctx->Stop();
    });

    svr.Post("/previous-setting", [&](const Request &req, Response &res) {
        ctx->PopInput();
    });

    svr.Post("/iot", [&](const Request &req, Response &res) {
        json response;
        json requestJson = json::parse(req.body);

        try
        {
            /* Validating all mandatory keys from the JSON */
            if (requestJson.contains(INPUT_KEY) &&
                requestJson.contains(INPUT_TYPE_KEY) &&
                requestJson.contains(INPUT_SETTINGS_KEY))
            {

                /* Parsing the values from each key */
                const std::string requestType = requestJson[INPUT_TYPE_KEY];
                const json requestSettings = requestJson[INPUT_SETTINGS_KEY];

                if (InputType.find(requestType) != InputType.end())
                {
                    // Pushing json to the context instance
                    ctx->AddInput(buildContext(requestJson[INPUT_KEY], requestType));

                    response[OUTPUT_VALID_KEY] = requestJson[INPUT_KEY];
                }
                else
                {
                    throw std::runtime_error(INVALID_REQUEST_BODY);
                }
            }
        }
        catch (std::runtime_error &error)
        {
            response[OUTPUT_ERROR_KEY] = BAD_REQUEST_JSON;
        }

        /* Return response to user */
        res.set_content(response.dump(), "text/json");
    });

    svr.Get("/hi", [](const Request &req, Response &res) {
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
    Pentru MQTT daca trimiti in JSON cheia "start", atunci o sa dea start
    curl --header "Content-Type: application/json" \
         --request POST \
         --data '{}' \
         http://localhost:8080/start

    Example /stop
    Pentru MQTT daca trimiti in JSON cheia "stop", atunci o sa dea stop
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
```


-------------------------------

Updated on 23 May 2021 at 21:54:47 UTC
