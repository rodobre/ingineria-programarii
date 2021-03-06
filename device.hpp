#include <cstdio>
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include "include/nlohmann/json.hpp"
#include "inputcontext.hpp"

/**
 * @brief AppContext Templated Types
 */
class AppContext;

using AppContextDeleter = std::function<void(AppContext*)>;
using AppContextPtr = std::unique_ptr<AppContext, AppContextDeleter>;


/**
 * @brief Singleton application context
 */
class AppContext
{
    AppContext() = default;
    ~AppContext() = default;

    static AppContextPtr instance;

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
};

// * Static instantiation
AppContextPtr AppContext::instance = nullptr;