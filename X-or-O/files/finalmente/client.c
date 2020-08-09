#include <unistd.h>
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h>
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include "jogo.h"

#define PORT 8080 
   
int main(int argc, char const *argv[]) 
{ 
    struct sockaddr_in address; 
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    //msg de leitura tam sempre 100

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    memset(&serv_addr, '0', sizeof(serv_addr)); 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
    // preparando msg de leitura de pedido de nome e enviando nome
    char* str_rcv_msg=NULL;
    char nome[50];
    str_rcv_msg=(char*)malloc(100*sizeof(char));
    valread = read( sock , str_rcv_msg, 100);
    printf("%s\n",str_rcv_msg ); 
    scanf("%s",nome);
    send(sock , nome , strlen(nome) , 0 ); 
 
    // preparando msg de leitura do nome do adversario
    char* nome_adversario=NULL;
    nome_adversario=(char*)malloc(50*sizeof(char));
    valread = read( sock , nome_adversario, 50);
    printf("%s \n",nome_adversario );     

    //pegando o numero de jogadas
    char *j=NULL;    
    j=(char*)malloc(1*sizeof(char));
    valread = read( sock , j, 1);
    int jogadas;
    jogadas=atoi(j);    
    
    int cont=0;
    
    int flag_ok=-1;
    Ppacote jogo_velha=NULL;
    jogo_velha = novo_pacote();

    int ret=-1;
    int retf=-1;
    int * pos= NULL;
    int *flag_vencedor;//
    flag_vencedor = (int*)malloc(1*sizeof(int));//
    pos = (int*)malloc(1*sizeof(int));
    *flag_vencedor=0;
    while(jogadas>cont){
        
        ret =-1;
        while(ret < 0){
            ret=read(sock, jogo_velha ,sizeof(Tpacote));        
        }
        sleep(1);
        *flag_vencedor=jogo_velha->encerrou;
        
        if( *flag_vencedor!=0){
            printf("acabou\n");
            break;
        }
        show(jogo_velha);
        printf("de a posição desejada\n");
        scanf("%d",pos);
        send(sock , pos , sizeof(int) , 0 ); 
        sleep(1);

        cont++;
    }

    int retorno_final=-1;    
    char * resultado;
    resultado = (char*)malloc(100*sizeof(char));
        while(retorno_final < 0 ){
            retorno_final=read(sock,resultado,100 );//   
        }   
    sleep(1); 
    printf("%s %s\n",resultado , nome);

    return 0; 
} 
