g++ -g -Wall -I/include main.cpp -lpthread -o build/main
doxygen Doxyfile
./doxybook2 --input xml/ --output doxybook_output/documentation/content --config .doxybook/config.json --templates .doxybook/templates/