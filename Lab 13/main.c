/* SYSC 2006 - Lab 13 - demonstrate ADT dictionary/map.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

int main(void)
{
    printf("Creating a dictionary of names & email addresses\n");
    dict_t *addresses = make_dictionary();

    printf("Adding key: %s, value: %s\n", "Lynn", "lynn.marshall@carleton.ca");
    put(addresses, "Lynn", "lynn.marshall@carleton.ca");

    // Multiple keys can be associated with the duplicate values
    printf("Adding key: %s, value: %s\n", "Don", "donald.bailey@carleton.ca");
    put(addresses, "Don", "donald.bailey@carleton.ca");
    printf("Adding key: %s, value: %s\n", "Donald", "donald.bailey@carleton.ca");
    put(addresses, "Donald", "donald.bailey@carleton.ca");

    printf("Adding key: %s, value: %s\n", "Babak", "babak.esfandiari@carleton.ca");
    put(addresses, "Babak", "babak.esfandiari@carleton.ca");
    printf("Adding key: %s, value: %s\n", "Greg", "gregory.franks@carleton.ca");
    put(addresses, "Greg", "gregory.franks@carleton.ca");
    printf("Adding key: %s, value: %s\n", "Jason", "jason.jaskolka@carleton.ca");
    put(addresses, "Jason", "jason.jaskolka@carleton.ca");

    printf("Email for Babak is %s\n", get(addresses, "Babak"));
    printf("Email for Lynn is %s\n", get(addresses, "Lynn"));
    printf("Email for Jason is %s\n", get(addresses, "Jason"));
    printf("Email for Don is %s\n", get(addresses, "Don"));
    printf("Email for Donald is %s\n", get(addresses, "Donald"));
    printf("Email for Greg is %s\n", get(addresses, "Greg"));

    printf("Changing %s to %s\n", "Babak", "babak@sce.carleton.ca");
    put(addresses, "Babak", "babak@sce.carleton.ca");
    printf("Email for Babak is now %s\n", get(addresses, "Babak"));


//--------------------------------------------------------------------------------------

    // test excerisce 1, print dictionary
    printf("\n\nPrinting for Testing Exersice 1: \n");
    print_dictionary(addresses);

    // test excersice 2
    // test when name IS in dictionary
    _Bool excersice_2 = replace(addresses, "Babak", "test_exercise_2");
    printf("\n\nTesting Excersice 2, name IS in dictionary: ");
    if (excersice_2 == 1)
        printf("TRUE\n");
    else
        printf("FALSE\n");
    // test when name IS NOT in dictionary
    _Bool excersice_2_2 = replace(addresses, "Hi", "gregory.franks@carleton.ca");
    printf("\nTesting Excersice 2, name is NOT in dictionary: ");

    if (excersice_2_2 == 1)
        printf("TRUE\n\n");
    else
        printf("FALSE\n\n");

    // print new dictionary after testing excersice 2
    printf("Printing for Testing Exersice 2 Updated: \n");

    print_dictionary(addresses);

    // test excersice 3 by printing dictionary after running it
    clear(addresses);
    printf("\n\nPrinting for Testing Exersice 3: \n");
    print_dictionary(addresses);

    // indicate to user all testing is done
    printf("\n\nAll testing complete.\n\n");

    return EXIT_SUCCESS;
}
