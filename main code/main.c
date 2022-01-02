#pragma ide diagnostic ignored "misc-no-recursion"
#include <stdio.h>
#include <stdlib.h>

// tree struct
typedef struct node * tree;
struct node {
    int key;
    tree left, right;
};

// list struct
typedef struct element *list;
struct element {
    int value;
    list next;
};

// tree methods
tree tree_create(int, tree, tree);
void tree_l_rot(tree*);
void tree_r_rot(tree*);
int  tree_height(tree);
void tree_insert_left(tree *tp, int key);
void tree_insert_right(tree *tp, int key);
list tree_to_list_evens(tree);
int  tree_leaf_product(tree);
int  tree_prom(tree);
int  tree_is_rightist(tree);
tree tree_bfs(tree);

void tree_print(tree);

// list methods
void list_append(list *, int);
int  list_sum(list);
void list_remove(list*);
void list_remove_evens(list*);
void list_remove_max(list*);

void list_print(list);

int main() {
    list list_test = NULL;
    list_append(&list_test, 5);
    list_append(&list_test, 6);
    list_append(&list_test, 2);
    list_append(&list_test, 9);
    list_append(&list_test, 7);
    list_append(&list_test, 4);
    list_append(&list_test, 9);

    printf("List: ");
    list_print(list_test);
    printf("List sum: %d\n", list_sum(list_test));

    list_remove_max(&list_test);
    printf("List without max: ");
    list_print(list_test);

    list_remove_evens(&list_test);
    printf("List without evens: ");
    list_print(list_test);

    /*
    Example Tree:
           015
          /   \
       005     035
       /       / \
     003     020 056
    */
//    tree tree_test = tree_create(15,
//                                 tree_create(5,
//                                             tree_create(3,
//                                                         NULL,
//                                                         NULL),
//                                             NULL),
//                                 tree_create(35,
//                                             tree_create(20,
//                                                         NULL,
//                                                         NULL),
//                                             tree_create(56,
//                                                         NULL,
//                                                         NULL)));
    /*
    Bigger example tree
                        050
                  /-----/ \-------------\
                030                     080
                / \-\             /-----/ \
              015   045         071       093
            /-/     / \       /-/ \-\
          007     035 047   059     077
          / \               / \     / \
        001 010           054 063 074 078
     */

    tree tree_test = tree_create(50,
                                 tree_create(30,
                                             tree_create(15,
                                                         tree_create(7,
                                                                     tree_create(1,
                                                                                 NULL,
                                                                                 NULL),
                                                                     tree_create(10,
                                                                                 NULL,
                                                                                 NULL)),
                                                         NULL),
                                             tree_create(45,
                                                         tree_create(35,
                                                                     NULL,
                                                                     NULL),
                                                         tree_create(47,
                                                                     NULL,
                                                                     NULL))),
                                 tree_create(80,
                                             tree_create(71,
                                                         tree_create(59,
                                                                     tree_create(54,
                                                                                 NULL,
                                                                                 NULL),
                                                                     tree_create(63,
                                                                                 NULL,
                                                                                 NULL)),
                                                         tree_create(77,
                                                                     tree_create(74,
                                                                                 NULL,
                                                                                 NULL),
                                                                     tree_create(78,
                                                                                 NULL,
                                                                                 NULL))),
                                             tree_create(93,
                                                         NULL,
                                                         NULL)));
    tree_print(tree_test);

    tree_l_rot(&tree_test);
    printf("left rotation:\n");
    tree_print(tree_test);

    tree_insert_right(&tree_test, 95);
    tree_insert_right(&tree_test, 104);
    tree_insert_right(&tree_test, 108);
    tree_insert_left(&tree_test, 0);
    printf("append:\n");
    tree_print(tree_test);

    tree_r_rot(&tree_test);
    printf("rotating back:\n");
    tree_print(tree_test);

    list tree_list_even = tree_to_list_evens(tree_test);
    printf("Even list of tree: ");
    list_print(tree_list_even);

    return 0;
}

// TREES ========================================================================

// Übung 6 Aufgabe 2a
tree tree_create(int key_value, tree left, tree right) {
    tree new_tree = malloc(sizeof(struct node));
    new_tree->left = left;
    new_tree->right = right;
    new_tree->key = key_value;
    return new_tree;
}

// Übung 6 Aufgabe 2b
void tree_insert_left(tree* tp, int key){
    if (tp == NULL)
        return;
    while (*tp != NULL)
        tp = &(*tp)->left;
    *tp = tree_create(key, NULL, NULL);
}
void tree_insert_right(tree* tp, int key){
    if (tp == NULL)
        return;
    while (*tp != NULL)
        tp = &(*tp)->right;
    *tp = tree_create(key, NULL, NULL);
}

// Übung 9 Aufgabe 2b
void tree_l_rot(tree* tp) {
    if (tp == NULL || *tp == NULL || (*tp)->right == NULL)
        return;

    tree right = (*tp)->right;

    (*tp)->right = right->left;
    right->left = (*tp);
    *tp = right;
}
void tree_r_rot(tree* tp) {
    if (tp == NULL || *tp == NULL || (*tp)->left == NULL)
        return;

    tree left = (*tp)->left;

    (*tp)->left = left->right;
    left->right = (*tp);
    *tp = left;
}

int tree_height(tree t) {
    if (t == NULL)
        return 0;
    int hl = tree_height(t->left);
    int hr = tree_height(t->right);
    if (hl > hr)
        return hl + 1;
    return hr + 1;
}

// Übung 6 Aufgabe 2c
int tree_leaf_product(tree t){
    if (t == NULL)
        return 1;
    if (t->left == NULL && t->right == NULL)
        return t->key;
    return tree_leaf_product(t->left) * tree_leaf_product(t->right);
}

void tree_to_list_evens_recursive(tree t, list* lp){
    if (t == NULL)
        return;
    tree_to_list_evens_recursive(t->left, lp);
    if (t->key % 2 == 0)
        list_append(lp, t->key);
    tree_to_list_evens_recursive(t->right, lp);
}

// Übung 6 Aufgabe 2d
list tree_to_list_evens(tree t){
    list l = NULL;
    tree_to_list_evens_recursive(t, &l);
    return l;
}

// Übung 9 Aufgabe 2a
tree tree_bfs(tree t) {
    if (t == NULL)
        return NULL;
    tree bf = malloc(sizeof(struct node));
    bf->key = tree_height(t->right) - tree_height(t->left);
    bf->left = tree_bfs(t->left);
    bf->right = tree_bfs(t->right);
    return bf;
}

// Übung 7 ZAufgabe 3a
int tree_prom(tree t){
    int prom = 0;
    while (t != NULL) {
        if (t->left == NULL)
            t = t->right;
        else
            t = t->left;
        prom ++;
    }
    return prom;
}

// Übung ZAufgabe 3b
int tree_is_rightist(tree t){
    if (t == NULL)
        return 1;
    return (tree_prom(t->left) <= tree_prom(t->right))
            && tree_is_rightist(t->left)
            && tree_is_rightist(t->right);
}

// LISTS ========================================================================

// Übung 6 Aufgabe 1a
void list_append(list *lp, int new_value) {
    while (*lp != NULL)
        lp = &((*lp)->next);
    (*lp) = (list) malloc(sizeof(struct element));
    (*lp)->value = new_value;
    (*lp)->next = NULL;
}

// Übung 6 Aufgabe 1b
int list_sum(list list){
    int sum = 0;
    while (list != NULL){
        sum += list->value;
        list = list->next;
    }
    return sum;
}

// Übung 6 Aufgabe 1c
void list_remove_evens(list* lp){
    if (lp == NULL)
        return;
    while (*lp != NULL) {
        if ((*lp)->value % 2 == 0)
            list_remove(lp);
        else
            lp = &((*lp)->next);
    }
}

// removes the first element of the passed list
void list_remove(list* lp){
    if (lp == NULL || *lp == NULL)
        return;
    list temp = *lp;
    *lp = (*lp)->next;
    free(temp);
}

// Übung 6 ZAufgabe 2
void list_remove_max(list* lp){
    if (lp == NULL || (*lp) == NULL)
        return;
    int max_value = (*lp)->value;
    list l = (*lp)->next; // loop variable
    while (l != NULL) {
        if (l->value > max_value)
            max_value = l->value;
        l = l->next;
    }
    while (*lp != NULL) {
        if ((*lp)->value != max_value)
            lp = &((*lp)->next);
        else
            list_remove(lp);
    }
}

// ==================================================================== THIS CODE IS NOT PART OF ANY AUD EXERCISE ====================================================================
// this is only here to help you visualize trees and lists

// printing of lists

void list_print(list l) {
    printf("[");
    if (l != NULL) {
        printf("%d", l->value);
        l = l->next;
        while (l != NULL) {
            printf(", %d", l->value);
            l = l->next;
        }
    }
    printf("]\n");
}

// printing of trees

typedef struct element_generic* list_generic;
struct element_generic {
    // a void* is a general pointer which could point onto anything
    // malloc(..) for example returns a void*
    void *data;
    list_generic next;
};

void list_generic_append(list_generic* lp, void* value) {
    while (*lp != NULL)
        lp = &((*lp)->next);
    (*lp) = (list_generic) malloc(sizeof(struct element_generic));
    (*lp)->data = value;
    (*lp)->next = NULL;
}

list_generic list_generic_remove_first(list_generic* lp){
    if (lp == NULL || *lp == NULL) // there is no list or the list has no first element
        return NULL;
    list_generic first_element = (*lp);
    *lp = first_element->next;
    return first_element;
}

int tree_width(tree t){
    // calc width of a tree to create right spacing in the output
    if (t == NULL)
        return 1;
    else
        return tree_width(t->left) + 1 + tree_width(t->right);
}
void tree_print_node(tree t){
    // only prints the root node
    if (t == NULL){
        printf(" ");
        return;
    }
    for (int i = 1; i < tree_width(t->left); i ++)
        printf(" ");
    printf("%03d", t->key);
    for (int i = 1; i < tree_width(t->right); i ++)
        printf(" ");
}

void tree_print_connection(tree t){
    // prints the connection of the root node to the next layer
    if (t == NULL){
        printf(" ");
        return;
    }
    if (t->left != NULL) {
        for (int i = 0; i <= tree_width(t->left->left); i++)
            printf(" ");
        printf("/");
        int right = tree_width(t->left->right);
        if (right > 1) {
            for (int i = 2; i < right; i++)
                printf("-");
            printf("/");
        }
    } else
        printf(" ");
    printf(" ");
    if (t->right!= NULL) {
        int left = tree_width(t->right->left);
        printf("\\");
        if (left > 1) {
            for (int i = 2; i < left; i++)
                printf("-");
            printf("\\");
        }
        for (int i = 0; i <= tree_width(t->right->right); i++)
            printf(" ");
    } else
        printf(" ");
}

void tree_print(tree t) {
    printf("\n");
    if (t == NULL) {
        printf("Empty tree!");
        return;
    }

    list_generic node_list = NULL;
    list_generic_append(&node_list, t);
    for (int level = 0; level < tree_height(t); level++) {
        // print nodes of current level
        list_generic loop_list = node_list;
        while (loop_list != NULL){
            tree_print_node(loop_list->data);
            printf(" ");
            loop_list = loop_list->next;
        }

        // print connections to the next level
        printf("\n");
        loop_list = node_list;
        while (loop_list != NULL){
            tree_print_connection(loop_list->data);
            printf(" ");
            loop_list = loop_list->next;
        }
        printf("\n");

        // find nodes of next level
        list_generic new_list = NULL; // list containing next's level nodes
        while (node_list != NULL){
            list_generic first_element = list_generic_remove_first(&node_list);
            tree current_node = (tree) first_element->data;
            free(first_element);
            if (current_node == NULL){ // filling the list with NULLs for missing elements
                list_generic_append(&new_list, NULL);
            } else {
                list_generic_append(&new_list, current_node->left);
                list_generic_append(&new_list, current_node->right);
            }
        }
        node_list = new_list;
    }
    printf("\n");
}