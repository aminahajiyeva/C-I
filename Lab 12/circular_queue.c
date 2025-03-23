/* SYSC 2006 Lab 12
 *
 * circular_queue.c - circular linked-list implementation of a queue.
 */

#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "circular_queue.h"

/* Return a pointer to a new, empty queue.
 * Terminate (via assert) if memory for the queue cannot be allocated.
 */
queue_t *alloc_queue(void)
{
    queue_t *queue = malloc(sizeof(queue_t));
    assert(queue != NULL);

    queue->rear = NULL;
    queue->size = 0;
    return queue;
}

/* Return true if the specified queue contains no elements;
 * otherwise return false.
 * Parameter queue points to the queue.
 * Terminate (via assert) if queue is NULL.
 */
_Bool queue_is_empty(const queue_t *queue)
{
    assert(queue != NULL);
    return queue->size == 0;
}

/* Return the number of elements stored in the specified queue.
 * Parameter queue points to the queue.
 * Terminate (via assert) if queue is NULL.
 */
int queue_size(const queue_t *queue)
{
    assert(queue != NULL);
    return queue->size;
}

/* Print the contents of the specified queue to the console,
 * from front to rear: [value0, value1, value3, ...]
 * Parameter queue points to the queue.
 * Terminate (via assert) if queue is NULL.
 */
void queue_print(const queue_t *queue)
{
    assert(queue != NULL);

    if (queue_is_empty(queue))
    { // Handle an empty queue (no nodes).
        printf("[]");
        return;
    }

    node_t *current;

    printf("[");

    /* Print all the elements in the queue, except for the one at the rear. */
    for (current = queue->rear->next; // queue->rear points to the tail node
                                      // (the node at the rear of the queue).
                                      // The tail node points to the head node
                                      // (the node at the front of the queue).
         current != queue->rear;
         current = current->next)
    {
        printf("%d, ", current->data);
    }

    /* Now print the element at the rear of the queue. */
    printf("%d]", current->data);
}

/*--------------------------------------------------------
 *
 * Solutions to Lab 12 exercises.
 */

/* Enqueue the specified value to the rear of a queue.
 * Parameter queue points to the queue.
 * Terminate (via assert) if queue is NULL.
 */
void enqueue(queue_t *queue, int value)
{
    // Assert that the queue is not NULL
    assert(queue != NULL);

    // Create a new node with the given value
    node_t *new_node = malloc(sizeof(node_t));
    assert(new_node != NULL); // Ensure memory allocation is successful
    new_node->data = value;

    // Case 1: The queue is empty
    if (queue->size == 0)
    {
        new_node->next = new_node; // Circular: points to itself
        queue->rear = new_node;    // Rear points to the new node
    }
    else
    {
        // Case 2: The queue is not empty
        new_node->next = queue->rear->next; // Points to the front node
        queue->rear->next = new_node;       // Rear points to the new node
        queue->rear = new_node;             // Update rear to the new node
    }

    // Increment the size of the queue
    queue->size++;
}

/* Copy the value at the front of a queue to the variable pointed to by
 * parameter element, and return true.
 * Return false if the queue is empty.
 * Parameter queue points to the queue.
 * Terminate (via assert) if queue is NULL.
 */
_Bool front(const queue_t *queue, int *element)
{
    // Ensure the queue is not NULL
    assert(queue != NULL);

    // If the queue is empty, return false
    if (queue->size == 0)
    {
        return false;
    }

    // Copy the value at the front (queue->rear->next) to element
    *element = queue->rear->next->data;

    // Return true indicating success
    return true;
}

/* Copy the value at the front of a queue to the variable pointed to by
 * parameter element, remove that value from the queue, and return true.
 * Return false if the queue is empty.
 * Parameter queue points to the queue.
 * Terminate (via assert) if queue is NULL.
 */
_Bool dequeue(queue_t *queue, int *element)
{
    // Ensure the queue is valid
    assert(queue != NULL);

    // If the queue is empty, return false
    if (queue->size == 0)
    {
        return false;
    }

    // Save the front node
    node_t *front_node = queue->rear->next;

    // Copy the value of the front node to *element
    *element = front_node->data;

    // Case 1: Only one element in the queue
    if (queue->size == 1)
    {
        // Free the node and set rear to NULL
        free(front_node);
        queue->rear = NULL;
    }
    else
    {
        // Case 2: Two or more elements in the queue
        queue->rear->next = front_node->next; // Adjust rear's next pointer
        free(front_node);                     // Free the front node
    }

    // Decrement the size of the queue
    queue->size--;

    // Indicate successful dequeue
    return true;
}
