//
// Created by Anish Sinha on 1/2/22.
//

#ifndef SELFORGANIZINGLIST_MODELS_H
#define SELFORGANIZINGLIST_MODELS_H

typedef struct ListNode {
    double val;
    unsigned int accesses;
    struct ListNode *prev;
    struct ListNode *next;
} ListNode;

typedef struct List {
    unsigned int length;
    ListNode *head;
    ListNode *tail;
    void (*organize)(struct List *, ListNode *); // any function that implements this signature can be assigned here
    void (*print)(const struct List *);
    void (*print_metadata)(const struct List *);
    void (*insert)(struct List *, double);
    ListNode *(*delete)(struct List *, double);
    ListNode *(*search)(const struct List *, double);
    ListNode *(*create_node)(double);
} List;

#endif //SELFORGANIZINGLIST_MODELS_H
