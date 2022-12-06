#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_MSG 50
#define MAX_MTU 60

struct QNode
{
    char message[MAX_MSG];
    struct QNode *next;
};

typedef struct Args
{
    /* data */
    char ip[14];
    char porta[5];
    char message[MAX_MSG];
}Args;

// The queue, front stores the front node of LL and rear
// stores the last node of LL
typedef struct Queue
{
    struct QNode *front, *rear;
}Queue;

// A utility function to create a new linked list node.
struct QNode *newNode(char *s)
{
    struct QNode *temp = (struct QNode *)malloc(sizeof(struct QNode));
    strcpy(temp->message,s);
    temp->next = NULL;
    return temp;
}

struct Args *newArgs(char*msg,char* ip,char*port)
{
    struct Args *temp = (struct Args *)malloc(sizeof(struct Args));
    strcpy(temp->message,msg);
    strcpy(temp->porta,port);
    strcpy(temp->ip,ip);
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
    char* mensagem = malloc(sizeof(char)*MAX_MSG+1);
    // If queue is empty, return NULL.
    if (q->front == NULL)
    {
        strcpy(mensagem,"1");
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

int get_n(char *message,FILE *fp)
{
    int i = 0;
    char ch;
/*
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
*/
    printf("bytes = %ld\n",fread(message,MAX_MSG, 1, fp));
    
    //fgets(message,100,fp);
    printf("\n\nlen da mensagem %ld\na mensagem eh %s\n\n\n",strlen(message),message);

    return 1;
}

int le_arquivo(Queue *q,char *nome_arquivo)
{
    FILE *fp = fopen(nome_arquivo,"rb");
    char message[MAX_MSG];
    char header[1000];

    // strcpy(destination,source,n_chars)
    if(fp == NULL)
    {
        printf("Não foi possível fazer a leitura do arquivo.\nAbortando . . .\n");
        return -1;
    }

    int bytes = 0;
    strcpy(header,"header-");
    // write header 
    //printf("Escrevendo header %s\n",strcat(header,nome_arquivo));
    //enQueue(q,strcat("header-",nome_arquivo));
    enQueue(q,strcat(header,nome_arquivo));

    while (fread((message), MAX_MSG, 1, fp)) {
        printf("\n\nlen da mensagem %ld\na mensagem eh %s\n\n\n",strlen(message),message);
        message[MAX_MSG] = '\0';

        enQueue(q, message);
        memset(message, 0x0, MAX_MSG);

    }

    enQueue(q, message);
    enQueue(q, "FIM\0");
    memset(message, 0x0, MAX_MSG);

    printf("Arquivo enviado \\(^o^)/\n");
}

void escreve_arquivo(FILE *fp,char* msg)
{
    int i = 0;

    if(strcmp(msg,"FIM\0") == 0){
        fclose(fp);
        printf("Arquivo lido com sucesso !!!!\n");
        return;
    }

    fwrite(msg,1,strlen(msg),fp);

}