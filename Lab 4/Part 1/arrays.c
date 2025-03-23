/* SYSC 2006 Lab 4.

 * Incomplete implementations of the functions that will be coded during the lab.
 */
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "arrays.h"

/* Exercise 1. */

/* Return the average magnitude of the signal represented by
 * the n doubles in x[].
 * This function assumes that parameter n is >= 1.
 */
double avg_magnitude(double x[], int n)
{
    double result = 0;          // declare variable to hold final result of function
    for (int i = 0; i < n; i++) // iterate through every element of array
    {
        result += fabs((x[i])); // repopulate 'result' with all absolute values of array
    }
    return (result / n); // calculate average and return to user
}

/* Exercise 2. */

/* Return the average power of the signal represented by
 * the n doubles in x[].
 * This function assumes that parameter n is >= 1.
 */
double avg_power(double x[], int n)
{
    double result = 0;          // declare variable to hold final result of function
    for (int i = 0; i < n; i++) // iterate through every element of array
    {
        result += fabs((x[i])) * (fabs((x[i]))); // repopulate 'result' with the ^2 values of each element of the array
    }
    return result / n; // calculate average and return to user
}

/* Exercise 3. */

/* Return the largest of the n doubles in arr[].
 * This function assumes that parameter n is >= 1.
 */
double maxi(double arr[], int n)
{
    double max = arr[0];        // declare variable to hold maximum value of array
    for (int i = 1; i < n; i++) // iterate through every element of array
    {
        if (arr[i] > max) // determine whether current element of array is greater then previously greatest element
        {
            max = arr[i]; // replace max value with greater element if necessary
        }
    }
    return max; // return greatest value to user
}

/* Exercise 4. */

/* Return the smallest of the n doubles in arr[].
 * This function assumes that parameter n is >= 1.
 */
double mini(double arr[], int n)
{
    double min = arr[0];        // declare variable to hold minimum value of array
    for (int i = 1; i < n; i++) // iterate through every element of array
    {
        if (arr[i] < min) // determine whether current element of array is smaller then previously minimum element
        {
            min = arr[i]; // replace min value with smaller element if necessary
        }
    }
    return min; // return minimum value to user
}

/* Exercise 5. */

/* Normalize the n doubles in x[].
 * This function assumes that parameter n is >= 2, and that at least
 * two of the values in x[] are different.
 */
void normalize(double x[], int n)
{
    double max = maxi(x, n), min = mini(x, n); // declare variables to hold the max and min values of the array using the previously made funcitons
    for (int i = 0; i < n; i++)                // iterate through every element of the array
    {
        x[i] = (x[i] - min) / (max - min); // use the given logic and equation to normalize the array
    }
}
