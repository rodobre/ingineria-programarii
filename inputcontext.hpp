#include <cstdio>
#include <memory>
#include <functional>
#include <vector>
#include <utility>
#include <tuple>

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

    LEDContext(const LEDContext& led_context) :
        intensity(led_context.intensity),
        rgb(led_context.rgb),
        visible(led_context.visible)
    {
    }
};

/**
 * @brief Application Input Hierarchy Enum
 * 
 */
enum class InputTypes
{
    UserManualInput,
    UserProgrammableInput,
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
};

/**
 * @brief Base input context class for input processing
 */
class BaseInputContext
{
    AppParameters parameters;
    std::vector<LEDContext> led_vector;
    InputTypes input_type;

public:
    BaseInputContext() = default;
    BaseInputContext(BaseInputContext& other)
        :
        parameters(other.parameters),
        led_vector(std::exchange(led_vector, other.led_vector)),
        input_type(std::exchange(input_type, other.input_type))
    {
    }

    BaseInputContext(BaseInputContext&& other)
        :
        parameters(std::move(other.parameters)),
        led_vector(std::move(other.led_vector)),
        input_type(std::move(other.input_type))
    {
    }

    BaseInputContext& operator=(BaseInputContext& other)
    {
        parameters = other.parameters;
        led_vector = other.led_vector;
        input_type = other.input_type;
        return *this;
    }

    BaseInputContext& operator=(BaseInputContext&& other)
    {
        parameters = std::move(other.parameters);
        led_vector = std::move(other.led_vector);
        input_type = std::move(other.input_type);
        return *this;
    }

    virtual ~BaseInputContext() = default;
    virtual
        std::tuple<AppParameters&, std::vector<LEDContext>&>
        Process(AppParameters& parameters, std::vector<LEDContext>& led_vector) = 0;
};

/**
 * @brief Input context class for manual user input
 */
class UserManualInputContext : public BaseInputContext
{
    std::tuple<AppParameters&, std::vector<LEDContext>&>
    Process(AppParameters& parameters, std::vector<LEDContext>& led_vector)
    {
        return std::tie(parameters, led_vector);
    }
};


/**
 * @brief Input context class for programmable user input
 */
class UserProgrammableInputContext : public BaseInputContext
{
    std::tuple<AppParameters&, std::vector<LEDContext>&>
    Process(AppParameters& parameters, std::vector<LEDContext>& led_vector)
    {
        return std::tie(parameters, led_vector);
    }
};


/**
 * @brief Input context class for display input
 */
class DisplayInputContext : public BaseInputContext
{
    std::tuple<AppParameters&, std::vector<LEDContext>&>
    Process(AppParameters& parameters, std::vector<LEDContext>& led_vector)
    {
        return std::tie(parameters, led_vector);
    }
};


/**
 * @brief Input context class for music input
 */
class MusicInputContext : public BaseInputContext
{
    std::tuple<AppParameters&, std::vector<LEDContext>&>
    Process(AppParameters& parameters, std::vector<LEDContext>& led_vector)
    {
        return std::tie(parameters, led_vector);
    }
};


/**
 * @brief Input context class for brightness input
 */
class BrightnessInputContext : public BaseInputContext
{
    std::tuple<AppParameters&, std::vector<LEDContext>&>
    Process(AppParameters& parameters, std::vector<LEDContext>& led_vector)
    {
        return std::tie(parameters, led_vector);
    }
};

/**
 * @brief Input context class for random input
 */
class RandomInputContext : public BaseInputContext
{
    std::tuple<AppParameters&, std::vector<LEDContext>&>
    Process(AppParameters& parameters, std::vector<LEDContext>& led_vector)
    {
        return std::tie(parameters, led_vector);
    }
};