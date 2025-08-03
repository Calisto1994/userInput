#ifndef USERINPUT_H
#define USERINPUT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>
#include "userInput_errors.h"

int userInput (char **buffer, char* prompt); // Memory-safe implementation of user input (single line)
int userInput_c (char *buffer, char* prompt); // Memory-safe implementation of user input (single character)
int userInput_ml (char **buffer, char* prompt); // Memory-safe implementation of user input (multiple lines)
int userInput_int (int *buffer, char* prompt); // Memory-safe implementation of user input for integers
int userInput_double (double *buffer, char* prompt); // Memory-safe implementation of user input for doubles
int userInput_yesno (bool *buffer, char* prompt, char yesChar, char noChar); // Memory-safe implementation of user input for yes/no questions
int userInput_version (char **versionInfo, char ***featureList); // query userInput version information

#endif