g++ -g -Wall -I/include -std=c++17 main.cpp -lpthread -lpaho-mqtt3a -lpaho-mqttpp3 -o build/main
doxygen Doxyfile
./doxybook2 --input xml/ --output doxybook_output/documentation/content --config .doxybook/config.json --templates .doxybook/templates/
