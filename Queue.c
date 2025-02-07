#include <stdlib.h>
#include <assert.h>



struct node {
    int val;
    struct node* next;
};

static struct node* node_create(int num) {
    struct node* new_node = malloc(sizeof(struct node));
    new_node->val = num;
    new_node->next = NULL;
    return new_node;
}

static void node_destroy_recursion(struct node* node) {
    if (node != NULL) {
        node_destroy_recursion(node->next);
        free(node);
    }
}

static void node_destroy_iteration(struct node* node) {
    struct node* curr = node;
    while (curr != NULL) {
        // saves the pointer to next node
        struct node* temp = curr->next;
        free(curr);
        curr = temp;
    }
}


struct queue {
    struct node* front;
    struct node* back;
    int len;        // number of elements in queue
};


// queue_create()
//  create a new empty queue in heap memory
// effects: allocates memory
// requires: caller must free
struct queue* queue_create() {
    struct queue* q = malloc(sizeof(struct queue));
    q->front = NULL;
    q->back = NULL;
    q->len = 0;
    return q;
}


// queue_destroy(q) deallocates q in heap memory
// effects: deallocates memory
void queue_destroy(struct queue* q) {
    if (q) {
        node_destroy_recursion(q->front);
        free(q);
    }
}


// queue_enqueue(q, num) enqueues num at the back of q
// effects: mutates *q
void queue_enqueue(struct queue* q, int num) {
    assert(q);
    struct node* new_node = node_create(num);
    if (q->front == NULL) {
        q->front = new_node;
        q->back = new_node;
    } else {
        q->back->next = new_node;
        q->back = new_node;
    }
    q->len += 1;
}


// queue_front(q)
// returns the front value in q
// requires: q is not empty
int queue_front(const struct queue* q) {
    assert(q);
    assert(q->front);
    return q->front->val;
}


// queue_dequeue(q) removes the front value of q
// effects: mutates q
// requires: q is not empty
void queue_dequeue(struct queue* q) {
    assert(q);
    assert(q->front);
    struct node* temp = q->front;
    q->front = q->front->next;
    // free just a single node
    free(temp);
    if (q->front == NULL) {
        q->back = NULL;
    }
    q->len -= 1;
}


// queue_length(q) returns the number of values in q
// requires: q is not NULL
// time: O(1)
int queue_length(const struct queue* q) {
    assert(q);
    return q->len;
}


// queue_insert_at(q, index, num) inserts num at position index inside q
// effects; mutates q
// requires: index >= 0 && index <= len;
void queue_insert_at(struct queue* q, int index, int num) {
    assert(q);
    assert(index >= 0);
    assert(index <= q->len);

    struct node* new_node = node_create(num);
    // two pointers
    struct node* prev = NULL;
    struct node* curr = q->front;
    for (int i = 0; i < index; i++) {
        prev = curr;
        curr = curr->next;
    }
    if (prev && curr) { // insert in the middle
        prev->next = new_node;
        new_node->next = curr;
    } else if (prev) { // insert at the end
        prev->next = new_node;
        q->back = new_node;
    } else if (curr) { // insert at the front
        new_node->next = q->front;
        q->front = new_node;
    } else { // insert into an empty queue
        q->front = new_node;
        q->back = new_node; 
    }

    q->len += 1;
}


// queue_remove_at(q, index) removes and returns the value at position
//  index in q
// effects: mutates *q
// requires: q is not NULL, q is not empty
//          index >= 0 && index < len
int queue_remove_at(struct queue* q, int index) {
    assert(q);
    assert(q->len > 0);
    assert(index >= 0);
    assert(index < q->len);

    struct node* prev = NULL;
    struct node* curr = q->front;
    for (int i = 0; i < index; i++) {
        prev = curr;
        curr = curr->next;
    }
    int result = 0;
    if (prev && curr) {
        result = curr->val;
        prev->next = curr->next;
        free(curr);
        if (prev->next == NULL) {
            q->back = prev;
        }
    } else if (curr) {
        result = curr->val;
        q->front = q->front->next;
        free(curr);
        if (q->front == NULL) {
            q->back = NULL;
        }
    }
    q->len -= 1;
}

