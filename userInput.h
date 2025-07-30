#ifndef USERINPUT_H
#define USERINPUT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <stdbool.h>
#include <ctype.h>

int userInput (char **buffer, char* prompt); // Speichersichere Implementierung der Nutzereingabe
int userInput_c (char *buffer, char* prompt); // Speichersichere Implementierung der Nutzereingabe (Einzelzeichen)
int userInput_ml (char **buffer, char* prompt); // Speichersichere Implementierung der Nutzereingabe (mehrere Zeilen)
int userInput_int (int *buffer, char* prompt); // Speichersichere Implementierung der Nutzereingabe für Ganzzahlen
int userInput_double (double *buffer, char* prompt); // Speichersichere Implementierung der Nutzereingabe für Gleitkommazahlen
bool userInput_yesno (char* prompt); // Speichersichere Implementierung der Nutzereingabe für Ja/Nein-Antworten

#endif