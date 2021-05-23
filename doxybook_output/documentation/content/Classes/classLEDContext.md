---
title: LEDContext
summary: LED context class.  

---

**LEDContext Class Reference**


LED context class. 
`#include <inputcontext.hpp>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[LEDContext](classes/classledcontext/#function-ledcontext)**() |
| | **[LEDContext](classes/classledcontext/#function-ledcontext)**(unsigned char intensity, [RGB](classes/structrgb/) rgb, bool visible) |
| | **[LEDContext](classes/classledcontext/#function-ledcontext)**(const [LEDContext](classes/classledcontext/) & led_context) |
| [RGB](classes/structrgb/) | **[getRGB](classes/classledcontext/#function-getrgb)**() |

## Public Functions Documentation

### function LEDContext

```cpp
inline LEDContext()
```


### function LEDContext

```cpp
inline LEDContext(
    unsigned char intensity,
    RGB rgb,
    bool visible
)
```


### function LEDContext

```cpp
inline LEDContext(
    const LEDContext & led_context
)
```


### function getRGB

```cpp
inline RGB getRGB()
```


-------------------------------

Updated on 23 May 2021 at 21:54:47 UTC