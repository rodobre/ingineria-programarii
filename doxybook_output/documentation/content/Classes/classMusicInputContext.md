---
title: MusicInputContext
summary: Input context class for music input.  

---

**MusicInputContext Class Reference**


Input context class for music input. 
`#include <inputcontext.hpp>`

Inherits from [BaseInputContext](classes/classbaseinputcontext/)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[MusicInputContext](classes/classmusicinputcontext/#function-musicinputcontext)**([AppParameters](classes/structappparameters/) parameters, [MusicData](classes/structmusicdata/) musicData, bool active) |
| virtual std::tuple< [AppParameters](classes/structappparameters/) &, std::vector< [LEDContext](classes/classledcontext/) > & > | **[Process](classes/classmusicinputcontext/#function-process)**() |

## Additional inherited members

**Public Functions inherited from [BaseInputContext](classes/classbaseinputcontext/)**

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
| InputTypes | **[GetInputType](classes/classbaseinputcontext/#function-getinputtype)**() const<br>Getter for the input context type.  |
| std::vector< [LEDContext](classes/classledcontext/) > & | **[GetLedVector](classes/classbaseinputcontext/#function-getledvector)**()<br>Getter for the LED vector.  |
| [AppParameters](classes/structappparameters/) & | **[GetAppParameters](classes/classbaseinputcontext/#function-getappparameters)**()<br>Getter for the application parameters.  |
| bool | **[IsActive](classes/classbaseinputcontext/#function-isactive)**()<br>Getter for activity status.  |
| void | **[SetAppParameters](classes/classbaseinputcontext/#function-setappparameters)**(const [AppParameters](classes/structappparameters/) & other_parameters)<br>Setter for application parameters.  |
| void | **[SetActive](classes/classbaseinputcontext/#function-setactive)**(bool is_active)<br>Setter for activity.  |

**Protected Attributes inherited from [BaseInputContext](classes/classbaseinputcontext/)**

|                | Name           |
| -------------- | -------------- |
| [AppParameters](classes/structappparameters/) | **[parameters](classes/classbaseinputcontext/#variable-parameters)**  |
| std::vector< [LEDContext](classes/classledcontext/) > | **[led_vector](classes/classbaseinputcontext/#variable-led_vector)**  |
| InputTypes | **[input_type](classes/classbaseinputcontext/#variable-input_type)**  |
| bool | **[active](classes/classbaseinputcontext/#variable-active)**  |


## Public Functions Documentation

### function MusicInputContext

```cpp
inline MusicInputContext(
    AppParameters parameters,
    MusicData musicData,
    bool active
)
```


### function Process

```cpp
inline virtual std::tuple< AppParameters &, std::vector< LEDContext > & > Process()
```


**Reimplements**: [BaseInputContext::Process](classes/classbaseinputcontext/#function-process)


-------------------------------

Updated on 23 May 2021 at 21:54:47 UTC