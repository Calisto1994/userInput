# userInput

A collection of memory-safe user input functions for C  
*(Tested on Windows, Linux, and macOS; C17 compliant)*

## Overview

This library provides a set of functions for reading user input in a memory-safe way.  
It includes functions for reading single characters, lines, integers, and doubles.  
All functions are designed to be portable and do **not** rely on platform-specific features.

## Features

- **Memory-safe input handling:**  
  All functions handle dynamic memory allocation and error cases (e.g., memory shortage, invalid input).
- **Cross-platform:**  
  Works on Windows, Linux, and macOS (tested).
- **C17 compliant:**  
  No platform-specific dependencies.
- **Simple API:**  
  Functions return `0` on success and `1` on failure.
- **Responsibility for freeing memory:**  
  Functions that return dynamically allocated buffers require the caller to free them.

## Functions

- `int userInput(char **buffer, char* prompt);`  
  Reads a line of input from the user into a dynamically allocated buffer.

- `int userInput_c(char *buffer, char* prompt);`  
  Reads a single character from the user.

- `int userInput_ml(char **buffer, char* prompt);`  
  Reads multiple lines of input from the user into a dynamically allocated buffer.

- `int userInput_int(int *buffer, char* prompt);`  
  Reads an integer from the user.

- `int userInput_double(double *buffer, char* prompt);`  
  Reads a double from the user.

  `bool userInput_yesno(char* prompt);`
  Returns a boolean on yes/no (true/false) after a user was questioned

## Memory Management

- Only the line input functions (`userInput`, `userInput_ml`) return a dynamically allocated buffer that **must be freed** by the caller.
- Other functions (`userInput_c`, `userInput_int`, `userInput_double`) use a static buffer or a pointer to an existing buffer and **do not require** the caller to free memory.

## Usage

Once introduced to your program (either by compiling as a shared object or by including userInput.c directly to your project), you can use either of these functions
in the following way:

### Character Inputs (single line)

```
    char* myChar;
    myChar = userInput(&myChar, "Tell me your name: ");
    // YOUR CODE HERE
    free(myChar);
```

### Character Inputs (multiple lines) - requires CTRL+D/EOF to continue

```
    char* myChar;
    myChar = userInput(&myChar, "Tell me your name: ");
    // YOUR CODE HERE
    free(myChar);
```

### All the other Input functions

```
    char mySingleChar;
    int myInteger;
    double myDouble;

    mySingleChar = userInput_c(&mySingleChar, "Yes or no [y/n]?");
    myInteger = userInput_int(&int, "How old are you?");
    myDouble = userInput_double(&myDouble, "How tall are you (in meters, two decimal places)?");
```

### Boolean input function - Yes/No questions

```
    switch (userInput_yesno("Do you want to continue?")) {
      case true:
          // CODE FOR YES HERE
          break;
      case false:
          // CODE FOR NO HERE
          break;
    }
```

## Use as shared library

You can also build the userInput library as a shared object (and, if required, install to your system using the makefile) 

### Build & Install

```
  make && make install

```

If you want to build just the shared object, you can just run `make` and the file `libuserInput.so` will be generated in the workdir directly.
To remove the library from your system, simply use `make uninstall` and the library and header file will be deleted.