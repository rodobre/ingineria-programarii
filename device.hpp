#include <cstdio>
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include "include/nlohmann/json.hpp"

/**
 * @brief RGB data structure
 */
struct RGB
{
    unsigned char r;
    unsigned char g;
    unsigned char b;

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
    RandomInput
};

/**
 * @brief Singleton application parameters
 */
struct AppParameters
{
    std::string DeviceName;
};

/**
 * @brief AppContext Templated Types
 */
using AppContextDeleter = std::function<void(void*)>;
using AppContextPtr = std::unique_ptr<AppContext, AppContextDeleter>;


/**
 * @brief Singleton application context
 */
class AppContext
{
    static AppContextPtr instance;
    AppParameters parameters;
    std::vector<LEDContext> led_vector;

public:
    AppContext() = default;
    ~AppContext() = default;

    static std::unique_ptr<AppContext, AppContextDeleter>& getInstance()
    {
        if(!instance)
        {
            instance = AppContextPtr(
                new AppContext(),
                [] (void* inst)
                {
                    printf("Deleted managed pointer instance in AppContext");
                    if(inst != nullptr)
                    {
                        delete inst;
                    }
                }
            );
        }

        return instance;
    }

};

// * Static instantiation
AppContextPtr AppContext::instance = nullptr;