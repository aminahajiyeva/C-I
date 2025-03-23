#include <assert.h>
#include <stdlib.h>

int *intlist_take(intlist_t *list, int n)
{
    // Assert that the list is not NULL
    assert(list != NULL);

    // Assert that n is positive
    assert(n > 0);

    // Assert that the list contains at least n elements
    assert(list->size >= n);

    // Allocate a new array to hold the first n elements
    int *taken_elements = malloc(n * sizeof(int));
    assert(taken_elements != NULL); // Ensure malloc succeeded

    // Copy the first n elements from the list to the new array
    for (int i = 0; i < n; i++)
    {
        taken_elements[i] = list->elems[i];
    }

    // Shift the remaining elements in the list
    for (int i = n; i < list->size; i++)
    {
        list->elems[i - n] = list->elems[i];
    }

    // Update the size of the list
    list->size -= n;

    // Return the new array
    return taken_elements;
}

_Bool intlist_push(intlist_t *lst, int x)
{
    assert(lst != NULL);

    if (lst->size >= lst->capacity)
    {
        int cap = lst->capacity + 5;
        int *new = realloc(lst->elems, cap * sizeof(int));
        if (new == NULL)
            return false;

        lst->elems = new;
        lst->capacity = cap;
    }

    for (int i = lst->size; i > 0; i--)
    {
        lst->elems[i] = lst->elems[i - 1];
    }
    
    lst->elems[0] = x;
    lst->size++;
    return true;
}
