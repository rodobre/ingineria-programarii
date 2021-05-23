#include <mqtt/client.h>

void mqttExample()
{
    const std::string address = "localhost";
    const std::string clientId = "rgbLed";

    mqtt::client client(address, clientId);

    mqtt::connect_options options;
    options.set_keep_alive_interval(20);
    options.set_clean_session(true);

    try
    {
        client.connect(options);

        const std::string TOPIC = "LED";
        const std::string PAYLOAD = "{\"message\": \"asta e baaaaaaaaaaaaa\"}";
        auto msg = mqtt::make_message(TOPIC, PAYLOAD);

        client.publish(msg);

        client.disconnect();
    }
    catch (const mqtt::exception &exc)
    {
        std::cerr << exc.what() << " [" << exc.get_reason_code() << "]" << std::endl;
    }
}

int main(int argc, char *argv[])
{
    mqttExample();

    return 0;
}