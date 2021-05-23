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

    void Subscribe()
    {
        std::cout << "Started Subscribe" << std::endl;
        using json = nlohmann::json;

        const std::string address = "localhost";
        const std::string clientId = "ceprstsunt";

        mqtt::client client(address, clientId, mqtt::create_options(MQTTVERSION_5));

        mqtt::connect_options options;
        options.set_clean_session(false);
        options.set_automatic_reconnect(seconds(2), seconds(30));
        options.set_mqtt_version(MQTTVERSION_5);

        try
        {
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
                    std::cout << msg->to_string() << std::endl;
                    json requestJson = json::parse(msg->to_string());

                    if (requestJson.contains("message"))
                    {
                        std::cout << requestJson["message"] << std::endl;
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
        std::thread
        t2([](MqttSubscriber *ptr) -> void {
            ptr->Subscribe();
        },
           this);
        // Cu join merge dar blocheaza, cu detach iei mumu
        t2.detach();
        // t2.join();
    }
};
