#include <tuple>
#include <cstdio>
#include <memory>
#include <vector>
#include <utility>
#include <iostream>
#include <functional>
#include <stdlib.h>

/**
 * @brief RGB data structure
 */
struct RGB
{
    unsigned char r;
    unsigned char g;
    unsigned char b;

public:
    RGB()
        :
        r(0),
        g(0),
        b(0)
    {}

    RGB(unsigned char _r, unsigned char _g, unsigned char _b)
        :
        r(_r),
        g(_g),
        b(_b)
    {}

    RGB(const RGB& rgb)
        :
        r(rgb.r),
        g(rgb.g),
        b(rgb.b)
    {}

    unsigned char getRed() {
        return r;
    }

    unsigned char getGreen() {
        return g;
    }

    unsigned char getBlue() {
        return b;
    }
};

/**
 * @brief LED context class
 */
class LEDContext
{
    unsigned char intensity;
    RGB rgb;
    bool visible;

public:
    LEDContext()
        :
        intensity(100),
        rgb(255, 255, 255),
        visible(false)
    {
    }

    LEDContext(unsigned char intensity, RGB rgb, bool visible)
        :
        intensity(intensity),
        rgb(rgb),
        visible(visible)
    {
    }

    LEDContext(const LEDContext& led_context) 
        :
        intensity(led_context.intensity),
        rgb(led_context.rgb),
        visible(led_context.visible)
    {
    }

    RGB getRGB() {
        return rgb;
    }
};

/**
 * @brief Application Input Hierarchy Enum
 * 
 */
enum class InputTypes
{
    UserManualInput,
    DisplayInput,
    MusicInput,
    WeatherInput,
    BrightnessInput,
    RandomInput,
    UnassignedInput
};

/**
 * @brief Singleton application parameters
 */
struct AppParameters
{
    std::string DeviceName;

    AppParameters()
        :
        DeviceName("Default name")
    {
    }

    AppParameters(std::string DeviceName)
        :
        DeviceName(DeviceName)
    {
    }
};

/**
 * @brief Data used for parsing the UserManual input
 */
struct UserManualData
{
    LEDContext led;

    UserManualData(LEDContext led)
        :
        led(led)
    {

    }
};

/**
 * @brief Data used for parsing the Music input
 */
struct MusicData
{
    std::vector<double> frequencyVector;

    MusicData(std::vector<double>&& frequencyVector)
        :
        frequencyVector(std::move(frequencyVector))
    {

    }
};

/**
 * @brief Data used for parsing the Weather input
 */
struct WeatherData
{
    float temperature;

    WeatherData(float temperature)
        :
        temperature(temperature)
    {

    }
};

/**
 * @brief Data used for parsing the Brightness input
 */
struct BrightnessData
{
    std::vector<unsigned char> intensityVector;

    BrightnessData(std::vector<unsigned char>&& intensityVector)
        :
        intensityVector(std::move(intensityVector))
    {

    }
};

/**
 * @brief Base input context class for input processing
 */
class BaseInputContext
{
protected:
    AppParameters parameters;
    std::vector<LEDContext> led_vector;
    InputTypes input_type;
    bool active;

public:
    BaseInputContext()
        :
        parameters(),
        led_vector(),
        input_type(InputTypes::UnassignedInput),
        active(false)
    {
    }

    BaseInputContext(AppParameters parameters, InputTypes input_type, bool active)
        : 
        parameters(parameters),
        input_type(input_type),
        active(false)
    {
    }

    BaseInputContext(AppParameters parameters, std::vector<LEDContext>&& led_vector, InputTypes input_type, bool active)
        : 
        parameters(parameters),
        led_vector(std::move(led_vector)),
        input_type(input_type),
        active(false)
    {
    }

    BaseInputContext(BaseInputContext& other)
        :
        parameters(other.parameters),
        led_vector(std::exchange(led_vector, other.led_vector)),
        input_type(std::exchange(input_type, other.input_type)),
        active(std::exchange(active, other.active))
    {
    }

    BaseInputContext(BaseInputContext&& other)
        :
        parameters(std::move(other.parameters)),
        led_vector(std::move(other.led_vector)),
        input_type(std::move(other.input_type)),
        active(std::move(other.active))
    {
    }

    BaseInputContext& operator=(BaseInputContext& other)
    {
        parameters = other.parameters;
        led_vector = other.led_vector;
        input_type = other.input_type;
        active = other.active;
        return *this;
    }

    BaseInputContext& operator=(BaseInputContext&& other)
    {
        parameters = std::move(other.parameters);
        led_vector = std::move(other.led_vector);
        input_type = std::move(other.input_type);
        active = std::move(other.active);
        return *this;
    }

    virtual ~BaseInputContext() = default;
    virtual
        std::tuple<AppParameters&, std::vector<LEDContext>&>
        Process() = 0;
    
    /**
     * @brief Getter for the input context type
     */
    InputTypes GetInputType() const noexcept
    {
        return input_type;
    }

    /**
     * @brief Getter for the LED vector
     */
    std::vector<LEDContext>& GetLedVector() noexcept
    {
        return led_vector;
    }

    /**
     * @brief Getter for the application parameters
     */
    AppParameters& GetAppParameters() noexcept
    {
        return parameters;
    }

    /**
     * @brief Getter for activity status
     */
    bool IsActive() noexcept
    {
        return active;
    }

    /**
     * @brief Setter for application parameters
     */
    void SetAppParameters(const AppParameters& other_parameters) noexcept
    {
        parameters = other_parameters;
    }

    /**
     * @brief Setter for activity
     */
    void SetActive(bool is_active) noexcept
    {
        active = is_active;
    }
};

/**
 * @brief Input context class for manual user input
 */
class UserManualInputContext : public BaseInputContext
{
    UserManualData userManualData;
public:

    UserManualInputContext(AppParameters parameters, UserManualData userManualData, bool active)
        : 
        BaseInputContext(
            parameters,
            InputTypes::UserManualInput,
            active
        ),
        userManualData(userManualData)
    {
    }

    std::tuple<AppParameters&, std::vector<LEDContext>&>
    Process()
    {
        this->led_vector.push_back(
            userManualData.led
        );

        for (auto& led: led_vector) {
            std::cout << (int) led.getRGB().getRed()   << ' ' << 
                         (int) led.getRGB().getGreen() << ' ' <<
                         (int) led.getRGB().getBlue()  << std::endl;
        }

        return std::tie(parameters, led_vector);
    }
};


/**
 * @brief Input context class for display input
 */
class DisplayInputContext : public BaseInputContext
{
public:

    DisplayInputContext(AppParameters parameters, std::vector<LEDContext>&& led_vector, bool active)
        : 
        BaseInputContext(
            parameters,
            std::move(led_vector),
            InputTypes::DisplayInput,
            active
        )
    {
    }

    std::tuple<AppParameters&, std::vector<LEDContext>&>
    Process()
    {
        for (auto& led: led_vector) {
            std::cout << (int) led.getRGB().getRed()   << ' ' << 
                         (int) led.getRGB().getGreen() << ' ' <<
                         (int) led.getRGB().getBlue()  << std::endl;
        }
        return std::tie(parameters, led_vector);
    }
};


/**
 * @brief Input context class for music input
 */
class MusicInputContext : public BaseInputContext
{
    MusicData musicData;
public:

    MusicInputContext(AppParameters parameters, MusicData musicData, bool active)
        : 
        BaseInputContext(
            parameters,
            InputTypes::MusicInput,
            active
        ),
        musicData(musicData)
    {
    }

    std::tuple<AppParameters&, std::vector<LEDContext>&>
    Process()
    {
        for (auto& frequency: this->musicData.frequencyVector) {
            this->led_vector.push_back(
                LEDContext(
                    frequency, 
                    RGB(0, 255, 0), 
                    true
                )
            );
            std::cout << "frequency: " << frequency << std::endl;
        }

        for (auto& led: led_vector) {
            std::cout << (int) led.getRGB().getRed()   << ' ' << 
                         (int) led.getRGB().getGreen() << ' ' <<
                         (int) led.getRGB().getBlue()  << std::endl;
        }
        return std::tie(parameters, led_vector);
    }
};


/**
 * @brief Input context class for weather input
 */
class WeatherInputContext : public BaseInputContext
{

    WeatherData weatherData;

public:

    WeatherInputContext(AppParameters parameters, WeatherData weatherData, bool active)
        : 
        BaseInputContext(
            parameters,
            InputTypes::WeatherInput,
            active
        ),
        weatherData(weatherData)
    {
    }

    std::tuple<AppParameters&, std::vector<LEDContext>&>
    Process()
    {
        this->led_vector.push_back(
            LEDContext(
                1, 
                RGB(this->weatherData.temperature, 0, 1), 
                true
            )
        );

        std::cout << "temperature: " << this->weatherData.temperature << std::endl;
        return std::tie(parameters, led_vector);
    }
};


/**
 * @brief Input context class for brightness input
 */
class BrightnessInputContext : public BaseInputContext
{
    BrightnessData brightnessData;
public:

    BrightnessInputContext(AppParameters parameters, BrightnessData brightnessData, bool active)
        : 
        BaseInputContext(
            parameters,
            InputTypes::BrightnessInput,
            active
        ),
        brightnessData(brightnessData)
    {
    }

    std::tuple<AppParameters&, std::vector<LEDContext>&>
    Process()
    {
        for (auto& intensity: this->brightnessData.intensityVector) {
            this->led_vector.push_back(
                LEDContext(
                    (int) intensity, 
                    RGB(255, 255, 255), 
                    true
                )
            );
            std::cout << "intensity: " << (int) intensity << std::endl;
        }
        return std::tie(parameters, led_vector);
    }
};

/**
 * @brief Input context class for random input
 */
class RandomInputContext : public BaseInputContext
{
public:

    RandomInputContext(AppParameters parameters, bool active)
        : 
        BaseInputContext(
            parameters,
            InputTypes::RandomInput,
            active
        )
    {
    }

    std::tuple<AppParameters&, std::vector<LEDContext>&>
    Process()
    {
        this->led_vector.push_back(
            LEDContext(
                1, 
                RGB(rand() % 255, rand() % 255, rand() % 255), 
                true
            )
        );

        for (auto& led: led_vector) {
            std::cout << (int) led.getRGB().getRed()   << ' ' << 
                         (int) led.getRGB().getGreen() << ' ' <<
                         (int) led.getRGB().getBlue()  << std::endl;
        }
        return std::tie(parameters, led_vector);
    }
};

// using BaseInputContextDeleter = std::function<void(void*)>;
// using BaseInputContextPtr = std::unique_ptr<BaseInputContext, BaseInputContextDeleter>; 