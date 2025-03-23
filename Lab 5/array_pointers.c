/* array_pointers.c - SYSC 2006 Lab 5 */

#include <stdlib.h>
#include <stdio.h>

#include "array_pointers.h"

// Exercise 1

/* Return the maximum value in the first n elements of array of integers, ar.
   If n is less than or equal to 0, it returns 0.
   This function uses array indices.  Do not change this function. */
int find_max_v0(const int ar[], int n)
{
	int max;
	if (n <= 0)
	{
		return 0; // ensure we proceed only if n is reasonable
	}
	max = ar[0];
	for (int i = 1; i < n; i++)
	{
		if (ar[i] > max)
		{
			max = ar[i];
		}
	}
	return max;
}

/* Return the maximum value in the first n elements of an array of integers.
   If n is less than or equal to 0, it returns 0.
   This function uses a pointer to an array. */
int find_max_v1(const int *arp, int n)
{
	int max = *arp; // initialize max to first element in array
	if (n <= 0)
	{
		return 0; // ensure we proceed only if n is reasonable
	}

	for (int i = 1; i < n; i++) // iterate through n elements of array
	{
		if (*(arp + i) > max) // if a[i] (or the i'th element of the array as indicated by the pointer) is greater than max, replace value of max with it
		{
			max = *(arp + i);
		}
	}

	return max; // return max value of n elements in array
}

/* Return the maximum value in the first n elements of an array of integers.
   If n is less than or equal to 0, it returns 0.
   This function uses a walking pointer to the array. */
int find_max_v2(const int *arp, int n)
{
	const int *p = arp; // initialize pointer to first element of array
	int max = *p;		// initialize max with the first element

	if (n <= 0)
	{
		return 0; // ensure we proceed only if n is reasonable
	}
	for (p = arp + 1; p < arp + n; p++) // walk the pointer through the array
	{
		if (*p > max) // if a[i] (or the i'th element of the array as indicated by walking pointer) is greater than max, replace value of max with it
		{
			max = *p;
		}
	}
	return max; // return max value of n elements in array
}

// Exercise 2
/* Return the count of the number of times target occurs in the first
 * n elements of array a.
 */
int count_in_array(int a[], int n, int target)
{
	if (n == 0) // if no elements to interate through, no target will be reached so return 0
	{
		return 0;
	}

	if (a[0] == target) // if the base element of the array of n values is equal to the target...
	{
		return (1 + count_in_array(a + 1, n - 1, target)); // update number of target values reached and call function again to reassess next elements
	}
	else
	{
		return count_in_array(a + 1, n - 1, target); // go through function again and check next element by moving to next element of array and decrementing the n values left to check.
	}
}

// Exercise 3
/* Return true if the first n elements in arr1 and arr2 are equal
and return false otherwise*/
_Bool array_compare(int arr1[], int arr2[], int n)
{
	if (n == 0) // if no more elements left to iterate through to check equality, return true to indicate equality
	{
		return 1;
	}
	if (arr1[0] == arr2[0]) // if the base element of the array of n values is equal to the target...
	{
		return array_compare(arr1 + 1, arr2 + 1, n - 1); // call recursive function to continue to check next elements of array for equality by moving to next element of array and decrementing the n values left to check.
	}
	else
	{
		return 0; // if arrays are different and not equal, return false to user
	}
	return 0;
}