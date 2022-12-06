#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "queue.h"

/*
Passo a passo
//      - Ler arquivo e quebrar em buffers e os colocar em uma fila de mensagens.
//      - Implementar a fila de mensagens.
//      - Fila de mensagens a princípio é uma fila normal mas que guarda
//        dados de cabeçalhos
//      - PDU
- Tem que ter cabeçalho e a área de dados (mensagem)
- Tem que ter um tamanho de área de dados fixa.
- Tamanho da PDU fixa

- Fluxo total :
- Lê de arquivo e monta fila OK
- Fila tem X tamanho de mensagem OK
- enqueue para PDU e da PDU via socket pro cliente 
- do lado do cliente
- Lê a PDU e remonta arquivo

*/
// A linked list (LL) node to store a queue entry

int main()
{
    Queue *q = createQueue();
    char teste[1000];

    le_arquivo(q,"poema.txt");

    printf("Queue Front : %s \n", q->front->message);
    printf("Queue Rear : %s\n", q->rear->message);

    printf("### PRINTANDO POEMA CARAI  ####\n\n");
    int i = 0;
    while(i<20)
    {
        //printf("Entrei\n");
        //printf("### teste = %s ###\n",teste);
        strcpy(teste,deQueue(q));

        if(strcmp(teste,"FIM\0") != 0)
        {   
            printf("%s",teste);
        }
        else{
            printf("Da hora\n");
            printf("Acabou com sucesso\n");
            break;
        }

        i++;
    }

    return 0;
}