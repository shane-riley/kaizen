/* 
 * Developed by R. E. Bryant, 2017
 * Extended to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
  queue_t *q = malloc(sizeof(queue_t));
  if (q == NULL) return NULL;
  q->head = NULL;
  q->tail = NULL;
  q->size = 0;

  return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
  /* How about freeing the list elements and the strings? */
  /* Free queue structure */

  // Null check
  if (q == NULL) return;

  // Loop through elements, freeing along the way
  list_ele_t *element = q->head;
  list_ele_t *next_element;
  // While element pointer is not null, get the next value and free the previous
  while (element != NULL) {

    // Get next elem
    next_element = element->next;

    // Free this elem
    free(element->value);
    free(element);

    // Iterate
    element = next_element;
  }

  free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
  // Null check
  if (q == NULL) return false;

  // Count string size
  char *sp = s;
  int count = 0;
  while (*(sp+count) != '\0') count++;
  count++;

  // Allocate
  list_ele_t *ele = malloc(sizeof(list_ele_t));
  if (ele == NULL) return false;
  ele->value = malloc(sizeof(char) * count);
  if (ele->value == NULL) {
    free(ele);
    return false;
  }

  // Write string
  int i;
  for (i = 0; i < count; i++) {
    ele->value[i] = s[i];
  }

  // Place element
  if (q->head == NULL) {
    q->head = ele;
    q->tail = ele;
    ele->next = NULL;
  } else {
    list_ele_t *old_head = q->head;
    q->head = ele;
    ele->next = old_head;
  }
  q->size++;
  return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
  // Null check
  if (q == NULL) return false;

  // Count string size
  char *sp = s;
  int count = 0;
  while (*(sp+count) != '\0') count++;
  count++;

  // Allocate
  list_ele_t *ele = malloc(sizeof(list_ele_t));
  if (ele == NULL) return false;
  ele->value = malloc(sizeof(char) * count);
  if (ele->value == NULL) {
    free(ele);
    return false;
  }

  // Write string
  int i;
  for (i = 0; i < count; i++) {
    ele->value[i] = s[i];
  }

  // Place element
  if (q->tail == NULL) {
    q->head = ele;
    q->tail = ele;
    ele->next = NULL;
  } else {
    q->tail->next = ele;
    q->tail = ele;
    ele->next = NULL;
  }
  q->size++;
  return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
  // Null check
  if (q == NULL) return false;

  // Element to remove
  list_ele_t *ele = q->head;

  // Empty check
  if (ele == NULL) return false;

  if (sp != NULL) {
    // Copy string
    int i;
    for (i = 0; (i < bufsize - 1) && (ele->value[i] != '\0'); i++) {
      sp[i] = ele->value[i];
    }
    sp[i] = '\0';
  }

  if (q->size == 1) {
    q->head = NULL;
    q->tail = NULL;
    free(ele->value);
    free(ele);
  } else {
    list_ele_t *new_head = ele->next;
    q->head = new_head;
    free(ele->value);
    free(ele);
  }
  q->size--;
  return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
  // Use the size attribute
  if (q != NULL) {
    return q->size;
  } else {
    return 0;
  }
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
  // Null check, empty check
  if (q == NULL) return;
  if (q->size < 2) return;

  list_ele_t *prev, *curr, *next;
  prev = NULL;
  curr = q->head;
  while (curr != NULL) {
    next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }

  // Flip tail and head
  curr = q->head;
  q->head = q->tail;
  q->tail = curr;
}

