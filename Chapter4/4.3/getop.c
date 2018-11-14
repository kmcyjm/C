#include <stdio.h>
#include <ctype.h>
#include "calc.h"

/*
    getop: get next operator or numeric operand
       
    getop will read stdin via getchar() in getch, push number (integer or float) to s[] array one by one.

    either operator or operand is ended with '\0' in the s array, and the last digit or dot will be pushed onto buf[]
    array.
*/

int getop(char s[])
{
    int i, c;
    
    // if getch() returns a whitespace or tab, continue the loop
    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;

    // add NULL('\0') to the end of array s to build a string.
    // because atof(const char *str) in main.c expects a string as its parameter
    // s[1] = '\0';
    
    // if c is not a digit nor a dot(.), return c
    // c should be a operator
    if (!isdigit(c) && c != '.')
        return c;       /* not a number */
    i = 0;
    if (isdigit(c))     /* collect integer part */
        while(isdigit(s[++i] = c = getch()))
            ;
    if (c == '.')       /* collect fraction part */
        while (isdigit(s[++i] = c =getch()))
            ;

    // add NULL('\0') to the end of array s to build a string.
    // because atof(const char *str) in main.c expects a string as its parameter
    // s[i] = '\0'; // here the first number in stdin is pushed to s[]

    // the last digit(or dot) of a number will be pushed on to buf[] defined in getch.c
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}
