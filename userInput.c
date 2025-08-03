#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>
#include "userInput_errors.h"      // Includes it's own header in order to know about the error message codes

// *** userInput.c - Memory-safe user input functions ***
// This file contains functions for reading user input in a memory-safe way.
// It includes functions for reading single characters, lines, integers, and doubles.
// It is meant to be compliant with the C17 standard and therefore can be used on
// various platforms without relying on platform-specific features.
// It, without further modifications, can be used in any C project that requires user input handling.
// It'll work on Windows, Linux and macOS, as test cases have shown.

// ****** User input functions ******
// List of features:
// userInput: Reads a line of input from the user and stores it in a dynamically allocated buffer.
// userInput_c: Reads a single character from the user and stores it in a char buffer.
// userInput_ml: Reads multiple lines of input from the user and stores them in a dynamically allocated buffer.
// userInput_int: Reads an integer from the user and stores it in an int buffer.
// userInput_double: Reads a double from the user and stores it in a double buffer.
// userInput_yesno: Reads a yes/no answer from the user and returns a boolean value (-1 for yes, -2 for no).

// !!!!! ATTENTION: These functions are designed to be memory-safe, meaning they handle dynamic memory allocation
// (malloc/realloc) and error cases such as memory shortages or invalid inputs.
// They return 0 on success and 1 on failure.
// The caller is responsible for freeing the returned buffer after use to avoid memory leaks.
// Therefore; handle with care and ensure to free the allocated memory after use.
//
// MEMORY FREEING: Only the line input functions (userInput, userInput_ml) return a dynamically allocated buffer that must be freed by the caller.
// Every other function (userInput_c, userInput_int, userInput_double) uses a static buffer or a pointer to an existing buffer that does not need
// to be freed by the caller.
// This was intentionally done to avoid unnecessary memory management overhead for simple inputs and to simplify the usage of these functions in most cases.

// ****** Variable declarations ******

// Variables for information (e.g. when using the shared library)
char* userInput_release         =       "v2.0-dev";
char* userInput_features[7]     =       {"userInput", "userInput_c", "userInput_ml", "userInput_int", "userInput_double", "userInput_yesno", "userInput_version"};
    // the array allows for checking whether a specific feature is available in this version of the library once compiled, since these
    // are globally available variables. For this, you'll use the userInput_version() function.
    // This function is required since the global variables of a shared object (.so (Linux) or .dll (Win32)) aren't otherwise accessible
    // to the caller.

// ****** Function declarations ******

int userInput (char **buffer, char* prompt); // Memory-safe implementation of user input (single line)          Returns dynamic buffer (must be freed)
int userInput_c (char *buffer, char* prompt); // Memory-safe implementation of user input (single character)    Returns static buffer (no need to be freed)
int userInput_ml (char **buffer, char* prompt); // Memory-safe implementation of user input (multiple lines)    Returns dynamic buffer (must be freed)
int userInput_int (int *buffer, char* prompt); // Memory-safe implementation of user input for integers         Returns static buffer (no need to be freed)
int userInput_double (double *buffer, char* prompt); // Memory-safe implementation of user input for doubles    Returns static buffer (no need to be freed)
int userInput_yesno (bool *buffer, char* prompt, char yesChar, char noChar); // Memory-safe implementation of user input for yes/no questions           Returns a boolean value directly, no freeing;
int userInput_date (time_t *date, char* prompt); // Memory-safe implementation of user input for dates         Returns a statc buffer (no need to be freed);
int userInfo_version (char **versionInfo, char ***featureList); // query userInput version information          Returns two pointers to some static buffers

struct DateTime {   // custom data type for mixed date/time inputs (and for calculations with them)
    int day;
    int month;
    int year;
    int hour;
    int minute;
    int second;
};
// These custom data types will be used to create time_t elements, representing the seconds since January 1st, 1970 - just like
// most programming languages handle this kind of data these days. But, as always: We want to be memory-safe here, ofc;
// Also, why we use time_t: it's standard C, and we want to keep all this C17-compliant.
// *** ------------------------------ ***

// ****** Character input functions ******

int userInput (char **buffer, char* prompt) {
    char thisChar;
    *buffer = malloc(1);
    size_t size = 1;
    size_t len = 0;

    printf("%s", prompt);
    while ((thisChar = getchar()) != '\n' && thisChar != EOF) {
        if (len + 2 > size) {
            size += 2;
            char* tmp = realloc(*buffer, size);
            if (!tmp) {
                free(*buffer);
                return UINPUT_ERRMSG_GENERAL;
            }
            *buffer = tmp;
        }
        (*buffer)[len++] = thisChar;
        (*buffer)[len] = '\0'; // Null-terminate the string
    }
    return 0;
}

int userInput_c (char *buffer, char* prompt) {
    char* thisChar;
    if (userInput(&thisChar, prompt) != 0) {
        return 1;
    }
    *buffer = thisChar[0]; // Only the first character is needed
    free(thisChar); // Free the buffer as it is no longer needed
    return 0;
}

int userInput_ml (char **buffer, char* prompt) {
    char thisChar;
    *buffer = malloc(1);
    size_t size = 1;
    size_t len = 0;

    printf("%s", prompt);
    while ((thisChar = getchar()) != EOF) { // Only EOF is checked, so multiple lines can be entered, "\n" is ignored
        if (len + 2 > size) {
            size *= 2;
            char* tmp = realloc(*buffer, size);
            if (!tmp) {
                free(*buffer);
                return UINPUT_ERRMSG_MEMORY;
            }
            *buffer = tmp;
        }
        (*buffer)[len++] = thisChar;
        (*buffer)[len] = '\0'; // Null-terminate the string
    }
    return 0;
}

// ****** Numeric input functions ******

int userInput_int (int *buffer, char* prompt) {
    // Variable declarations
    char *input;
    char *endptr;
    errno = 0; // Reset errno before input

    // User Input
    if (userInput(&input, prompt) != 0) {
        return UINPUT_ERRMSG_GENERAL; // Error in input
    }

    long value = strtol(input, &endptr, 10);
    if (value < INT_MIN || value > INT_MAX) {
        free(input);
        return UINPUT_ERRMSG_GENERAL; // Error in input
    }

    if (errno == ERANGE || (endptr == input) || (*endptr != '\0')) {
        free(input);
        return UINPUT_ERRMSG_MEMORY; // Error in input
    }

    free(input);
    *buffer = (int)value; // Convert long to int
    return 0; // Successful input
}

int userInput_double (double *buffer, char* prompt) {
    // Variable declarations
    char *input;
    char *endptr;
    errno = 0; // Reset errno before input

    // User Input
    if (userInput(&input, prompt) != 0) {
        return UINPUT_ERRMSG_GENERAL; // Error in input
    }

    double value = strtod(input, &endptr);

    if (errno == ERANGE || (endptr == input) || (*endptr != '\0')) {
        free(input); // Free memory on error
        return UINPUT_ERRMSG_DOUBLE; // Error in input
    }

    free(input);
    *buffer = value;
    return 0; // Successful input
}

int userInput_yesno (bool *buffer, char* prompt, char yesChar, char noChar) {
    char zeichen;

    if (tolower(zeichen) == yesChar) {
        printf("\n"); // New line for better readability
        buffer = true;
        return UINPUT_SUCCESS; // Yes
    } else if (tolower(zeichen) == noChar) {
        printf("\n"); // New line for better readability    
        return UINPUT_SUCCESS; // No
    } else {
        return UINPUT_ERRMSG_GENERAL;
    }


    /* Version information: v2.0-* */
    /* userInput_yesno() now does _not_ directly return the value using return(); - it will only return error messages this way.
       Like all other userInput functions, it'll write the return value of the requested information into a buffer, so a pointer
       has to be provided. This is a static buffer return, so it doesn't require free(); */
}

int userInput_date (time_t *date, char* prompt) {
    char* input;
    userInput(&input, prompt);
    // TODO: Well... what about some conversion of the user input to a date?!
}

int userInfo_version(char **versionInfo, char ***featureList) {
    *versionInfo = userInput_release;
    *featureList = userInput_features;
    return 0; // Function can't fail, so we'll always return 0 to signal everything's okay.
}