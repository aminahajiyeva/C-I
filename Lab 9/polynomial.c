/* polynomial.c - SYSC 2006 Lab 9 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include "polynomial.h"

/* Print a polynomial term in the form ax^n; for example,
 * a term with coefficient 4 and exponent 5 is printed as 4x^5.
 */
void print_term(term_t *term)
{
    printf("%dx^%d", term->coeff, term->exp); // print terms with required format
}

/* Make a polynomial term with coefficient coeff and exponent exp
 * and return the pointer to the term.
 *
 * Memory for the term is allocated from the heap.
 *
 * Terminate the program via assert if:
 * (1) coeff is 0;
 * (2) malloc fails.
 */
term_t *make_term(int coeff, int exp)
{
    term_t *term = malloc(sizeof(term_t)); // allocate memory for a term_t structure

    // populate with coefficient and exponent values
    term->coeff = coeff;
    term->exp = exp;

    return term; // return pointer to created term
}

/* Return the value of a polynomial term; i.e., return ax^n for a term with
 * coefficient a and exponent n when evaluated at x.
 * Example: if a term has coefficient 3 and exponent 2 and x is 4.0,
 * this function returns 3(4.0^2), which is 48.0.
 */
double eval_term(term_t *term, double x)
{
    return term->coeff * pow(x, term->exp); // determine and return ax^n
}

/* Make a polynomial that has 0 terms and return the pointer to the polynomial.
 * The polynomial can store up to MAX_TERMS terms (see polynomial.h).
 *
 * Memory for the polynomial is allocated from the heap.
 *
 * Terminate the program via assert if malloc fails.
 */
polynomial_t *make_polynomial(void)
{
    polynomial_t *polynomial = malloc(sizeof(polynomial_t)); // allocate memory for a polynomial_t structure

    polynomial->num_terms = 0; // initialize with default value of zero terms

    for (int i = 0; i < MAX_TERMS; i++) // iterate through all terms of polynomial
    {
        polynomial->terms[i] = NULL; // set all terms to null
    }

    return polynomial; // return pointer to poly
}

/* Add a term to a polynomial.
 *
 * This function doesn't check if the polynomial already contains a term with the
 * same exponent as the term being added; in other words, it's the caller's
 * reponsibility to ensure that the polynomial doesn't have terms with duplicate
 * exponents.
 *
 * Terminate the program via assert if there's no room in the polynomial for
 * additional terms.
 */
void add_term(polynomial_t *poly, term_t *term)
{
    poly->terms[poly->num_terms] = term; // add term to polynomial

    poly->num_terms++; // increase number of terms to indicate new addition
}

/* Return the value of a polynomial when it is evaluated at x.
 *
 * Terminate the program via assert if the polynomial has 0 terms.
 */
double eval_polynomial(polynomial_t *poly, double x)
{
    double result = 0.0; // declare variable to hold sum and initialize with default variable

    for (int i = 0; i < poly->num_terms; i++) // iterate through each term of poly
    {
        result += eval_term(poly->terms[i], x); // sum values of each term in poly
    }

    return result; // return sum of values
}
