---
title: mqtt_subscriber.hpp


---

**mqtt_subscriber.hpp File Reference**
## Namespaces

| Name           |
| -------------- |
| **[std::chrono](namespaces/namespacestd_1_1chrono/)**  |

## Classes

|                | Name           |
| -------------- | -------------- |
| class | **[MqttSubscriber](classes/classmqttsubscriber/)**  |

## Attributes

|                | Name           |
| -------------- | -------------- |
| const std::string | **[TOPIC](files/mqtt__subscriber_8hpp/#variable-topic)**  |



## Attributes Documentation

### variable TOPIC

```cpp
const std::string TOPIC = "LED";
```



## Source code

```cpp
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cctype>
#include <thread>
#include <chrono>
#include <vector>
#include <functional>
#include "mqtt/client.h"
#include "include/nlohmann/json.hpp"

using namespace std::chrono;

const std::string TOPIC = "LED";

class MqttSubscriber
{
public:
    MqttSubscriber()
    {
    }

    ~MqttSubscriber() = default;

    static void publishToThirdParty(std::string message)
    {
        const std::string address = "localhost";
        const std::string clientId = "smartLed";

        mqtt::client client(address, clientId);

        mqtt::connect_options options;
        options.set_keep_alive_interval(20);
        options.set_clean_session(true);

        try
        {
            client.connect(options);

            const std::string TOPIC = "outputStream";
            const std::string PAYLOAD = message;
            auto msg = mqtt::make_message(TOPIC, PAYLOAD);

            client.publish(msg);

            client.disconnect();
        }
        catch (const mqtt::exception &exc)
        {
            std::cerr << exc.what() << " [" << exc.get_reason_code() << "]" << std::endl;
        }
    }

    static void Subscribe(std::string message)
    {
        const std::set<std::string> InputType = {
            "UserManualInput",
            "DisplayInput",
            "MusicInput",
            "WeatherInput",
            "BrightnessInput",
            "RandomInput"};

        using json = nlohmann::json;

        std::cout << "Started Subscribe" << std::endl;

        const std::string address = "localhost";
        const std::string clientId = "subscriber";

        mqtt::client client(address, clientId, mqtt::create_options(MQTTVERSION_5));

        mqtt::connect_options options;
        options.set_clean_session(false);
        options.set_automatic_reconnect(seconds(2), seconds(30));
        options.set_mqtt_version(MQTTVERSION_5);

        try
        {
            auto &ctx = AppContext::getInstance();
            ctx->StartProcessingInputs();

            std::cout << "Connecting to the MQTT server..." << std::flush;
            client.connect(options);
            std::cout << "Connected!" << std::endl;

            std::cout << "Subscribing to topic: " << TOPIC << std::endl;
            client.subscribe(TOPIC);
            std::cout << "Subscribed to topic: " << TOPIC << std::endl;

            while (true)
            {
                auto msg = client.consume_message();

                if (msg)
                {
                    json requestJson = json::parse(msg->to_string());

                    if (requestJson.contains("stop"))
                    {
                        ctx->Stop();
                    }

                    if (requestJson.contains("start"))
                    {
                        ctx->StartProcessingInputs();
                    }

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
                            publishToThirdParty("A functionat");
                        }
                        else
                        {
                            throw std::runtime_error(INVALID_REQUEST_BODY);
                        }
                    }
                }
                else if (!client.is_connected())
                {
                    std::cout << "Lost connection" << std::endl;
                    while (!client.is_connected())
                    {
                        std::this_thread::sleep_for(milliseconds(250));
                    }
                    std::cout << "Re-established connection" << std::endl;
                }
            }

            std::cout << "Disconnecting from MQTT server..." << std::flush;
            client.disconnect();
            std::cout << "Disconnected from MQTT server" << std::endl;
        }
        catch (const mqtt::exception &exc)
        {
            std::cerr << exc.what() << " [" << exc.get_reason_code() << "]" << std::endl;
        }
    }

    void StartProcessingInputs()
    {
        std::thread processInput(Subscribe, "PROCESS_MQTT");
        processInput.detach();
    }
};
```


-------------------------------

Updated on 23 May 2021 at 21:54:47 UTC
