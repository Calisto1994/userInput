#ifndef EXTSTRING_H
#define EXTSTRING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int extString_explode (char separator, char ***buffer); // Array of char-arrays ("explodes" a string based on the given separator)

#endif