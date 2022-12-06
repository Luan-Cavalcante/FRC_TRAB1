#ifndef QUEUE_LIB
#define QUEUE_LIB 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_MSG 50
#define MAX_MTU 60

typedef struct Queue
{
    struct QNode *front, *rear;
}Queue;

struct QNode
{
    char message[MAX_MSG+5];
    struct QNode *next;
};

struct QNode * newNode(char *s);
struct Queue * createQueue();
void enQueue(struct Queue *q, char* k);
char* deQueue(struct Queue *q);
int get_n(char * message,FILE *fp);
int le_arquivo(Queue *q,char* nome_arquivo);
int escreve_arquivo(FILE *fp,char* msg);

#endif