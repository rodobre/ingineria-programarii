#define INPUT_KEY "input"
#define INPUT_TYPE_KEY "input_type"
#define INPUT_SETTINGS_KEY "input_settings"

#include <fstream>
#include "include/nlohmann/json.hpp"

const std::set<std::string> InputType = {
    "UserManualInput",
    "DisplayInput",
    "MusicInput",
    "WeatherInput",
    "BrightnessInput",
    "RandomInput"
};

/**
 * @brief Opens a stream and parses the json from the parameter file
 */
nlohmann::json parseInputFromFile(std::string fileName) 
{
	std::ifstream inputJson("file.json");
	json result;
	inputJson >> requestJson;

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
}