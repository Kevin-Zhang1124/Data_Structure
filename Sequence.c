#include <stdlib.h>
#include "sequence.h"
// add your include here
#include <assert.h>

// ================= DO NOT CHANGE THESE LINES =================
typedef void* (*Copy_data)    (const void*);
typedef void  (*Destroy_data) (void*);
typedef void  (*Print_data)   (const void*);
// =============================================================


struct Sequence {
    Copy_data copy;
    Print_data print;
    Destroy_data destroy;
    // additional field definitions goes here
    int row;
    int col;
    void*** data;
};


// seq_create(row, col, print, destroy)
//  returns a pointer to heap allocated Sequence
// Effects: allocates memory, caller must free
// Time: O(row * col)
struct Sequence* seq_create(const int row, const int col, 
                            Copy_data copy, Print_data print, Destroy_data destroy) {
    // your implementation goes here
    struct Sequence* seq = malloc(sizeof(struct Sequence));
    seq->copy = copy;
    seq->print = print;
    seq->destroy = destroy;
    seq->row = row;
    seq->col = col;
    seq->data = malloc(sizeof(void**) * row);
    for (int i = 0; i < row; i++) {
        seq->data[i] = malloc(sizeof(void*) * col);
        for (int j = 0; j < col; j++) {
            seq->data[i][j] = NULL;
        }
    }
    return seq;
}


// seq_destroy(seq) fress the heap allocated seq
// Effects: frees memory
// Time: O(r * c * k) where O(k) is destroy
void seq_destroy(struct Sequence* seq) {
    // your implementation goes here
    assert(seq);
    for (int i = 0; i < seq->row; i++) {
        for (int j = 0; j < seq->col; j++) {
            seq->destroy(seq->data[i][j]);
        }
        free(seq->data[i]);
    }
    free(seq->data);
    free(seq);
}


// seq_insert_at(seq, data, r, c) inserts data at given row and column
//  data will be replaced if such position already contains an element
// Effects: mutates *seq
// Requires: seq is not NULL, 0 <= r < row, 0 <= c < col
// Time: O(k)
void seq_insert_at(struct Sequence* seq, void* data, const int r, const int c) {
    // your implementation goes here
    assert(seq);
    assert(data);
    assert(0 <= r && r < seq->row);
    assert(0 <= c && c < seq->col);
    seq->destroy(seq->data[r][c]);
    seq->data[r][c] = seq->copy(data);
}


// seq_remove_at(seq, r, c) removes and returns the data at given row and column
//  returns NULL if no element is at such position
// Effects: may mutate *seq
// Requires: seq is not NULL, 0 <= r < row, 0 <= c < col
// Time: O(k)
void* seq_remove_at(struct Sequence* seq, const int r, const int c) {
    // your implementation goes here
    assert(seq);
    assert(0 <= r && r < seq->row);
    assert(0 <= c && c < seq->col);
    void* retval = seq->data[r][c];
    seq->data[r][c] = NULL;
    return retval;
}

