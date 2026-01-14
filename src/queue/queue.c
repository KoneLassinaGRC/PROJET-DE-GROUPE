#include "queue.h"

/*LISTE CHAÎNÉE SIMPLE*/

Node* list_insert(Node* head, int value) {
    Node* newNode = malloc(sizeof(Node));
    if (!newNode) {
        printf("Erreur allocation mémoire\n");
        return head;
    }
    newNode->data = value;
    newNode->next = head;
    return newNode;
}

Node* list_delete(Node* head, int value) {
    if (!head) return NULL;

    if (head->data == value) {
        Node* temp = head;
        head = head->next;
        free(temp);
        return head;
    }

    Node* current = head;
    while (current->next && current->next->data != value) {
        current = current->next;
    }

    if (current->next) {
        Node* temp = current->next;
        current->next = temp->next;
        free(temp);
    }

    return head;
}

void list_display(Node* head) {
    while (head) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

void list_free(Node* head) {
    while (head) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

/*FILE SIMPLE (FIFO)*/

void queue_init(Queue* q) {
    q->front = NULL;
    q->rear = NULL;
}

int queue_is_empty(Queue* q) {
    return q->front == NULL;
}

void queue_enqueue(Queue* q, int value) {
    Node* newNode = malloc(sizeof(Node));
    if (!newNode) {
        printf("Erreur allocation mémoire\n");
        return;
    }

    newNode->data = value;
    newNode->next = NULL;

    if (queue_is_empty(q)) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

int queue_dequeue(Queue* q) {
    if (queue_is_empty(q)) {
        printf("File vide\n");
        return -1;
    }

    Node* temp = q->front;
    int value = temp->data;

    q->front = temp->next;
    if (!q->front)
        q->rear = NULL;

    free(temp);
    return value;
}

void queue_free(Queue* q) {
    while (!queue_is_empty(q)) {
        queue_dequeue(q);
    }
}

/* FILE DE PRIORITÉ (BONUS)*/

void pq_init(PriorityQueue* pq) {
    pq->front = NULL;
}

int pq_is_empty(PriorityQueue* pq) {
    return pq->front == NULL;
}

void pq_push(PriorityQueue* pq, int value, int priority) {
    PNode* newNode = malloc(sizeof(PNode));
    if (!newNode) {
        printf("Erreur allocation mémoire\n");
        return;
    }

    newNode->data = value;
    newNode->priority = priority;
    newNode->next = NULL;

    if (pq_is_empty(pq) || pq->front->priority > priority) {
        newNode->next = pq->front;
        pq->front = newNode;
    } else {
        PNode* current = pq->front;
        while (current->next && current->next->priority <= priority) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

int pq_pop(PriorityQueue* pq) {
    if (pq_is_empty(pq)) {
        printf("File de priorité vide\n");
        return -1;
    }

    PNode* temp = pq->front;
    int value = temp->data;
    pq->front = temp->next;
    free(temp);
    return value;
}

void pq_free(PriorityQueue* pq) {
    while (!pq_is_empty(pq)) {
        pq_pop(pq);
    }
}
// Test commit feature-queue