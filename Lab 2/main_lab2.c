// SYSC 2006 - Lab 2 Template

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // Include the necessary header for _Bool
#include "lab2.h"

/* Replace these lines with your information */
const char *author_main = "Amina Hajiyeva";
const char *student_number_main = "101303729";

int main(void)
{
  // Tests exercise 1 - Complete for a comprehensive test harness
  /* Tests for Exercise 1 - alarm_clock function. This part tests both vacation and non-vacation scenarios for weekdays and weekends. It checks the returned alarm time against expected values and prints test
  results. */
  // Test for non vacation weekdays
  int expected_week_non_vac = 7;
  for (int day = 1; day <= 5; day++)
  {
    int alarm_time = alarm_clock(day, false);
    if (alarm_time == expected_week_non_vac)
    {
      printf("Day %d, Non vacation: TEST PASS.\n", day);
    }
    else
    {
      printf("Day %d, Non vacation: TEST FAIL.\n", day);
    }
  }
  // Test for vacation weekday
  int expected_week_vac = 10;
  for (int day = 1; day <= 5; day++) // Looping through weekdays (Monday to Friday)
  {
    int alarm_time = alarm_clock(day, true); // Vacation case
    if (alarm_time == expected_week_vac)     // Check if the alarm time matches the expected alarm time
    {
      printf("Day %d, Non vacation: TEST PASS.\n", day); // If test is passed and output is correct, inform user
    }
    else
    {
      printf("Day %d, Non vacation: TEST FAIL.\n", day); // If test is NOT passed and output is NOT correct, inform user
    }
  }

  // Test for non vacation weekends
  int expected_weekend_non_vac = 10;    // On weekends, the alarm should ring at 10 AM for non-vacation
  for (int day = 0; day <= 6; day += 6) // Testing Sunday (0) and Saturday (6)
  {
    int alarm_time = alarm_clock(day, false);   // Non Vacation case
    if (alarm_time == expected_weekend_non_vac) // Check if the alarm time matches the expected alarm time
    {
      printf("Day %d, Non vacation: TEST PASS.\n", day); // If test is passed and output is correct, inform user
    }
    else
    {
      printf("Day %d, Non vacation: TEST FAIL.\n", day); // If test is NOT passed and output is NOT correct, inform user
    }
  }

  // Test for vacation weekends
  int expected_weekend_vac = -1;        // No alarm should ring during vacation weekends
  for (int day = 0; day <= 6; day += 6) // Testing Sunday (0) and Saturday (6)
  {
    int alarm_time = alarm_clock(day, true); // Vacation case
    if (alarm_time == expected_weekend_vac)  // Check if the alarm time matches the expected alarm time
    {
      printf("Day %d, Non vacation: TEST PASS.\n", day); // If test is passed and output is correct, inform user
    }
    else
    {
      printf("Day %d, Non vacation: TEST FAIL.\n", day); // If test is NOT passed and output is NOT correct, inform user
    }
  }

  // Type your test cases for exercise 2. Make sure to include border line cases
  /* Tests for Exercise 2 - count_replace function.The function is tested with various input values to check the correct replacement of numbers with "Fizz", "Buzz", or "FizzBuzz". */

  // Border case (no multiples of 3 or 5 and small integer.)
  printf("Test Case 1: Input = 1\nActual Output:");
  count_replace(1);
  printf("\nExpected Output: 1\n");

  // Border case (first integer to contain multiples of 3 and multiples of 5.)
  printf("Test Case 2: Input = 7\nActual Output:");
  count_replace(7);
  printf("\nExpected:     1 2 Fizz 4 Buzz Fizz 7\n");

  // Border case (Integer contains multiples of 3 and multiples of 5 and multiples of both 3 and 5.)
  printf("Test Case 3: Input = 16\nActual Output:");
  count_replace(16);
  printf("\nExpected:     1 2 Fizz 4 Buzz Fizz 7 8 Fizz Buzz 11 Fizz 13 14 FizzBuzz 16\n");

  // Type your test cases for exercise 3. Make sure to include border line cases
  /* Tests for Exercise 3 - is_prime function. Tests the function with known prime and non-prime numbers. Includes border cases like 1. */
  if ((is_prime(7) == 1) && (is_prime(1) == 0) && (is_prime(101) == 1)) // Check if test cases match expected output
  {
    printf("TEST PASS for isPrime()\n"); // If test is passed and output is correct, inform user
  }
  else
  {
    printf("TEST FAIL for isPrime()\n"); // If test is NOT passed and output is NOT correct, inform user
  }

  // Type your test cases for exercise 4. Make sure to include border line cases
  /* Tests for Exercise 4 - sum_even function. The function is tested with different input values to ensure correct summation of even numbers. */
  if ((sum_even(1) == 0) && (sum_even(9999) == 24995000) && (sum_even(2) == 2)) // Check if test cases match expected output
  {
    printf("TEST PASS for sum_even()\n"); // If test is passed and output is correct, inform user
  }
  else
  {
    printf("TEST FAIL for sum_even()\n"); // If test is NOT passed and output is NOT correct, inform user
  }

  printf("Test harness finished\n");
  return EXIT_SUCCESS;
}