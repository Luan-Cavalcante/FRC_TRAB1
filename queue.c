#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_MSG 50
#define MAX_MTU 60

struct QNode
{
    char message[MAX_MSG+5];
    struct QNode *next;
};

// The queue, front stores the front node of LL and rear
// stores the last node of LL
typedef struct Queue
{
    struct QNode *front, *rear;
}Queue;

// A utility function to create a new linked list node.
struct QNode * newNode(char *s)
{
    struct QNode *temp = (struct QNode *)malloc(sizeof(struct QNode));
    strcpy(temp->message,s);
    temp->next = NULL;
    return temp;
}

// A utility function to create an empty queue
struct Queue * createQueue()
{
    struct Queue *q =(struct Queue *)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q;
}

// The function to add a message k to q
void enQueue(struct Queue *q, char* k)
{
    // Create a new LL node
    struct QNode *temp = newNode(k);

    // If queue is empty, then new node is front and rear
    // both
    if (q->rear == NULL)
    {
        q->front = q->rear = temp;
        return;
    }

    // Add the new node at the end of queue and change rear
    q->rear->next = temp;
    q->rear = temp;
}

// Function to remove a message from given queue q
char* deQueue(struct Queue *q)
{
    char * mensagem = malloc(sizeof(char)*MAX_MSG+1);
    // If queue is empty, return NULL.
    if (q->front == NULL)
    {
        strcpy(mensagem,"Empty");
        return mensagem;
    }
    // Store previous front and move front one node ahead
    struct QNode *temp = q->front;

    q->front = q->front->next;

    // If front becomes NULL, then change rear also as NULL
    if (q->front == NULL)
        q->rear = NULL;

    strcpy(mensagem,temp->message);

    free(temp);

    return mensagem;
}

int get_n(char * message,FILE *fp)
{
    int i = 0;
    char ch;

    do {
        ch = fgetc(fp);
        if(ch==EOF){
            printf("Arquivo acabou . . .\n");
            // retorna zero qnd acaba
            return 0;
        }
        message[i] = ch;
        //printf("i = %d\n",i);
        i++;
        printf("%c", ch);
    } while(i<MAX_MSG);
    
    //fgets(message,100,fp);
    //printf("\n\nlen da mensagem %ld\na mensagem eh %s\n\n\n",strlen(message),message);

    return 1;
}

int le_arquivo(Queue *q,char *nome_arquivo)
{
    FILE *fp = fopen(nome_arquivo,"r");
    char message[MAX_MSG+1];

    // strcpy(destination,source,n_chars)
    if(fp == NULL)
    {
        printf("Não foi possível fazer a leitura do arquivo.\nAbortando . . .\n");
        return -1;
    }

    // lê n chars e adiciona pra mensagem na fila
    int fim = 1;
    do{
        fim = get_n(message,fp);
        //rintf("\n\n%d - a len da message eh %ld\na mensagem eh %s\n\n\n",fim,strlen(message),message);
        enQueue(q,message);
    }while(fim == 1);
}