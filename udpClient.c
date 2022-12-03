
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>  
#include <stdlib.h>
#include "queue.h"

#define MAX_MSG 100

int main(int argc, char *argv[]){
    int sd, rc, i;
    struct sockaddr_in ladoCli;    //dados do cliente local    
    struct sockaddr_in ladoServ; 	  //dados do servidor remoto  

    //confere o numero de argumentos passados para o programa  
    if(argc<3){
        printf("uso correto: %s <ip_do_servidor> <porta_do_servidor> <dado1> ... <dadoN> \n", argv[0]);
        exit(1);    
    }

    //Preenchendo as informacoes de identificacao do remoto  
    ladoServ.sin_family 	   = AF_INET;
    ladoServ.sin_addr.s_addr = inet_addr(argv[1]);
    ladoServ.sin_port 	   = htons(atoi(argv[2]));

    //Preenchendo as informacoes de identificacao do cliente  
    ladoCli.sin_family 	 = AF_INET;
    ladoCli.sin_addr.s_addr= htonl(INADDR_ANY);
    ladoCli.sin_port 	     = htons(0);   //usa porta livre entre (1024-5000) 

    //Criando um socket. Nesse momento a variavel        
    // /sd contem apenas dados sobre familia e protocolo   

    sd = socket(AF_INET,SOCK_DGRAM,0);
    if(sd<0) {
        printf("%s: nao pode abrir o socket \n",argv[0]);
        exit(1); }

    //Relacionando o socket sd com a estrutura ladoCli  
    //Depois do bind, sd faz referencia a protocolo local, ip local e porta local  
    rc = bind(sd, (struct sockaddr *) &ladoCli, sizeof(ladoCli));
    if(rc<0) {
        printf("%s: nao pode fazer um bind da porta\n", argv[0]);
        exit(1); }
    printf("{UDP, IP_Cli: %s, Porta_Cli: %u, IP_R: %s, Porta_R: %s}\n", inet_ntoa(ladoCli.sin_addr), ntohs(ladoCli.sin_port), argv[1], argv[2]);

    //Enviando um pacote para cada parametro informado  
    // PASSO A PASSO
    // - Interfacezinha ??????
    // - qual arquivo deseja enviar para o outro lado ? 
    // - lê o arquivo -> fila de mensagem 
    // - criar a PDU com a mensagem do dequeue
    //for(i=3;i<argc;i++) {

    char nome_arquivo[64];
    
    for(;;)
    {
        printf("### Teste ###\n");
        printf("Qual arquivo você deseja ler :");
        scanf("%s",nome_arquivo);
        
        // ler o arquivo e passar ele pra fila de mensagem
        FILE *fp = fopen(nome_arquivo,"r");
        Queue *q = createQueue();

        // da fila de mensagem, escrever a PDU com a mensagem lida
        // enviar a PDU



        while ((getchar()) != '\n');
    }


    while(1) {
        if (le_fila() == 1) {
            //chama função para tratamento de envio dos dados coletados da fila de mensagens:
            //recuperar dados da fila  
            //alimentar PDU com a mensagem - lembrar que a mensagem é uma string de tamanho
            //variável 
            rc = sendto(sd, argv[i], strlen(argv[i]), 0,(struct sockaddr *) &ladoServ, sizeof(ladoServ));
        if(rc<0) {
            printf("%s: nao pode enviar dados %d \n",argv[0],i-1);
            close(sd);
            exit(1); 
        }
        printf("Enviando parametro %d: %s\n", i-2, argv[i]);
            //enviar PDU  
            //aguardar reconhecimento da PDU enviada 
            //etc.  
        }   fim-if  
        if (le_porta_socket() == true) {
            //chama função para tratamento de recepção dos dados recebidos pela porta_socket:
            //recuperar dados da porta socket  
            //desmontar a PDU recebida  
            //entregar dados recebidos para a camada superior, via fila de mensagens  
            //enviar reconhecimento  
            //etc.  
            }   fim-if  
    }   //fim-while 

    return 1;
}
