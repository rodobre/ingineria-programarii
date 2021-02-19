---
title: main.cpp
summary: Driver program for the project, exposes an HTTP server on port 8080 to handle API requests.  

---

**main.cpp File Reference**
Driver program for the project, exposes an HTTP server on port 8080 to handle API requests. ## Functions

|                | Name           |
| -------------- | -------------- |
| int | **[main](files/main_8cpp/#function-main)**(void )<br>Main driver function of the program, runs an HTTP server on port 8080 to process incoming requests (blocking!)  |


## Functions Documentation

### function main

```cpp
int main(
    void 
)
```

Main driver function of the program, runs an HTTP server on port 8080 to process incoming requests (blocking!) 

**Return**: int - status code 



## Source code

```cpp

#include <iostream>
#include "include/httplib/httplib.h"
#include "include/nlohmann/json.hpp"

int main(void) {
  httplib::Server svr;

  svr.Get("/hi", [](const auto &, auto &res) {
    res.set_content("Hello World!", "text/plain");
  });

  std::cout << "start server..." << std::endl;
  svr.listen("0.0.0.0", 8080);
}
```


-------------------------------

Updated on 19 February 2021 at 14:53:36 UTC
