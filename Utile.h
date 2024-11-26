//
// Created by gadan on 10/13/2024.
//

#ifndef UTILE_H
#define UTILE_H

/**
 * Empty the buffer of standard input
 */
void emptyBuffer();

/**
 * Print a message in the console and asks for a number
 *
 * @param message the message that will be shown
 * @return the number entered by the user
 */
int getUserNumber(const char *message);

/**
 * Remove all space caracteres ' ' at the beginning and at the end of the string provided
 *
 * @param buffer the string provided
 * @return the new string without ep
 */
char *trim(const char *buffer);

/**
 * Reduce the space ' ' to one in a string which each char € ]0, n-1[
 *
 * @param buffer the provided string
 * @return the new string
 */
char *coverExcessSpace(char *buffer);

#endif //UTILE_H
