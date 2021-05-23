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

## Building

Build by executing build.sh on Linux (Debian/Ubuntu/CentOS RHEL), run `doxygen Doxyfile` to regenerate documentation

## Better visuals, better documentation

For better visuals, install `hugo` and run `./doxybook2 --input xml/ --output doxybook_output/documentation/content --config .doxybook/config.json --templates .doxybook/templates/`.
The, navigate to documentation using `cd doxybook_output/documentation` and run `hugo serve`.
