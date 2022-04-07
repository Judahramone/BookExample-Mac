//
// Name: Judah Small
// OS: Mac OS
// Class/Section: CS2060 T-Th
// Assignment: Learning Activity 9
//
//

#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> // including of libraries

#define LENGTH 13

void validateInt(const char *buff);

int main(void)
{
    char inputStr[LENGTH]; // character array with a modular length
    fgets(inputStr, LENGTH, stdin); //gets a string from the user
    validateInt(inputStr); //sends it to the validate function
}

void validateInt(const char *buff) // recieves an address of an array
{
    char *end;
    errno = 0;
    int validInt = 0;
    long intTest = strtol(buff, &end, 10); //converts from sting to long data type
    //only allows a max of 10 characters to be processed end is assigned the address of the end of the new array, intTest
    if (end == buff) // if the array is the same at the beginning and the end nothing was placed into the array so null character will be present on both ends.
    {
        fprintf(stderr, "%s: not a decimal number\n", buff);
    }
    else if ('\0'!= *end) // if it is not the null character at the end of the data then there are extra characters at the end of the array
    {
        fprintf(stderr,"%s: extra characters at end of input: %s\n", buff, end);
    }
    else if ((LONG_MIN == intTest || LONG_MAX == intTest) && ERANGE == errno)
    {
        fprintf(stderr, "%s out of range of type long \n", buff);
    }
    else if(intTest > INT_MAX) // max and min values for integer data type
    {
        fprintf(stderr, "%ld greater than INT_MAX\n", intTest);
    }
    else if(intTest < INT_MIN)
    {
        fprintf(stderr, "%ld less than INT_MIN\n", intTest);
    }
    else
    {
        validInt=(int)intTest;
        
        printf("%ld is integer value", intTest);
    }
}
