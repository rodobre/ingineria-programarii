while true
do
 	response=$(curl --header "Content-Type: application/json" \
        			  --request POST \
         			  --data "{\"input_type\":\"WeatherInput\",\"input\":{\"temperature\":"$(( RANDOM % 40 ))"},\"input_settings\":\"{}\"}" \
         			  http://localhost:8080/iot)
    echo $response
    sleep 5
done