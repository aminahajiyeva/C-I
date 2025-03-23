/* SYSC 2006 Lab 8
 *
 * array_list.c
 *
 * A dynamically allocated, fixed-capacity list collection that supports a subset of the
 * operations provided by Python's list type.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "array_list.h"

/* Construct a new, empty list, and return a pointer to it
 * Parameter capacity is the # of elements that can be stored in the list.
 *
 * Terminate the program via assert if capacity is <= 0.
 * Terminate the program via assert if memory for the list cannot be
 * allocated from the heap.
 */
list_t *list_construct(int capacity)
{
    assert(capacity > 0); // function terminates via assert if capacity is less then or equal to 0

    // allocate two blocks of memory from heap
    // allocate memory for struct
    list_t *list = (list_t *)malloc(sizeof(list_t));
    assert(list != NULL); // function terminates via assert if memory cannot be allocated for struct

    // allocate memory for array
    list->elems = (int *)malloc(capacity * sizeof(int));
    assert(list->elems != NULL); // function terminates via assert if memory cannot be allocated for array

    // initialize members of list with default values or given values
    list->capacity = capacity;
    list->size = 0;

    return list; // return list
}

/* Destroy the list pointed to by parameter list, deallocating all memory
 * that was allocated from the heap.
 *
 * Terminate the program via assert if list is NULL.
 */
void list_destroy(list_t *list)
{
    assert(list != NULL);
    free(list->elems); /* Return the array to the heap. */
    free(list);        /* Return the structure to the heap. */
}

/* Print the list pointed to by parameter list on the console.
 *
 * Terminate the program via assert if list is NULL.
 * Terminate the program via assert if the pointer to the list's backing array is NULL.
 * Terminate the program via assert if the list's capacity and size are invalid.
 */
void list_print(const list_t *list)
{
    assert(list != NULL);
    assert(list->elems != NULL);
    assert(list->capacity > 0 && list->size >= 0 && list->size <= list->capacity);

    printf("[");
    int n = list->size;
    if (n > 0)
    {
        /* Print all the array elements, with a leading space before
         * all but the first element.
         */
        printf("%d", list->elems[0]);

        for (int i = 1; i < n; i += 1)
        {
            printf(" %d", list->elems[i]);
        }
    }
    printf("]");
    printf(", capacity: %d, size: %d\n", list->capacity, list->size);
}

/* Insert element at the end of the list pointed to by list.
 * Return true if element is appended; otherwise return false
 * (which indicates that the list is full.)
 *
 * Terminate the program via assert if list is NULL.
 */
_Bool list_append(list_t *list, int element)
{
    assert(list != NULL); // function terminates via assert if parameter list is NULL

    if (list->size >= list->capacity) // if the size (current number of index) of the list exceeds its capacity (max number of index's), the list is full, therefore return false
        return false;

    // if list is not full, return true and append element to list
    list->elems[list->size] = element; // access the next available index in the array
    list->size++;                      // increment size of list to indicate new appended addition
    return true;                       // return true to indicate appending of element
}

/* Return the maximum number of integers that can be stored in the list
 * pointed to by parameter list.
 *
 * Terminate the program via assert if list is NULL.
 */
int list_capacity(const list_t *list)
{
    assert(list != NULL);  // function terminates via assert if parameter list is NULL
    return list->capacity; // return capacity of list
}

/* Return the number of integers in the list pointed to by parameter list.
 *
 * Terminate the program via assert if list is NULL.
 */
int list_size(const list_t *list)
{
    assert(list != NULL); // function terminates via assert if parameter list is NULLL
    return list->size;    // return size of list
}

/* Return the element located at the specified index, in the list
 * pointed to by parameter list.
 *
 * Terminate the program via assert if list is NULL,
 * or if index is not in the range 0 .. list_size() - 1.
 */
int list_get(const list_t *list, int index)
{
    assert(list != NULL);                     // function terminates via assert if parameter list is NULL
    assert(index >= 0 && index < list->size); // if index exceeds range of list, function terminates via assert
    return list->elems[index];                // return element of list located at specific index
}

/* Store element at the specified index, in the list pointed to by
 * parameter list. Return the integer that was previously
 * stored at that index.
 *
 * Terminate the program via assert if list is NULL,
 * or if index is not in the range 0 .. list_size() - 1.
 */
int list_set(list_t *list, int index, int element)
{
    assert(list != NULL);                     // function terminates via assert if parameter list is NULL
    assert(index >= 0 && index < list->size); // if index exceeds range of list, function terminates via assert
    int num = list->elems[index];             // determine previous value by accessing it and storing it in a variable for later use
    list->elems[index] = element;             // update specific index with new element
    return num;                               // return previously stored value
}

/* Empty the list pointed to by parameter list.
 * Memory allocated to the list is not freed, so the emptied list can
 * continue to be used.
 *
 * Terminate the program via assert if list is NULL.
 */
void list_removeall(list_t *list)
{
    assert(list != NULL); // function terminates via assert if parameter list is NULL
    list->size = 0;       // empty list
}

/* Return the index (position) of the first occurrence of an integer
 * equal to target in the list pointed to by parameter list.
 * Return -1 if target is not in the list.
 *
 * Terminate the program via assert if list is NULL.
 */
int list_index(const list_t *list, int target)
{
    assert(list != NULL); // function terminates via assert if parameter list is NULL

    for (int i = 0; i < list->size; i++) // iterate through each index of the array
    {
        if (list->elems[i] == target) // determine if index of array contains target
            return i;                 // return index at which target is located
    }

    return -1; // return -1 if target is not found in the list
}

/* Count the number of integers that are equal to target, in the list
 * pointed to by parameter list, and return that number.
 *
 * Terminate the program via assert if list is NULL.
 */
int list_count(const list_t *list, int target)
{
    int count = 0;        // initialize variable to hold number of integers that are equal to the target that are found in the array
    assert(list != NULL); // function terminates via assert if parameter list is NULL

    for (int i = 0; i < list->size; i++) // iterate through each index of the array
    {
        if (list->elems[i] == target) // determine if index of array contains target
            count++;                  // if found, increment count to indicate one more target was found
    }

    return count; // return the number of times the target integer was found in the array
}

/* Determine if an integer in the list pointed to by parameter list
 * is equal to target.
 * Return true if target is in the list, otherwise return false.
 *
 * Terminate the program via assert if list is NULL.
 */
_Bool list_contains(const list_t *list, int target)
{
    assert(list != NULL); // function terminates via assert if parameter list is NULL

    for (int i = 0; i < list->size; i++) // iterate through each index of the array
    {
        if (list->elems[i] == target) // determine if index of array contains target
            return true;              // if found, return true to indicate the target was found
    }

    return false; // return false if the target was not found in the array
}
