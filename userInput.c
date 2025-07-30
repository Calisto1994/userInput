#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <stdbool.h>
#include <ctype.h>
#include "language_EN.h" // English language. May be replaced, but NOT left out.

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
// userInput_yesno: Reads a yes/no answer from the user and returns a boolean value (true for yes, false for no).

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
char* userInput_version         =       "v1.0.2-dev";
char* userInput_features[6]     =       {"userInput", "userInput_c", "userInput_ml", "userInput_int", "userInput_double", "userInput_yesno"};

// ****** Function declarations ******

int userInput (char **buffer, char* prompt); // Memory-safe implementation of user input (single line)
int userInput_c (char *buffer, char* prompt); // Memory-safe implementation of user input (single character)
int userInput_ml (char **buffer, char* prompt); // Memory-safe implementation of user input (multiple lines)
int userInput_int (int *buffer, char* prompt); // Memory-safe implementation of user input for integers
int userInput_double (double *buffer, char* prompt); // Memory-safe implementation of user input for doubles
bool userInput_yesno (char* prompt); // Memory-safe implementation of user input for yes/no questions

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
                fprintf(stderr, LANG_ERRMSG_MEMORY);
                free(*buffer);
                return 1;
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
                fprintf(stderr, LANG_ERRMSG_MEMORY);
                free(*buffer);
                return 1;
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
        printf(LANG_ERRMSG_GENERAL);
        return 1; // Error in input
    }

    long value = strtol(input, &endptr, 10);
    if (value < INT_MIN || value > INT_MAX) {
        fprintf(stderr, LANG_ERRMSG_INT_RANGE);
        free(input);
        return 1; // Error in input
    }

    if (errno == ERANGE || (endptr == input) || (*endptr != '\0')) {
        fprintf(stderr, LANG_ERRMSG_INT);
        free(input);
        return 1; // Error in input
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
        printf(LANG_ERRMSG_GENERAL);
        return 1; // Error in input
    }

    double value = strtod(input, &endptr);

    if (errno == ERANGE || (endptr == input) || (*endptr != '\0')) {
        free(input); // Free memory on error
        fprintf(stderr, LANG_ERRMSG_DOUBLE);
        return 1; // Error in input
    }

    free(input);
    *buffer = value;
    return 0; // Successful input
}

bool userInput_yesno (char* prompt) {
    char zeichen;

    while (true) {
        if (userInput_c(&zeichen, prompt) != 0) {
            fprintf(stderr, "Error on input (yes/no).\n");
            return false; // Treat EOF as no answer
        }
        if (tolower(zeichen) == LANG_YESCHAR) {
            printf("\n"); // New line for better readability
            return true; // Yes
        } else if (tolower(zeichen) == LANG_NOCHAR) {
            printf("\n"); // New line for better readability    
            return false; // No
        } else {
                    printf(LANG_ERRMSG_YN);
            continue; // Restart loop
        }
    }
}