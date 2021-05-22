#include <cstdio>
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <queue>
#include <atomic>
#include <thread>
#include <future>
#include "include/nlohmann/json.hpp"
#include "inputcontext.hpp"

class AppContext;

/**
 * @brief AppContext Templated Types
 */
using AppContextDeleter = std::function<void(AppContext*)>;
using AppContextPtr = std::unique_ptr<AppContext, AppContextDeleter>;


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
    using BaseInputContextRef = std::reference_wrapper<BaseInputContext>;
    using BaseInputContextRefVector = std::vector<BaseInputContextRef>;
    std::priority_queue
        <
        BaseInputContextRef,
        BaseInputContextRefVector,
        std::function<bool(const BaseInputContext&, const BaseInputContext&)>
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
        input_queue
        (
            [] (const BaseInputContext& a, const BaseInputContext& b) -> bool
            {
                return a.GetInputType() < b.GetInputType();
            }
        ),
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
     * @brief Enqueue an item in to the priority queue, comparison done via custom functor
     */
    void AddInput(BaseInputContext&& input_ptr)
    {
        input_queue.push(input_ptr);
    }

    /**
     * @brief Peek the top of the queue
     */
    BaseInputContext& TopQueue()
    {
        return input_queue.top();
    }

    /**
     * @brief Pop the input on top
     */
    void PopInput()
    {
        input_queue.pop();
    }

    /**
     * @brief Process input - pass execution context to input context with highest priority
     */
    void ProcessQueue()
    {
        if(this->input_queue.empty())
        {
            // std::cout << "dam return" << std::endl;
            return;
        }
        // std::cout << "NU dam return" << std::endl;
        auto& input_processor = this->TopQueue();

        auto [parameters, led_vector] = input_processor.Process();
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
        std::thread t1([] (AppContext * ptr) -> void
        {
            while(ptr->context_active.load())
            {
                ptr->ProcessQueue();
                std::this_thread::sleep_for(std::chrono::milliseconds(ptr->sleep_interval));
            }
        }, this);
        t1.detach();
        // std::async(std::launch::async, [this] () -> void
        // {
        //     while(this->context_active.load())
        //     {
        //         this->ProcessQueue();
        //         std::this_thread::sleep_for(std::chrono::milliseconds(this->sleep_interval));
        //     }
        // });
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