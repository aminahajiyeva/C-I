/* SYSC 2006 Lab 3, part 2. */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "recursion.h"

/* Exercise 4. Return the number of digits in integer n, n >= 0. */
int num_digits(int n)
{
    int digits = 0;  // define variable to hold number of digits in given integer
    if (n / 10 == 0) // check if only one digit
    {
        return 1; // if only 1 digit, inform user
    }
    else
    {
        return 1 + (num_digits(n / 10)); // inform user of number of digits by calling function as many times as needed
    }
}

/* Exercise 5. Return x raised to the power n for n >= 0. */
double power2(double x, int n)
{
    printf("x = %.1f, n = %d\n", x, n);
    if (n == 0) // if integer is a 0
    {
        return 1;
    }
    if (n % 2 == 0) // even cases
    {
        return (power2(x, n / 2) * power2(x, n / 2));
    }
    else // odd cases
    {
        return (x * power2(x, n / 2) * power2(x, n / 2));
    }
}
