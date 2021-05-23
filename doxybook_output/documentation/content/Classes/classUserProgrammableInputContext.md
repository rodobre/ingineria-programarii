---
title: UserProgrammableInputContext
summary: Input context class for programmable user input.  

---

**UserProgrammableInputContext Class Reference**


Input context class for programmable user input. 
`#include <inputcontext.hpp>`

Inherits from [BaseInputContext](classes/classbaseinputcontext/)

## Additional inherited members

**Public Functions inherited from [BaseInputContext](classes/classbaseinputcontext/)**

|                | Name           |
| -------------- | -------------- |
| | **[BaseInputContext](classes/classbaseinputcontext/#function-baseinputcontext)**() |
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


-------------------------------

Updated on  7 March 2021 at 03:11:44 UTC