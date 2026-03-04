# Compile DLL with MinGW
- to compile the DLL : g++ -shared -o MyDLL.dll MyDLL.cpp 
- to generate exe : g++ -o MyApp main.cpp -L. -lMyDLL 

# Understanding DLLs and Static Libraries

## Static Library

- **Definition:** 
  A static library is a collection of object files that are linked directly into your executable at compile time. The library’s code becomes part of the final executable.

- **Advantages:**
  - **Single File Deployment:** No need to distribute separate library files.
  - **Simplicity:** Everything is included in one file, making deployment easier.

- **Disadvantages:**
  - **Increased Executable Size:** The final executable file is larger because it includes the library code.
  - **Update Complexity:** Updating the library requires recompiling the executable if the library changes.

- **Use Case Example:**
  - **Static Library:** Use when developing a small utility tool where you prefer to have everything bundled together, and you don’t expect frequent updates to the library. For instance, a standalone calculator application with built-in functions.

## DLL (Dynamic Link Library)

- **Definition:**
  A DLL is a separate file that contains code and data used by multiple programs. It is loaded and linked at runtime, rather than at compile time.

- **Advantages:**
  - **Reduced Executable Size:** The main executable file remains smaller as the library code is separate.
  - **Update Flexibility:** Allows updates to the library without needing to recompile the application.
  - **Shared Use:** Can be used by multiple applications, saving memory and disk space.

- **Disadvantages:**
  - **Version Management:** Requires careful management of DLL versions and dependencies.
  - **Deployment Complexity:** Involves distributing multiple files, making deployment slightly more complex.

- **Use Case Example:**
  - **DLL:** Ideal for larger applications or systems with shared components that need independent updates. For example, a web browser that uses plugins (DLLs) which can be updated without affecting the main browser executable.

## Summary

- **Static Library:** Best suited for simple, standalone applications where you want all code bundled into a single file and don’t anticipate frequent updates.
- **DLL:** Ideal for larger applications or systems with components that may be updated independently, allowing for shared code across multiple programs.
