#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

/* Notice: sometimes, Cppcheck would find the potential NULL pointer bugs,
 * but some of them cannot occur. You can suppress them by adding the
 * following line.
 *   cppcheck-suppress nullPointer
 */


/* Create an empty queue */
struct list_head *q_new()
{
    struct list_head *new = malloc(sizeof(struct list_head));
    if (!new)
        return NULL;

    INIT_LIST_HEAD(new);
    return new;
}

/* Free all storage used by queue */
void q_free(struct list_head *l)
{
    if (!l)
        return;

    // cppcheck-suppress nullPointer
    element_t *node = NULL;

    // cppcheck-suppress nullPointer
    element_t *prev = NULL;

    list_for_each_entry (node, l, list) {
        // cppcheck-suppress knownConditionTrueFalse
        if (prev) {
            list_del(&prev->list);
            q_release_element(prev);
        }
        prev = node;
    }
    // cppcheck-suppress knownConditionTrueFalse
    if (prev) {
        list_del(&prev->list);
        q_release_element(prev);
    }

    free(l);
}

/* Insert an element at head of queue */
bool q_insert_head(struct list_head *head, char *s)
{
    if (!head)
        return false;

    element_t *new = malloc(sizeof(element_t));
    if (!new)
        return false;

    INIT_LIST_HEAD(&new->list);
    int str_size = strlen(s);
    new->value = malloc((str_size + 1) * sizeof(char));

    if (!new->value) {
        free(new);
        return false;
    }

    strncpy(new->value, s, str_size);
    *(new->value + str_size) = '\0';
    list_add(&new->list, head);

    return true;
}

/* Insert an element at tail of queue */
bool q_insert_tail(struct list_head *head, char *s)
{
    if (!head)
        return false;

    element_t *new = malloc(sizeof(element_t));
    if (!new)
        return false;

    INIT_LIST_HEAD(&new->list);
    int str_size = strlen(s);
    new->value = malloc((str_size + 1) * sizeof(char));

    if (!new->value) {
        free(new);
        return false;
    }

    strncpy(new->value, s, str_size);
    *(new->value + str_size) = '\0';
    list_add_tail(&new->list, head);

    return true;
}

/* Remove an element from head of queue */
element_t *q_remove_head(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head))
        return NULL;

    element_t *target = list_entry(head->next, element_t, list);
    list_del(&target->list);

    if (bufsize) {
        strncpy(sp, target->value, bufsize - 1);
        *(sp + bufsize - 1) = '\0';
    }
    return target;
}

/* Remove an element from tail of queue */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    return NULL;
}

/* Return number of elements in queue */
int q_size(struct list_head *head)
{
    return -1;
}

/* Delete the middle node in queue */
bool q_delete_mid(struct list_head *head)
{
    // https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/
    return true;
}

/* Delete all nodes that have duplicate string */
bool q_delete_dup(struct list_head *head)
{
    // https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
    return true;
}

/* Swap every two adjacent nodes */
void q_swap(struct list_head *head)
{
    // https://leetcode.com/problems/swap-nodes-in-pairs/
}

/* Reverse elements in queue */
void q_reverse(struct list_head *head) {}

/* Reverse the nodes of the list k at a time */
void q_reverseK(struct list_head *head, int k)
{
    // https://leetcode.com/problems/reverse-nodes-in-k-group/
}

/* Sort elements of queue in ascending order */
void q_sort(struct list_head *head) {}

/* Remove every node which has a node with a strictly greater value anywhere to
 * the right side of it */
int q_descend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/description/
    return 0;
}
