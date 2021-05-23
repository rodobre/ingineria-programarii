---
title: mqtt_publisher.cpp


---

**mqtt_publisher.cpp File Reference**
## Functions

|                | Name           |
| -------------- | -------------- |
| void | **[mqttExample](files/mqtt__publisher_8cpp/#function-mqttexample)**() |
| int | **[main](files/mqtt__publisher_8cpp/#function-main)**(int argc, char * argv[]) |


## Functions Documentation

### function mqttExample

```cpp
void mqttExample()
```


### function main

```cpp
int main(
    int argc,
    char * argv[]
)
```




## Source code

```cpp
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
        const std::string PAYLOAD = "{\"stop\": 123}";
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
```


-------------------------------

Updated on 23 May 2021 at 21:54:47 UTC
