#include "selforglist/list.h"
#include "selforglist/models.h"
#include <stdlib.h>
#include <stdio.h>

ListNode *create_node(double val) {
    ListNode *new_node = malloc(sizeof(ListNode));
    new_node->prev = new_node->next = NULL;
    new_node->accesses = 0;
    new_node->val = val;
    return new_node;
}

void insert(List *self, double val) {
    ListNode *new_node = self->create_node(val);
    if (self->length == 0) {
        self->head = self->tail = new_node;
    } else {
//        a new member is always inserted at the tail
        ListNode *t = self->tail;
        t->next = new_node;
        new_node->prev = t;
        self->tail = new_node;
    }
    self->length++;
}

ListNode *search(const List *self, double val) {
    ListNode *it = self->head;
    while (it != NULL && it->val != val) {
        it = it->next;
    }
    if (it->val != val) return NULL;
    it->accesses++;
    self->organize((List *) self, it);
    return it;
}

ListNode *delete(List *self, double val) {
    ListNode *node_to_delete = self->search(self, val);
    if (node_to_delete == NULL) {
        printf("not_in_list");
        return NULL;
    }
    if (self->head == node_to_delete) {
        self->head = self->head->next;
        self->head->prev = NULL;
        self->length--;
        node_to_delete->prev = node_to_delete->next = NULL;
        return node_to_delete;
    } else if (self->tail == node_to_delete) {
        self->tail = self->tail->prev;
        self->tail->next = NULL;
        self->length--;
        node_to_delete->prev = node_to_delete->next = NULL;
        return node_to_delete;
    }
    ListNode *p = node_to_delete->prev;
    ListNode *n = node_to_delete->next;
    p->next = n;
    n->prev = p;
    self->length--;
    return node_to_delete;
}

void print(const List *self) {
    if (self == NULL) return;
    ListNode *it = self->head;
    while (it != NULL) {
        printf("%f\t", it->val);
        it = it->next;
    }
}

void print_metadata(const List *self) {
    if (self == NULL) return;
    printf("\n----- START LIST METADATA -----\n");
    printf(">length: %u\n", self->length);
    printf("\n----- END LIST METADATA ------\n");
}

void organize_mtf(List *self, ListNode *node) {
    ListNode *t = self->head;
    if (node == t) return;
    ListNode *p = node->prev;
    ListNode *n = node->next;
    if (self->tail == node)self->tail = p;
    p->next = n;
    if (n != NULL) n->prev = p;
    node->next = t;
    node->prev = NULL;
    t->prev = node;
    self->head = node;
}

void organize_transpose(List *self, ListNode *node) {
    if (self->head == node) return;
    if (node->prev == self->head) {
        ListNode *t = self->head;
        ListNode *n = node->next;
        node->next = t;
        t->prev = node;
        t->next = n;
        n->prev = t;
        node->prev = NULL;
        self->head = node;
    } else if (node == self->tail) {
        ListNode *t = node->prev->prev;
        ListNode *p = node->prev;
        t->next = node;
        node->prev = t;
        node->next = p;
        p->prev = node;
        p->next = NULL;
        self->tail = p;
    } else {
        ListNode *p = node->prev;
        ListNode *n = node->next;
        ListNode *np = node->prev->prev;
        np->next = node;
        node->prev = np;
        node->next = p;
        p->prev = node;
        p->next = n;
        n->prev = p;
    }
}

// bit of a hack solution here. not my best work but it'll do
void organize_count(List *self, ListNode *node) {
    if (self->length == 1 || self->head == node) return;
    if (node->accesses >= self->head->accesses) {
        ListNode *t = self->head;
        ListNode *p = node->prev;
        ListNode *n = node->next;
        p->next = n;
        if (n != NULL) n->prev = p;
        node->next = t;
        t->prev = node;
        node->prev = NULL;
        self->head = node;
    } else {
        ListNode *it = self->head;
        while (it != NULL && it->accesses > node->accesses) {
            it = it->next;
        }
        if (node->next == NULL) {
            self->tail = node->prev;
            self->tail->next = NULL;
        }
        ListNode *t = it->next;
        node->next = t;
        t->prev = node;
        node->prev = it;
        it->next = node;
    }
}

// this is one way to simulate overloading constructors, I suppose
List *new_list(void(*organize)(List *, ListNode *)) {
    List *new_list = malloc(sizeof(List));
    new_list->head = new_list->tail = NULL;
    new_list->length = 0;
    new_list->organize = *organize;
    new_list->create_node = create_node;
    new_list->print = print;
    new_list->print_metadata = print_metadata;
    new_list->search = search;
    new_list->insert = insert;
    new_list->delete = delete;
    return new_list;
}