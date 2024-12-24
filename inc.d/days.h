/* -------------------------------------------------------------------------- *
 *                                                                            *
 * This file is part of the application *calendar* by Simon Euchner.          *
 *                                                                            *
 * -------------------------------------------------------------------------- *
 *                                                                            *
 * LICENSE: GPL-3.0                                                           *
 *                                                                            *
 * IMPORTANT: THIS IS FREE SOFTWARE WITHOUT ANY WARRANTY. THE USER IS FREE TO *
 *            MODIFY AND REDISTRIBUTE THIS SOFTWARE UNDER THE TERMS OF THE    *
 *            LICENSE LISTED ABOVE PUBLISHED BY THE FREE SOFTWARE FOUNDATION. *
 *            THE PUBLISHER, SIMON EUCHNER, IS NOT RESPONSIBLE FOR ANY        *
 *            NEGATIVE EFFECTS THIS SOFTWARE MAY CAUSE.                       *
 *                                                                            *
 * -------------------------------------------------------------------------- *
 *                                                                            *
 * In this program a function to compute the correpsonding week day to any    *
 * date starting from the first January, 1753 is provided. The used calender  *
 * is the Gregorianian one, actually introduced in 1582 by Gregor XIII.       *
 * The different year 1753 is the year where the UNIX *cal* program started   *
 * to use the Gregorianian calender, which was used for testing this program. *
 * Therefore, one is advised to stay in the range of 1753 -> infty. So, if    *
 * you are a time traveller you may need to find another calender ;-).        *
 *                                                                            *
 * The function is called *get_days*. It has the following signature:         *
 *                                                                            *
 * Arguments:                                                                 *
 *     int **months            : This must be an array of 12 pointers to      *
 *                               integer arrays of size 42. The arrays do not *
 *                               need be initialized, as they are             *
 *                               automatically during the function call. Each *
 *                               array represents a months.                   *
 *     int year                : Year one wants to find out which week day    *
 *                               corresponds to which date.                   *
 *     int inityear            : Year used as initialization. It is best to   *
 *                               set a year near the *year* arguments one is  *
 *                               interested in for performance reasons.       *
 *                               However, it starts to really affect          *
 *                               performance only at a scale                  *
 *                               |*year*-*inityear*| ~ 10E+8.                 *
 *     int *first_days_inityear: This is a pointer to an integer array fo 12  *
 *                               entries specifying which days correspond to  *
 *                               which dates in the *inityear*. For instance, *
 *                               if *inityear*=2024, the array must have the  *
 *                               form {1, 4, 5, 1, 3, 6, 1, 4, 7, 2, 5, 7},   *
 *                               because the first day of January was a       *
 *                               Monday (1), the first of February a Thursday *
 *                               (4), and so son unitil December. This must   *
 *                               be set once in youre lifetime, unless you    *
 *                               are reaching ages in the order of 10E+8 ;-). *
 *                                                                            *
 * Return:                                                                    *
 *     Type is void. However, the arrays defined by *months* is filled.       *
 *     For each month an array of 42 integers is available. As an example     *
 *     take January of 2025. The array has the following form (in row-major   *
 *     order):                                                                *
 *                                                                            *
 *          0  0  1  2  3  4  5                                               *
 *          6  7  8  9 10 11 12                                               *
 *         13 14 15 16 17 18 19                                               *
 *         20 21 22 23 24 25 26                                               *
 *         27 28 29 30 31  0  0                                               *
 *                                                                            *
 * -------------------------------------------------------------------------- */


#ifndef DAYS_H
#define DAYS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_days(int **, const int, const int, const int *);

#endif
