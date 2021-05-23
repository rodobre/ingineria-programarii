---
title: BaseInputContext
summary: Base input context class for input processing.  

---

**BaseInputContext Class Reference**


Base input context class for input processing. 
`#include <inputcontext.hpp>`

Inherited by [BrightnessInputContext](classes/classbrightnessinputcontext/), [DisplayInputContext](classes/classdisplayinputcontext/), [MusicInputContext](classes/classmusicinputcontext/), [RandomInputContext](classes/classrandominputcontext/), [UserManualInputContext](classes/classusermanualinputcontext/), [WeatherInputContext](classes/classweatherinputcontext/)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[BaseInputContext](classes/classbaseinputcontext/#function-baseinputcontext)**() |
| | **[BaseInputContext](classes/classbaseinputcontext/#function-baseinputcontext)**([AppParameters](classes/structappparameters/) parameters, InputTypes input_type, bool active) |
| | **[BaseInputContext](classes/classbaseinputcontext/#function-baseinputcontext)**([AppParameters](classes/structappparameters/) parameters, std::vector< [LEDContext](classes/classledcontext/) > && led_vector, InputTypes input_type, bool active) |
| | **[BaseInputContext](classes/classbaseinputcontext/#function-baseinputcontext)**([BaseInputContext](classes/classbaseinputcontext/) & other) |
| | **[BaseInputContext](classes/classbaseinputcontext/#function-baseinputcontext)**([BaseInputContext](classes/classbaseinputcontext/) && other) |
| [BaseInputContext](classes/classbaseinputcontext/) & | **[operator=](classes/classbaseinputcontext/#function-operator=)**([BaseInputContext](classes/classbaseinputcontext/) & other) |
| [BaseInputContext](classes/classbaseinputcontext/) & | **[operator=](classes/classbaseinputcontext/#function-operator=)**([BaseInputContext](classes/classbaseinputcontext/) && other) |
| virtual | **[~BaseInputContext](classes/classbaseinputcontext/#function-~baseinputcontext)**() =default |
| virtual std::tuple< [AppParameters](classes/structappparameters/) &, std::vector< [LEDContext](classes/classledcontext/) > & > | **[Process](classes/classbaseinputcontext/#function-process)**() =0 |
| InputTypes | **[GetInputType](classes/classbaseinputcontext/#function-getinputtype)**() const<br>Getter for the input context type.  |
| std::vector< [LEDContext](classes/classledcontext/) > & | **[GetLedVector](classes/classbaseinputcontext/#function-getledvector)**()<br>Getter for the LED vector.  |
| [AppParameters](classes/structappparameters/) & | **[GetAppParameters](classes/classbaseinputcontext/#function-getappparameters)**()<br>Getter for the application parameters.  |
| bool | **[IsActive](classes/classbaseinputcontext/#function-isactive)**()<br>Getter for activity status.  |
| void | **[SetAppParameters](classes/classbaseinputcontext/#function-setappparameters)**(const [AppParameters](classes/structappparameters/) & other_parameters)<br>Setter for application parameters.  |
| void | **[SetActive](classes/classbaseinputcontext/#function-setactive)**(bool is_active)<br>Setter for activity.  |

## Protected Attributes

|                | Name           |
| -------------- | -------------- |
| [AppParameters](classes/structappparameters/) | **[parameters](classes/classbaseinputcontext/#variable-parameters)**  |
| std::vector< [LEDContext](classes/classledcontext/) > | **[led_vector](classes/classbaseinputcontext/#variable-led_vector)**  |
| InputTypes | **[input_type](classes/classbaseinputcontext/#variable-input_type)**  |
| bool | **[active](classes/classbaseinputcontext/#variable-active)**  |

## Public Functions Documentation

### function BaseInputContext

```cpp
inline BaseInputContext()
```


### function BaseInputContext

```cpp
inline BaseInputContext(
    AppParameters parameters,
    InputTypes input_type,
    bool active
)
```


### function BaseInputContext

```cpp
inline BaseInputContext(
    AppParameters parameters,
    std::vector< LEDContext > && led_vector,
    InputTypes input_type,
    bool active
)
```


### function BaseInputContext

```cpp
inline BaseInputContext(
    BaseInputContext & other
)
```


### function BaseInputContext

```cpp
inline BaseInputContext(
    BaseInputContext && other
)
```


### function operator=

```cpp
inline BaseInputContext & operator=(
    BaseInputContext & other
)
```


### function operator=

```cpp
inline BaseInputContext & operator=(
    BaseInputContext && other
)
```


### function ~BaseInputContext

```cpp
virtual ~BaseInputContext() =default
```


### function Process

```cpp
virtual std::tuple< AppParameters &, std::vector< LEDContext > & > Process() =0
```


**Reimplemented by**: [UserManualInputContext::Process](classes/classusermanualinputcontext/#function-process), [DisplayInputContext::Process](classes/classdisplayinputcontext/#function-process), [MusicInputContext::Process](classes/classmusicinputcontext/#function-process), [WeatherInputContext::Process](classes/classweatherinputcontext/#function-process), [BrightnessInputContext::Process](classes/classbrightnessinputcontext/#function-process), [RandomInputContext::Process](classes/classrandominputcontext/#function-process)


### function GetInputType

```cpp
inline InputTypes GetInputType() const
```

Getter for the input context type. 

### function GetLedVector

```cpp
inline std::vector< LEDContext > & GetLedVector()
```

Getter for the LED vector. 

### function GetAppParameters

```cpp
inline AppParameters & GetAppParameters()
```

Getter for the application parameters. 

### function IsActive

```cpp
inline bool IsActive()
```

Getter for activity status. 

### function SetAppParameters

```cpp
inline void SetAppParameters(
    const AppParameters & other_parameters
)
```

Setter for application parameters. 

### function SetActive

```cpp
inline void SetActive(
    bool is_active
)
```

Setter for activity. 

## Protected Attributes Documentation

### variable parameters

```cpp
AppParameters parameters;
```


### variable led_vector

```cpp
std::vector< LEDContext > led_vector;
```


### variable input_type

```cpp
InputTypes input_type;
```


### variable active

```cpp
bool active;
```


-------------------------------

Updated on 23 May 2021 at 21:54:47 UTC