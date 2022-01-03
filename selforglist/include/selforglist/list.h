#include "selforglist/models.h"

#ifndef SELFORGANIZINGLIST_LIST_H
#define SELFORGANIZINGLIST_LIST_H

void print(const struct List *);
void print_metadata(const struct List *);
void insert(List *, double);
ListNode *delete(List *, double);
ListNode *search(const struct List *, double);
ListNode *create_node(double);

void organize_mtf(List *, ListNode *);
void organize_transpose(List *, ListNode *);
void organize_count(List *, ListNode *);

List *new_list(void(*organize)(List *, ListNode *));


#endif //SELFORGANIZINGLIST_LIST_H
