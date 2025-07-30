#ifndef USERINPUT_H
#define USERINPUT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <stdbool.h>
#include <ctype.h>

int userInput (char **buffer, char* prompt); // Memory-safe implementation of user input (single line)
int userInput_c (char *buffer, char* prompt); // Memory-safe implementation of user input (single character)
int userInput_ml (char **buffer, char* prompt); // Memory-safe implementation of user input (multiple lines)
int userInput_int (int *buffer, char* prompt); // Memory-safe implementation of user input for integers
int userInput_double (double *buffer, char* prompt); // Memory-safe implementation of user input for doubles
bool userInput_yesno (char* prompt); // Memory-safe implementation of user input for yes/no questions

#endif