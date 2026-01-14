#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>

/* LISTE CHAÎNÉE SIMPLE*/

typedef struct Node {
    int data;
    struct Node* next;
} Node;

/* Fonctions liste chaînée */
Node* list_insert(Node* head, int value);
Node* list_delete(Node* head, int value);
void list_display(Node* head);
void list_free(Node* head);

/* FILE SIMPLE (FIFO)*/

typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

void queue_init(Queue* q);
int queue_is_empty(Queue* q);
void queue_enqueue(Queue* q, int value);
int queue_dequeue(Queue* q);
void queue_free(Queue* q);

/* FILE DE PRIORITÉ (BONUS)*/

typedef struct PNode {
    int data;
    int priority;
    struct PNode* next;
} PNode;

typedef struct PriorityQueue {
    PNode* front;
} PriorityQueue;

void pq_init(PriorityQueue* pq);
int pq_is_empty(PriorityQueue* pq);
void pq_push(PriorityQueue* pq, int value, int priority);
int pq_pop(PriorityQueue* pq);
void pq_free(PriorityQueue* pq);

#endif

// Test commit feature-queue