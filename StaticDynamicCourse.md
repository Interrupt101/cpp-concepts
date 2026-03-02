# Header Files (.h or .hpp)
### Purpose: Header files contain declarations of functions, classes, variables, and other constructs. They act as an interface that other files can include and use.
### Usage: Header files are typically included in source files (.cpp), allowing those source files to access the declarations inside the headers.
```cpp
// mathutils.h
#ifndef MATHUTILS_H
#define MATHUTILS_H

// Function declaration
int add(int a, int b);
int multiply(int a, int b);

#endif
```

# 2. Source Files (.cpp or .c)
### Purpose: Source files contain the actual implementation (definitions) of functions, classes, and other constructs declared in header files.
### Usage: The .cpp file includes the header file and provides the definitions for the functions declared in the header.
```cpp
// mathutils.cpp
#include "mathutils.h"

// Function definitions
int add(int a, int b) {
    return a + b;
}

int multiply(int a, int b) {
    return a * b;
}
```
# 3. Libraries
Libraries are collections of precompiled code that you can reuse in your programs. There are two main types of libraries:

## 3.1 Static Libraries (.lib or .a on Linux)
- Purpose: Static libraries are linked directly into your executable at compile time. This means the code from the library is included in the final .exe or binary file.
- Usage: The code from a static library becomes part of your application, which makes the final application larger in size but independent of the library afterward.

## 3.2 Dynamic Libraries (DLLs in Windows, .so in Linux)
- Purpose: Dynamic libraries are linked at runtime, meaning they are separate files (like .dll in Windows) that the application uses during execution. The main advantage is smaller executable size and the ability to update the DLL without recompiling the whole application.
- Usage: The application loads the DLL at runtime and calls its functions.
