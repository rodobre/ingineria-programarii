---
title: AppContext
summary: Singleton application context.  

---

**AppContext Class Reference**


Singleton application context. 
`#include <device.hpp>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| AppContextPtr & | **[getInstance](classes/classappcontext/#function-getinstance)**() |
| void | **[publishToThirdParty](classes/classappcontext/#function-publishtothirdparty)**(std::string message)<br>Sends a request with metadata to a third party.  |
| void | **[AddInput](classes/classappcontext/#function-addinput)**(BaseInputContextPtr && input_ptr)<br>Enqueue an item in to the priority queue, comparison done via custom functor.  |
| const BaseInputContextPtr & | **[TopQueue](classes/classappcontext/#function-topqueue)**()<br>Peek the top of the queue.  |
| void | **[PopInput](classes/classappcontext/#function-popinput)**()<br>Pop the input on top.  |
| void | **[ProcessQueue](classes/classappcontext/#function-processqueue)**()<br>Process input - pass execution context to input context with highest priority.  |
| void | **[PublishChangesToDevice](classes/classappcontext/#function-publishchangestodevice)**(const [AppParameters](classes/structappparameters/) & parameters, const std::vector< [LEDContext](classes/classledcontext/) > & led_vector)<br>Publish recently made changes to the controlled device.  |
| void | **[StartProcessingInputs](classes/classappcontext/#function-startprocessinginputs)**()<br>Start processing the inputs.  |
| void | **[Stop](classes/classappcontext/#function-stop)**()<br>Stop processing inputs.  |

## Public Functions Documentation

### function getInstance

```cpp
static inline AppContextPtr & getInstance()
```


### function publishToThirdParty

```cpp
static inline void publishToThirdParty(
    std::string message
)
```

Sends a request with metadata to a third party. 

### function AddInput

```cpp
inline void AddInput(
    BaseInputContextPtr && input_ptr
)
```

Enqueue an item in to the priority queue, comparison done via custom functor. 

### function TopQueue

```cpp
inline const BaseInputContextPtr & TopQueue()
```

Peek the top of the queue. 

### function PopInput

```cpp
inline void PopInput()
```

Pop the input on top. 

### function ProcessQueue

```cpp
inline void ProcessQueue()
```

Process input - pass execution context to input context with highest priority. 

### function PublishChangesToDevice

```cpp
inline void PublishChangesToDevice(
    const AppParameters & parameters,
    const std::vector< LEDContext > & led_vector
)
```

Publish recently made changes to the controlled device. 

**Parameters**: 

  * **parameters** Structure of application parameters 
  * **led_vector** Array of LED vectors, internally managed by the input context 


Dummy function, simulate publishing changes to device


### function StartProcessingInputs

```cpp
inline void StartProcessingInputs()
```

Start processing the inputs. 

### function Stop

```cpp
inline void Stop()
```

Stop processing inputs. 

-------------------------------

Updated on 23 May 2021 at 21:54:47 UTC