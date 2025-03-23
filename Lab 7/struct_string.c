#include "struct_string.h"
#include <stdlib.h> // abs(x)
#include <stdio.h>  // printf

// Exercise 1
/* Print fraction pointed to by pf in the form a/b. */
void print_fraction(const fraction_t *pf)
{
   printf("%d/%d", pf->num, pf->den);
}

/* Return the greatest common divisor of integers a and b;
   i.e., return the largest positive integer that evenly divides
   both values.  Copy this function from Lab 6.  No changes are needed.
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

/* Updates the fraction pointed to by pf to its reduced form.

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
void reduce(fraction_t *pf)
{
   if (pf->num == 0) // if numerator is 0, as per given coniditions, set denominator to 1
      pf->den = 1;

   int div = gcd(pf->num, pf->den); // determine the gcd of the given fraction

   pf->num = pf->num / div; // use the gcd to find the reduced fraction numerator
   pf->den = pf->den / div; // use the gcd to find the recuced fraction denominator

   if (pf->den < 0) // if the denominator of the fraction is negative, as per propert notation, make the numerator positive instead - unless the numerator is already negative too, then make both positive.
   {
      pf->num *= -1;
      pf->den *= -1;
   }
}

/* Returns a pointer to a fraction (by reference) with numerator a and denominator b.
   Print an error message and terminate the calling program via exit()
   if the denominator is 0.
   The fraction returned by this function is always in reduced form.
*/
void make_fraction(int a, int b, fraction_t *pf)
{
   fraction_t f = {a, b}; // populate the fraction with its numerator and denominator

   pf->num = a; // populate pf with its values for numerator and denominator
   pf->den = b;

   if (pf->den == 0) // if the denominator is 0, exit the function
   {
      printf("ERROR: denominator == 0");
      exit(1);
   }
   else // otherwise reduce the fraction
      reduce(pf);
}

/* Returns by reference a pointer to the sum of fractions pointed to by pf1 and pf2.
   The fraction returned by this function is always in reduced form
 */
void add_fractions(const fraction_t *pf1, const fraction_t *pf2, fraction_t *psum)
{
   psum->num = (pf1->num * pf2->den) + (pf1->den * pf2->num); // populate the sum of the two fractions with the numerator and denominator values
   psum->den = (pf1->den * pf2->den);
   reduce(psum); // reduce fraction
}

/* Returns by reference a pointer to the product of fractions pointed to by pf1 and pf2.
   The fraction returned by this function is always in reduced form
 */
void multiply_fractions(const fraction_t *pf1, const fraction_t *pf2, fraction_t *pprod)
{
   pprod->num = (pf1->num * pf2->num); // populate the product of the two fractions with the numerator and denominator values
   pprod->den = (pf1->den * pf2->den);
   reduce(pprod); // reduce fraction
}

// Exercise 2

/* Update the GPA of the student pointed to by studentp, assuming the student has numGrades.	Note that update_gpa must call calc_gpa for each student. */
void update_gpa(student_t *studentp, int numGrades)
{
   studentp->gpa = calc_gpa(studentp->grades, numGrades); // update gpa
}

/* Calculate the GPA associated with the numGrades pointed to by gradesp.
   The implementation must use a walking pointer.
   If the total weight of all courses is 0, a GPA of 0 is returned. */
float calc_gpa(const grade_t *gradesp, int numGrades)
{
   float gpa = 0.0; // declare and populate default values for variables to be used later on
   float weight = 0;
   const grade_t *p = gradesp;

   for (int i = 0; i < numGrades; i++, p++) // iterate with walking pointer through each student
   {
      gpa += (p->gp) * (p->weight); // calculate total gpa of student
      weight += p->weight;          // calculate total weight of student
   }

   if (weight > 0) // if gpa has weight, return value
      return gpa / weight;
   else // if gpa has no weight, return 0
      return 0.0;
}

// Exercise 3

/* Calculate how many time the target character appears in string my_str
For example:
count_char("Hello world ",'l') return 3
count_char("Hello world ",'a') return 0
Your implementation must use array-indexing.
*/

int count_char(const char *my_str, char target)
{
   int count = 0; // declare and populate variable to hold number of char's found in string

   for (int i = 0; my_str[i] != '\0'; i++) // iterate through each letter, or index, of the string
   {
      if (my_str[i] == target) // if the target char is found within the index of the string, increase count by one to show that
         count++;
   }

   return count; // return count
}

// Exercise 4

/* Calculate how many time the target character appears in string my_str
For example:
count_char("Hello world ",'l') return 3
count_char("Hello world ",'a') return 0
Your implementation must use walking pointer.
*/

int count_char_wp(const char *my_str, char target)
{
   int count = 0; // declare and populate variable to hold number of char's found in string

   for (const char *p = my_str; *p != '\0'; p++) // iterate through each letter of the string by pointing to it, using a walking pointer
   {
      if (*p == target) // if the target char is found at the pointer, increase count by one to show that
         count++;
   }

   return count; // return count
}