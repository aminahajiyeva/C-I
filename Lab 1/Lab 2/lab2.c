// SYSC 2006 - Lab 2 Solution template

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> // Include the necessary header for _Bool
#include "lab2.h"

/* Replace these lines with your information */
const char *author = "Amina Hajiyeva";
const char *student_number = "101303729";

// Type your solution to exercise 1 inside the body of the function. You need to update the return statement
/* This function calculates the alarm time based on whether it’s a weekday or weekend and whether the person is on vacation. Returns: -1 if it's a weekend and vacation
(no alarm needed), 10 if it's a weekend (non-vacation),7 if it's a weekday and non-vacation, or 10 if it's a weekday but vacation. */
int alarm_clock(int day, _Bool vacation)
{
  if (vacation) // Check if vacation
  {
    if (day == 0 || day == 6) // Check for weekend (Saturday/Sunday)
    {
      return -1; // No alarm on weekends during vacation
    }
    else
    {
      return 10; // Alarm at 10 AM on weekdays during vacation
    }
  }
  else
  {
    if (0 < day && day < 6) // Check for weekdays
    {
      return 7; // Alarm at 7 AM on weekdays when not on vacation
    }
    else
    {
      return 10; // Alarm at 10 AM on weekends when not on vacation
    }
  }
  return 1; // Default case return
}

// Type your solution to exercise 2 inside the body of the function.
/* This function prints numbers from 0 to a user-provided integer, but replaces numbers divisible by 3 with "Fizz", numbers divisible by 5 with "Buzz", and numbers divisible by
both with "FizzBuzz". */
void count_replace(int value)
{
  for (int i = 1; i <= value; i++) // Loop from 0 to num (inclusive)
  {
    if (i % 3 == 0 && i % 5 == 0) // Divisible by both 3 and 5
    {
      printf("FizzBuzz "); // Replace multiples of 3 and 5 with "FizzBuzz"
    }
    else if (i % 3 == 0) // Divisible by 3
    {
      printf("Fizz "); // Replace multiples of 3 with "Fizz"
    }
    else if (i % 5 == 0) // Divisible by 5
    {
      printf("Buzz "); // Replace multiples of 5 with "Buzz"
    }
    else // If number not divisible by 3 or 5
    {
      printf("%d ", i); // Otherwise, print the number itself
    }
  }
}

// Type your solution to exercise 3 inside the body of the function. You need to update the return statement
/* This function checks whether a given integer is prime. Returns: true if the number is prime, false otherwise.*/
_Bool is_prime(int value)
{
  if (value < 2) // Prime numbers are greater than 1
  {
    return false;
  }

  for (int i = 2; i < value; i++) // Loop through numbers less than the value
  {
    if (value % i == 0) // If divisible by any number, it's not prime

    {
      return false;
    }
  }
  return true; // If no divisors found, the number is prime
}
// Type your solution to exercise 4 inside the body of the function. You need to update the return statement
/* This function returns the sum of all even numbers from 1 to the given value. Returns: The sum of all even numbers from 1 to value. */
int sum_even(int value)
{
  int total_sum = 0;
  for (int i = 1; i <= value; i++) // Loop through numbers from 1 to the user's given value
  {
    if (i % 2 == 0) // Check if the number is even
    {
      total_sum += i; // Add the even number to the total sum
    }
  }
  return total_sum; // Return the total sum of even numbers
}