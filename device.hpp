#define REQUEST_BODY_KEY "message"
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

/**
 * @brief AppContext Templated Types
 */
using AppContextDeleter = std::function<void(AppContext*)>;
using AppContextPtr = std::unique_ptr<AppContext, AppContextDeleter>;

/**
 * @brief BaseInputContext Templated Types
 */
struct BaseInputContextDeleter {
    void operator()(BaseInputContext * ptr) {
        delete ptr;
    }
};

using BaseInputContextPtr = std::unique_ptr<BaseInputContext, BaseInputContextDeleter>; 

/**
 * @brief Singleton application context
 */
class AppContext
{
    /**
     * @brief Static singleton instance, internally managed and exposed via `getInstance`
     */
    static AppContextPtr instance;

    /**
     * @brief Priority queue used for storage of inputs with highest priority
     */
    // using BaseInputContextRef = std::reference_wrapper<BaseInputContext>;
    using BaseInputContextPtrVector = std::vector<BaseInputContextPtr>;
    std::stack
        <
        BaseInputContextPtr//,
        // BaseInputContextPtrVector,
        // std::function<bool(const BaseInputContextPtr&, const BaseInputContextPtr&)>
        > input_queue;
    
    /**
     * @brief Atomic bool to represent current status
     */
    std::atomic_bool context_active;

    /**
     * @brief Sleep interval in milliseconds for async task
     */
    unsigned int sleep_interval{16};

    /**
     * @brief JSON settings for multiple inputs
     * 
     */
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

    /**
     * @brief Custom constructor
     */
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

    /**
     * @brief Default destructor
     */
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

    /**
     * @brief Sends a request with metadata to a third party
     */
    static void publishToThirdParty(std::string message) 
    {
        nlohmann::json body;
        body[REQUEST_BODY_KEY] = message;
        
        std::cout << "Sending logs to third party..." << std::endl;
        httplib::Client cli("http://cpp-httplib-server.yhirose.repl.co");
        auto res = cli.Post("/post", body.dump(), "text/plain");
    }

    /**
     * @brief Enqueue an item in to the priority queue, comparison done via custom functor
     */
    void AddInput(BaseInputContextPtr&& input_ptr)
    {
        std::thread pushMetadataAdd(publishToThirdParty, NEW_INPUT);
        pushMetadataAdd.detach();

        input_queue.push(std::move(input_ptr));
    }

    /**
     * @brief Peek the top of the queue
     */
    const BaseInputContextPtr& TopQueue()
    {
        return input_queue.top();
    }

    /**
     * @brief Pop the input on top
     */
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

    /**
     * @brief Process input - pass execution context to input context with highest priority
     */
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

    /**
     * @brief Publish recently made changes to the controlled device
     * 
     * @param parameters Structure of application parameters
     * @param led_vector Array of LED vectors, internally managed by the input context
     */
    void PublishChangesToDevice(const AppParameters& parameters, const std::vector<LEDContext>& led_vector) noexcept
    {
        /**
         * @brief Dummy function, simulate publishing changes to device
         */
        return;
    }

    /**
     * @brief Start processing the inputs
     */
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

    /**
     * @brief Stop processing inputs
     */
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
