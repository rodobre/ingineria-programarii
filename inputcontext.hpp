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
    std::tuple<AppParameters&, std::vector<LEDContext>&>
    Process()
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
    Process()
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
    Process()
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
    Process()
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
    Process()
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
    Process()
    {
        return std::tie(parameters, led_vector);
    }
};

using BaseInputContextDeleter = std::function<void(void*)>;
using BaseInputContextPtr = std::unique_ptr<BaseInputContext, BaseInputContextDeleter>; 