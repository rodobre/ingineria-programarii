# L.E.D




## Dependencies

Install apt packages with the versioning provided in `system_requirements.MD`

Install Mosquitto

```sh
sudo apt-add-repository ppa:mosquitto-dev/mosquitto-ppa
sudo apt update
sudo apt install mosquitto
```

Install Paho

```sh
sudo apt-get install build-essential gcc make cmake cmake-gui cmake-curses-gui
sudo apt-get install libssl-dev


git clone https://github.com/eclipse/paho.mqtt.c.git
cd paho.mqtt.c
git checkout v1.3.8
cmake -Bbuild -H. -DPAHO_ENABLE_TESTING=OFF -DPAHO_BUILD_STATIC=ON \
    -DPAHO_WITH_SSL=ON -DPAHO_HIGH_PERFORMANCE=ON
sudo cmake --build build/ --target install
sudo ldconfig


git clone https://github.com/eclipse/paho.mqtt.cpp
cd paho.mqtt.cpp
cmake -Bbuild -H. -DPAHO_BUILD_STATIC=ON \
    -DPAHO_BUILD_DOCUMENTATION=TRUE -DPAHO_BUILD_SAMPLES=TRUE
sudo cmake --build build/ --target install
sudo ldconfig
```

## MQTT Server

Run `mosquitto -v` in terminal

## MQTT Publisher

Build `mqtt_publisher.cpp` and run it to send a JSON message to MQTT Server

## Building

Build by executing build.sh on Linux (Debian/Ubuntu/CentOS RHEL), run `doxygen Doxyfile` to regenerate documentation

## Better visuals, better documentation

For better visuals, install `hugo` and run `./doxybook2 --input xml/ --output doxybook_output/documentation/content --config .doxybook/config.json --templates .doxybook/templates/`.
The, navigate to documentation using `cd doxybook_output/documentation` and run `hugo serve`.

## Running

Run `mosquitto -v` in terminal.
After building with build.sh, run /build/main. This will open HTTP (port 8080) and MQTT (port 1883, topic "LED") input buffers.
You can modify `mqtt_publisher.cpp` to publish different JSONs to the client, or use any other MQTT Client to publish messages to topic "LED".
You can send JSONs through CURL that match the regex in the documentation to change LED state.
