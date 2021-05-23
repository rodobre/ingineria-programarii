---
title: device.hpp


---

**device.hpp File Reference**
## Classes

|                | Name           |
| -------------- | -------------- |
| struct | **[BaseInputContextDeleter](classes/structbaseinputcontextdeleter/)** <br>[BaseInputContext](classes/classbaseinputcontext/) Templated Types.  |
| class | **[AppContext](classes/classappcontext/)** <br>Singleton application context.  |

## Types

|                | Name           |
| -------------- | -------------- |
| using std::function< void([AppContext](classes/classappcontext/) *)> | **[AppContextDeleter](files/device_8hpp/#using-appcontextdeleter)** <br>[AppContext](classes/classappcontext/) Templated Types.  |
| using std::unique_ptr< [AppContext](classes/classappcontext/), AppContextDeleter > | **[AppContextPtr](files/device_8hpp/#using-appcontextptr)**  |
| using std::unique_ptr< [BaseInputContext](classes/classbaseinputcontext/), [BaseInputContextDeleter](classes/structbaseinputcontextdeleter/) > | **[BaseInputContextPtr](files/device_8hpp/#using-baseinputcontextptr)**  |

## Functions

|                | Name           |
| -------------- | -------------- |
| BaseInputContextPtr | **[buildContext](files/device_8hpp/#function-buildcontext)**(nlohmann::json requestJson, std::string requestType) |

## Defines

|                | Name           |
| -------------- | -------------- |
|  | **[NEW_INPUT](files/device_8hpp/#define-new_input)**  |
|  | **[POP_INPUT](files/device_8hpp/#define-pop_input)**  |

## Types Documentation

### using AppContextDeleter

```cpp
using AppContextDeleter =  std::function<void(AppContext*)>;
```

[AppContext](classes/classappcontext/) Templated Types. 

### using AppContextPtr

```cpp
using AppContextPtr =  std::unique_ptr<AppContext, AppContextDeleter>;
```


### using BaseInputContextPtr

```cpp
using BaseInputContextPtr =  std::unique_ptr<BaseInputContext, BaseInputContextDeleter>;
```



## Functions Documentation

### function buildContext

```cpp
BaseInputContextPtr buildContext(
    nlohmann::json requestJson,
    std::string requestType
)
```




## Macro Documentation

### define NEW_INPUT

```cpp
#define NEW_INPUT "new_input_added"
```


### define POP_INPUT

```cpp
#define POP_INPUT "top_input_popped"
```


## Source code

```cpp
#define NEW_INPUT "new_input_added"
#define POP_INPUT "top_input_popped"

#include <cstdio>
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <queue>
#include <stack>
#include <atomic>
#include <thread>
#include <future>
#include "inputcontext.hpp"
#include "include/nlohmann/json.hpp"
#include "include/httplib/httplib.h"

class AppContext;

using AppContextDeleter = std::function<void(AppContext*)>;
using AppContextPtr = std::unique_ptr<AppContext, AppContextDeleter>;

struct BaseInputContextDeleter {
    void operator()(BaseInputContext * ptr) {
        delete ptr;
    }
};

using BaseInputContextPtr = std::unique_ptr<BaseInputContext, BaseInputContextDeleter>; 

class AppContext
{
    static AppContextPtr instance;

    // using BaseInputContextRef = std::reference_wrapper<BaseInputContext>;
    using BaseInputContextPtrVector = std::vector<BaseInputContextPtr>;
    std::stack
        <
        BaseInputContextPtr//,
        // BaseInputContextPtrVector,
        // std::function<bool(const BaseInputContextPtr&, const BaseInputContextPtr&)>
        > input_queue;
    
    std::atomic_bool context_active;

    unsigned int sleep_interval{16};

    nlohmann::json settings
    {
        {"UserManualInput", {}},
        {"UserProgrammableInput", {}},
        {"DisplayInput", {}},
        {"MusicInput", {}},
        {"WeatherInput", {}},
        {"BrightnessInput", {}},
        {"RandomInput", {}}
    };

    AppContext()
        :
        // input_queue
        // (
        //     [] (const BaseInputContextPtr& a, const BaseInputContextPtr& b) -> bool
        //     {
        //         return a->GetInputType() < b->GetInputType();
        //     }
        // ),
        context_active(false)
    {}

    ~AppContext() = default;

public:
    
    static AppContextPtr& getInstance()
    {
        if(!instance)
        {
            instance = AppContextPtr(
                new AppContext(),
                [] (AppContext* inst) -> void
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

    static void publishToThirdParty(std::string message) 
    {
        std::cout << "getting to publish changes" << std::endl;
        httplib::Client cli("http://cpp-httplib-server.yhirose.repl.co");
        auto res = cli.Post("/post", message, "text/plain");
        std::cout << "after publishing changes" << std::endl;
    }

    void AddInput(BaseInputContextPtr&& input_ptr)
    {
        std::thread pushMetadataAdd(publishToThirdParty, NEW_INPUT);
        pushMetadataAdd.detach();

        input_queue.push(std::move(input_ptr));
    }

    const BaseInputContextPtr& TopQueue()
    {
        return input_queue.top();
    }

    void PopInput()
    {
        if (this->input_queue.empty()) 
        {
            return;
        }

        std::thread pushMetadataPop(publishToThirdParty, POP_INPUT);
        pushMetadataPop.detach();
        input_queue.pop();
    }

    void ProcessQueue()
    {
        if(this->input_queue.empty())
        {
            return;
        }

        const auto& input_processor = this->TopQueue();

        auto [parameters, led_vector] = input_processor->Process();

        this->PublishChangesToDevice(parameters, led_vector);
    }

    void PublishChangesToDevice(const AppParameters& parameters, const std::vector<LEDContext>& led_vector) noexcept
    {
        return;
    }

    void StartProcessingInputs()
    {
        context_active.store(true);
        std::thread input_lookup_t([] (AppContext * ptr) -> void
        {
            while(ptr->context_active.load())
            {
                ptr->ProcessQueue();
                std::this_thread::sleep_for(std::chrono::milliseconds(ptr->sleep_interval));
            }
        }, this);
        input_lookup_t.detach();
    }

    void Stop()
    {
        context_active.store(false);
    }
};

// Static instantiation
AppContextPtr AppContext::instance = nullptr;

BaseInputContextPtr buildContext(nlohmann::json requestJson, std::string requestType) {
    
    AppParameters parameters("testing device name");
    std::vector<LEDContext> tmpLedValues;
    
    BaseInputContext * tmp = nullptr;

    // No possible invalid type because of previous filtering....
    if (requestType == "UserManualInput") {
        /*
            { color: LEDContext (not array) }
        */
        nlohmann::json& led = requestJson;        
        tmp = dynamic_cast<BaseInputContext*>(
            new UserManualInputContext(
                parameters, 
                UserManualData(
                    LEDContext(
                        led["intensity"], 
                        RGB(led["r"], led["g"], led["b"]), 
                        true
                    )
                ), 
                true
            )
        );
    }
    else if(requestType == "DisplayInput") {
        /*
            { rgb: RGB }
        */
        for (nlohmann::json& led: requestJson) {
            tmpLedValues.push_back(
                LEDContext(
                    led["intensity"], 
                    RGB(led["r"], led["g"], led["b"]), 
                    true
                )
            );
        }
        tmp = dynamic_cast<BaseInputContext*>(
            new DisplayInputContext(
                parameters, std::move(tmpLedValues), true
            )
        );
    }
    else if(requestType == "MusicInput") {
        /*
            { frequency: double }
        */
        std::vector<double> frequencyVector;

        for (nlohmann::json& data: requestJson) {
            frequencyVector.push_back(
                (double) data["frequency"]
            );
        }

        tmp = dynamic_cast<BaseInputContext*>(
            new MusicInputContext(
                parameters, 
                MusicData(std::move(frequencyVector)), 
                true
            )
        );
    }
    else if(requestType == "WeatherInput") {
        /*
            { temperature: float }
        */
        float temperature = requestJson["temperature"];
        tmp = dynamic_cast<BaseInputContext*>(
            new WeatherInputContext(
                parameters, 
                WeatherData(temperature), 
                true
            )
        );
    }
    else if(requestType == "BrightnessInput") {
        /*
            { intensity: unsigned char }
        */
        std::vector<unsigned char> intensityVector;

        for (nlohmann::json& data: requestJson) {
            intensityVector.push_back(
                (unsigned char) data["intensity"]
            );
        }

        tmp = dynamic_cast<BaseInputContext*>(
            new BrightnessInputContext(
                parameters, 
                BrightnessData(std::move(intensityVector)), 
                true
            )
        );
    }
    else if(requestType == "RandomInput") {
        /*
            empty
        */
        tmp = dynamic_cast<BaseInputContext*>(
            new RandomInputContext(
                parameters, true
            )
        );
    }
    
    BaseInputContextPtr smartPtr(tmp);
    return smartPtr;
}
```


-------------------------------

Updated on 23 May 2021 at 21:54:47 UTC
