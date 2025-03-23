/* fraction.c - SYSC 2006 Lab 6 */

#include <stdlib.h> // abs(x)
#include <stdio.h>  // printf

#include "fraction.h"

/* Print fraction f in the form a/b. */
void print_fraction(fraction_t f)
{
   printf("%d/%d", f.num, f.den); // print each individual member of the structure, add a "/" for the correct fraction notation
}

/* Return the greatest common divisor of integers a and b;
   i.e., return the largest positive integer that evenly divides
   both values.
*/
int gcd(int a, int b)
{
   /* Euclid's algorithm, using iteration and calculation of remainders. */
   int q, p, r;
   if (a < 0) // if a is a negative value, multiply it by -1 to get its positive equivalent and store it in q
      q = a * -1;
   else // if a is not negative, store it in q without any further operations
      q = a;

   if (b < 0) // if b is a negative value, multiply it by -1 to get its positive equivalent and store it in p
      p = b * -1;
   else // if b is not negative, store it in p without any further operations
      p = b;

   r = q % p; // calculate the remainder and store in r

   while (r != 0) // follow Euclid's algorithm and continue finding the gcd until the remainder is 0
   {
      q = p;     // copy p into q
      p = r;     // copy r into p
      r = q % p; // update the remainder
   }

   return p; // return the gcd
}

/* Return the reduced form of fraction f.

   This means that:
   (1) if the numerator is equal to 0 the denominator is always 1.
   (2) if the numerator is not equal to 0 the denominator is always
      positive, and the numerator and denominator have no common
      divisors other than 1.

   In other words,
   (1) if the numerator is 0 the denominator is always changed to 1.
   (2) if the numerator and denominator are both negative, both values
      are made positive, or if the numerator is positive and the
      denominator is negative, the numerator is made negative and the
      denominator is made positive.
   (3) the numerator and denominator are both divided by their greatest
      common divisor.
*/
fraction_t reduce(fraction_t f)
{
   if (f.num == 0) // if numerator is 0, as per given coniditions, set denominator to 1
      f.den = 1;

   int div = gcd(f.num, f.den); // determine the gcd of the given fraction

   f.num = f.num / div; // use the gcd to find the reduced fraction numerator
   f.den = f.den / div; // use the gcd to find the recuced fraction denominator

   if (f.den < 0) // if the denominator of the fraction is negative, as per propert notation, make the numerator positive instead - unless the numerator is already negative too, then make both positive.
   {
      f.num *= -1;
      f.den *= -1;
   }

   return f; // return reduced fraction
}

/* Return a fraction with numerator a and denominator b.
   Print an error message and terminate the calling program via exit()
   if the denominator is 0.
   The fraction returned by this function is always in reduced form
   (see documentation for reduce).
*/
fraction_t make_fraction(int a, int b)
{
   fraction_t f = {a, b}; // populate the fraction with its numerator and denominator

   if (f.den == 0)
   {
      printf("ERROR --- Program Terminated: denominator == 0");
      exit(1);
   }
   else
      return reduce(f); // return its reduced form
}

/* Return the sum of fractions f1 and f2.
   The fraction returned by this function is always in reduced form
   (see documentation for reduce).
 */
fraction_t add_fractions(fraction_t f1, fraction_t f2)
{
   fraction_t fsum = {(f1.num * f2.den) + (f1.den * f2.num), (f1.den * f2.den)}; // populate the sum of the two fractions with the numerator and denominator values

   return make_fraction(fsum.num, fsum.den); // return reduced fraction
}

/* Return the product of fractions f1 and f2.
   The fraction returned by this function is always in reduced form
   (see documentation for reduce).
 */
fraction_t multiply_fractions(fraction_t f1, fraction_t f2)
{
   fraction_t fprod = {(f1.num * f2.num), (f1.den * f2.den)}; // populate the product of the two fractions with the numerator and denominator values
   return make_fraction(fprod.num, fprod.den);                // return reduced fraction
}
