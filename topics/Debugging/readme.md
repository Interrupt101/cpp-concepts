What is Debug Mode?
When you compile a program, you can choose different modes which affect how the compiler optimizes and manages the code. Debug mode is one of these options. Here's what it typically involves:

- Debugging Information: In debug mode, the compiler includes additional information in the executable that helps with debugging. This includes information about the source code lines, variable names, and other details that make it easier to trace and debug issues.

- No Optimization: The compiler does not perform aggressive optimizations in debug mode. Optimization can change the way code executes and can make debugging more difficult, so it’s generally turned off.

- Error Checking: Debug mode often includes additional runtime checks that can help catch errors that might be harder to find otherwise. For example, it might help detect buffer overflows or uninitialized variables.


# Debugging with GDB and MinGW

This guide explains how to use GDB (GNU Debugger) with MinGW for debugging C++ programs on Windows.

## Compiling Your Program with Debug Information

To enable debugging, you need to compile your program with the `-g` flag. This includes debugging information in the executable.

```
g++ -g -o myprogram myprogram.cpp
```
Here:

- -g adds debugging information.
- -o myprogram specifies the name of the output executable.

## Starting GDB
Navigate to the directory containing your compiled program and start GDB with:
```
gdb myprogram
```
Add a break point:
```
break main
```
To run the program :
```
run
```
To step into next line :
```
next
```
Then to show the assembly :
```
disassemble
```
```
print *p
```
