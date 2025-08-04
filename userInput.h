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

int userInput (char **buffer, char* prompt); // Memory-safe implementation of user input (single line)          Returns dynamic buffer (must be freed)
int userInput_c (char *buffer, char* prompt); // Memory-safe implementation of user input (single character)    Returns static buffer (no need to be freed)
int userInput_ml (char **buffer, char* prompt); // Memory-safe implementation of user input (multiple lines)    Returns dynamic buffer (must be freed)
int userInput_int (int *buffer, char* prompt); // Memory-safe implementation of user input for integers         Returns static buffer (no need to be freed)
int userInput_double (double *buffer, char* prompt); // Memory-safe implementation of user input for doubles    Returns static buffer (no need to be freed)
int userInput_yesno (bool *buffer, char* prompt, char yesChar, char noChar); // Memory-safe implementation of user input for yes/no questions
                                                                                                            //  Returns static buffer (no need to be freed)
int userInput_date (time_t *myDate, char* prompt); // Memory-safe implementation of user input for dates          Returns a static buffer (no need to be freed)
int userInput_time (time_t *myTime, char* prompt); // Memory-safe implementation of user input for time           Returns a static buffer (no need to be freed)
int userInfo_version (char **versionInfo, char ***featureList); // query userInput version information          Returns two pointers to some static buffers

#endif