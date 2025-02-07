#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>


// Binary Search Tree Node
// key of parent > key of all children at left side
// key of parent < key of all children at right side
struct Node {
    int key;
    struct Node* left;
    struct Node* right;
};

struct Tree {
    struct Node* root;
};


static struct Node* node_create(int num) {
    struct Node* node = malloc(sizeof(struct Node));
    node->key = num;
    node->left = NULL;
    node->right = NULL;
    return node;
}


static void node_destroy(struct Node* node) {
    if (node != NULL) {
        node_destroy(node->left);
        node_destroy(node->right);
        free(node);
    }
}


struct Tree* tree_create() {
    struct Tree* tree = malloc(sizeof(struct Tree));
    tree->root = NULL;
    return tree;
}


void tree_destroy(struct Tree* tree) {
    if (tree) {
        node_destroy(tree->root);
        free(tree);
    }
}


static bool contain_key_internal(const struct Node* node, int num) {
    if (node == NULL) {
        return false;
    }
    if (num == node->key) {
        return true;
    } else if (num < node->key) {
        return contain_key_internal(node->left, num);
    } else {
        return contain_key_internal(node->right, num);
    }
} 

bool contain_key_recursive(const struct Tree* tree, int num) {
    assert(tree);
    return contain_key_internal(tree->root, num);
}


bool contain_key_iteration(const struct Tree* tree, int num) {
    // case 1: if current node contains the key, returns true
    // case 2: if current node key > num, search for left subtree
    // case 3: if current node key < num, search for right subtree
    assert(tree);

    struct Node* curr = tree->root;
    while (curr) {
        if (num == curr->key) {
            return true;
        } else if (num < curr->key) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    return false;
}


struct Node* insert_key_internal(struct Node* node, int num) {
    if (node == NULL) {
        return node_create(num);
    }
    if (node->key == num) {
        return node;
    } else if (num < node->key) {
        node->left = insert_key_internal(node->left, num);
    } else {
        node->right = insert_key_internal(node->right, num);
    }
    return node;
}

void insert_key_recursive(struct Tree* tree, int num) {
    assert(tree);
    tree->root = insert_key_internal(tree->root, num);
}


void insert_key_iteration(struct Tree* tree, int num) {
    assert(tree);
    if (tree->root == NULL) {
        tree->root = node_create(num);
        return;
    }
    struct Node* curr = tree->root;
    while (curr) {
        if (num == curr->key) {
            return;
        } else if (num < curr->key) {
            if (curr->left == NULL) {
                curr->left = node_create(num);
                break;
            } else {
                curr = curr->left;
            }
        } else {
            if (curr->right == NULL) {
                curr->right = node_create(num);
                break;
            } else {
                curr = curr->right;
            }
        }
    }
}


static struct Node* remove_key_internal(struct Node* node, int num) {
    // find the key to be removed
    if (node == NULL) {
        return node;
    }
    if (num < node->key) {                  // go left
        node->left = remove_key_internal(node->left, num);
    } else if (num > node->key) {           // go right
        node->right = remove_key_internal(node->right, num);
    } else {                                // key is found
        // case 1: no left and no right
        if (node->left == NULL && node->right == NULL) {
            free(node);
            return NULL;
        }
        // case 2: no left has right
        if (node->left == NULL) {
            struct Node* right_child = node->right;
            free(node);
            return right_child;
        }
        // case 3: has left no right
        if (node->right == NULL) {
            struct Node* left_child = node->left;
            free(node);
            return left_child;
        }
        // case 4: neither child is NULL
        struct Node* prev = NULL;
        struct Node* curr = node->right;
        while (curr->left != NULL) {
            prev = curr;
            curr = curr->left;
        }
        node->key = curr->key;      // replace the key
        if (prev == NULL) {
            node->right = curr->right;
        } else {
            prev->left = curr->right;
        }
        free(curr);
    }
    return node;
}

void remove_key(struct Tree* tree, int num) {
    assert(tree);

    tree->root = remove_key_internal(tree->root, num);
}


static void node_print(const struct Node* node) {
    if (node == NULL) return;
    node_print(node->left);
    printf("%d\n", node->key);
    node_print(node->right);
 }


void bst_print(const struct Tree* tree) {
    assert(tree);
    node_print(tree->root);
}


static int count_internal(const struct Node* node) {
    if (node == NULL) return 0;
    return 1 + count_internal(node->left) + count_internal(node->right);
}

int count_nodes(const struct Tree* tree) {
    assert(tree);
    
    return count_internal(tree->root);
}
