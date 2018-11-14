#include <stdio.h>
#define BUFSIZE 100

char buf[BUFSIZE];      /* buffer for ungetch */
int bufp = 0;           /* next free poistion in buf */

int getch(void) /*get a (possibly poushed back) character */
{
    // used to pop item off the stack
    // if bufp = 0, getchar(); otherwise return the element before current bufp position.
    // the position bufp currently pointing at does not have element stored, see ungetch()
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */

// add stuff to the buf[] stack.
{
    // control when to stop adding items to the stack
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        // push element onto the stack, then pointer sp to the next position
        buf[bufp++] = c;
}
