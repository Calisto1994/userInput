#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <stdbool.h>
#include <ctype.h>

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


// ****** Function declarations ******

int userInput (char **buffer, char* prompt); // Memory-safe implementation of user input (single line)
int userInput_c (char *buffer, char* prompt); // Memory-safe implementation of user input (single character)
int userInput_ml (char **buffer, char* prompt); // Memory-safe implementation of user input (multiple lines)
int userInput_int (int *buffer, char* prompt); // Memory-safe implementation of user input for integers
int userInput_double (double *buffer, char* prompt); // Memory-safe implementation of user input for doubles
bool userInput_yesno (char *buffer, char* prompt); // Memory-safe implementation of user input for yes/no questions

// ****** Character input functions ******

int userInput (char **buffer, char* prompt) {
    char thisChar;
    *buffer = malloc(1);
    size_t size = 1;
    size_t len = 0;

    printf("%s", prompt);
    while ((thisChar = getchar()) != '\n' && thisChar != EOF) {
        if (len + 2 > size) {
            size *= 2;
            char* tmp = realloc(*buffer, size);
            if (!tmp) {
                fprintf(stderr, "Memory allocation failed\n");
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
    while ((thisChar = getchar()) != EOF) { // Nur nach EOF abfragen für mehrere Zeilen ("\n" wird nicht berücksichtigt)
        if (len + 2 > size) {
            size *= 2;
            char* tmp = realloc(*buffer, size);
            if (!tmp) {
                fprintf(stderr, "Memory allocation failed\n");
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

    // User Input
    if (userInput(&input, prompt) != 0) {
        printf("Fehler bei der Eingabe.\n");
        free(input);
        return 1; // Error in input
    }

    int value = strtol(input, &endptr, 10);

    if (errno == ERANGE || (endptr == input) || (*endptr != '\0')) {
        fprintf(stderr, "User-provided input not a valid integer.\n");
        free(input);
        return 1; // Error in input
    }
    errno=0; // Reset errno for the next input

    free(input);
    *buffer = value;
    return 0; // Successful input
}

int userInput_double (double *buffer, char* prompt) {
    // Varable declarations
    char *input;
    char *endptr;

    // User Input
    if (userInput(&input, prompt) != 0) {
        printf("Fehler bei der Eingabe.\n");
        free(input);
        return 1; // Error in input
    }

    int value = strtof(input, &endptr);

    if (errno == ERANGE || (endptr == input) || (*endptr != '\0')) {
        fprintf(stderr, "User-provided input not a valid double.\n");
        free(input);
        return 1; // Error in input
    }
    errno=0; // Reset errno for the next input

    free(input);
    *buffer = value;
    return 0; // Successful input
}

bool userInput_yesno (char *buffer, char* prompt) {
    char zeichen;

    while (true) {
        userInput_c(&zeichen, prompt);
        if (tolower(zeichen) == 'y') {
            printf("\n"); // New line for better readability
            return true; // Yes
        } else if (tolower(zeichen) == 'n') {
            printf("\n"); // New line for better readability    
            return false; // No
        } else {
            printf("Invalid input! Only answer y/n please.\n");
            continue; // Restart loop
        }
    }
}