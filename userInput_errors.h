#ifndef UINPUT_ERRORS
#define UINPUT_ERRORS

#define UINPUT_SUCCESS            0 // No error occured.
#define UINPUT_ERRMSG_GENERAL     1 // Error on input (unknown error)
#define UINPUT_ERRMSG_YN          2 // Error on input (yes/no function)
#define UINPUT_ERRMSG_INT         3 // Error: Not a valid integer was provided
#define UINPUT_ERRMSG_INT_RANGE   4 // Error: Provided integer is out-of-range
#define UINPUT_ERRMSG_DOUBLE      5 // Error: Not a valid double was provided
#define UINPUT_ERRMSG_MEMORY      6 // Error: Memory allocation or re-allocation failed

#endif