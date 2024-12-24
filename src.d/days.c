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


#include "../inc.d/days.h"


static int is_leap(const int);
static void fill_array(int *, const int, const char *);
static int validate(int);


/* Function descibed at the top of this file.                                 */
void get_days(int **months,
              const int year,
              const int inityear,
              const int *first_days_inityear) {

    /* 1. Get difference of selected *year* and *inityear*                    */
    int years_from_inityear = year - inityear;
    int sign; if (years_from_inityear > 0) { sign = 1; } else { sign = -1; }

    /* 2. Find out if *year* is a leap year                                   */
    int is_leap_year = is_leap(year);

    /* 3. Copy *first_days_inityear* to *first_days_year*                     */
    int first_days_year[12];
    for (int i=0; i<12; i++) first_days_year[i] = first_days_inityear[i];

    /* 4. Obtain *first_days_year*                                            */
    int s1, s2;
    for (int i=0; i<sign*years_from_inityear; i++) {
        i = inityear + sign * i;
        s1 = (sign-1)/2;
        s2 = (sign+1)/2;
        first_days_year[ 0] = first_days_year[ 0] + sign + sign * is_leap(i+s1);
        first_days_year[ 1] = first_days_year[ 1] + sign + sign * is_leap(i+s1);
        first_days_year[ 2] = first_days_year[ 2] + sign + sign * is_leap(i+s2);
        first_days_year[ 3] = first_days_year[ 3] + sign + sign * is_leap(i+s2);
        first_days_year[ 4] = first_days_year[ 4] + sign + sign * is_leap(i+s2);
        first_days_year[ 5] = first_days_year[ 5] + sign + sign * is_leap(i+s2);
        first_days_year[ 6] = first_days_year[ 6] + sign + sign * is_leap(i+s2);
        first_days_year[ 7] = first_days_year[ 7] + sign + sign * is_leap(i+s2);
        first_days_year[ 8] = first_days_year[ 8] + sign + sign * is_leap(i+s2);
        first_days_year[ 9] = first_days_year[ 9] + sign + sign * is_leap(i+s2);
        first_days_year[10] = first_days_year[10] + sign + sign * is_leap(i+s2);
        first_days_year[11] = first_days_year[11] + sign + sign * is_leap(i+s2);
        i = sign * (i - inityear);
    }

    for (int i=0; i<12; i++) first_days_year[i] = validate(first_days_year[i]);

    /* 5. Use *first_days_year* to fill arrays                                */
    char type1[] = "31";
    char type2[] = "30";
    char type3[] = "feb_leap_false";
    char type4[] = "feb_leap_true";
    int first;
    char *type_of_month;
    for (int i=0; i<12; i++) {
        first = first_days_year[i];

        /* Check if the month has 30, 31 or 28/29 days and react accordingly  */
        switch (i) {
            case 0:
            case 2:
            case 4:
            case 6:
            case 7:
            case 9:
            case 11:
                type_of_month = type1;
                break;
            case 3:
            case 5:
            case 8:
            case 10:
                type_of_month = type2;
                break;
            case 1:
                if (is_leap_year)
                    type_of_month = type4;
                else
                    type_of_month = type3;
                break;
            default:
                printf("%s\n", "Error occurred in program *days.c*");
                exit(1);
                break;
        }

        fill_array(months[i], first, type_of_month);
    }
}

/* Function to check if *year* is a leap year according to Gregorianian rules */
static int is_leap(const int year) {
    int is_leap_year;
    if (year%4 != 0) {
        is_leap_year = 0;
    } else {
        if (year%100 != 0) {
            is_leap_year = 1;
        } else {
            if (year%400 == 0) {
               is_leap_year = 1;
            } else {
               is_leap_year = 0;
            }
        }
    }

    return is_leap_year;
}

/* Helper function filling one array corresponding to one month               */
static void fill_array(int *arr, const int first, const char *type_of_month) {

    /* Distinguish cases by *type_of_month*                                   */
    int i;
    if (strcmp(type_of_month, "31") == 0) {

        /* Trailing zeros                                                     */
        for (i=0; i<first-1; i++) arr[i] = 0;

        /* Count from 1 to 31                                                 */
        for (i=first-1; i<first+31-1; i++) arr[i] = i-first+2;

        /* Set remaining entries zero                                         */
        for (i=first+31-1; i<42; i++) arr[i] = 0;

    } else if (strcmp(type_of_month, "30") == 0) {

        /* Trailing zeros                                                     */
        for (i=0; i<first-1; i++) arr[i] = 0;

        /* Count from 1 to 30                                                 */
        for (i=first-1; i<first+30-1; i++) arr[i] = i-first+2;

        /* Set remaining entries zero                                         */
        for (i=first+30-1; i<42; i++) arr[i] = 0;

    } else if (strcmp(type_of_month, "feb_leap_false") == 0) {

        /* Trailing zeros                                                     */
        for (i=0; i<first-1; i++) arr[i] = 0;

        /* Count from 1 to 28                                                 */
        for (i=first-1; i<first+28-1; i++) arr[i] = i-first+2;

        /* Set remaining entries zero                                         */
        for (i=first+28-1; i<42; i++) arr[i] = 0;

    } else if (strcmp(type_of_month, "feb_leap_true") == 0) {

        /* Trailing zeros                                                     */
        for (i=0; i<first-1; i++) arr[i] = 0;

        /* Count from 1 to 29                                                 */
        for (i=first-1; i<first+29-1; i++) arr[i] = i-first+2;

        /* Set remaining entries zero                                         */
        for (i=first+29-1; i<42; i++) arr[i] = 0;
    }
}

/* Helper function changing action of *%* operator                            */
static int validate(int n) {
    int np = n%7;
    if (np == 0) np = 7;
    while (np < 0) {
        np = np + 7;
    }

    return np;
}
