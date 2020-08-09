#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <time.h> 
#include "jogo.h"
#define PORT 8080 

int main(int argc, char const *argv[]) 
{ 
    int server_fd, new_socket, valread; 
    int jogador1 , jogador2 ;

    struct sockaddr_in address; 
    
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer_1[1024] = {0}; 
    char buffer_2[1024] = {0}; 
    char *hello = "Hello from server"; 

    //jogadores
    char msgp1[100] = "jogador 1 entre com seu nome : "; 
    char msgp2[100] = "jogador 2 entre com seu nome : "; 

    char *msgp3 = NULL;
    msgp3=(char*)malloc(50*sizeof(char));
    char *msgp4 = NULL; 
    msgp4=(char*)malloc(50*sizeof(char));


    char nome_p1[64] = {0}; 
    char nome_p2[64] = {0};
    //tabuleiro
    Ppacote jogo=NULL;
    jogo = novo_pacote();

    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    // Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family      = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port        = htons( PORT ); 
       
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address,sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    if (listen(server_fd, 2) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    }
	while(1){ 
		
	    //aceitando jogador 1
	    if ((jogador1 = accept(server_fd, (struct sockaddr *)&address,(socklen_t*)&addrlen))<0) 
	    { 
	        perror("accept"); 
	        exit(EXIT_FAILURE); 
	    }
	    //aceitando jogador 2
	    if ((jogador2 = accept(server_fd, (struct sockaddr *)&address,(socklen_t*)&addrlen))<0) 
	    { 
	        perror("accept"); 
	        exit(EXIT_FAILURE); 
	    }
		
	    send(jogador1 , msgp1 , strlen(msgp1) , 0 );
	    valread = read( jogador1 , nome_p1, 64); 

	    //printf("pegando dados do jogador 2\n");
	    send(jogador2 , msgp2 , strlen(msgp2) , 0 ); 
	    valread = read( jogador2 , nome_p2, 64); 

	    strcpy(msgp3,"seu adversario eh ");
	    strcat(msgp3,nome_p2);
	    

	    strcpy(msgp4,"seu adversario eh ");
	    strcat(msgp4,nome_p1);

	    
	    /**
	    *informando nomes dos aversários
	    *
	    */
	    send(jogador1,msgp3,strlen(msgp3),0);
	    send(jogador2,msgp4,strlen(msgp4),0); 
	 
	    //criar o jogo
	    Ppacote jogo_velha=NULL;
	    jogo_velha = novo_pacote();
	    // variaveis para loop nos respectivos clientes
	    char *jogadas_p1=NULL;
	    char *jogadas_p2=NULL;
	    jogadas_p1=(char*)malloc(1*sizeof(char));
	    jogadas_p2=(char*)malloc(1*sizeof(char));
	    *jogadas_p1='5';
	    *jogadas_p2='4';

	    sleep(1);
	    send(jogador1,jogadas_p1,strlen(jogadas_p1),0); 
	    send(jogador2,jogadas_p2,strlen(jogadas_p2),0); 

	    int num_jogadas=0;
	    int ret1 = -1;
	    int ret2=-1;
	    int *pos=NULL;
	    int *flag_vencedor;//
	    flag_vencedor = (int*)malloc(1*sizeof(int));//
	    pos = (int*)malloc(1*sizeof(int));
	    *flag_vencedor=0;
		while (num_jogadas<9 && (*flag_vencedor)==0){
	    	//printf("entrou\n");
		    //jogador 1
		    if(num_jogadas%2==0){


		        send(jogador1, jogo_velha   , sizeof(Tpacote) ,0);
		        
		        ret1= -1 ;       
		        while(ret1 < 0){
		            ret1 = read( jogador1 , pos, sizeof(pos));
		            }  

		        ret1= -1 ; 
		        sleep(1);
		        jogo_velha->pos= *pos ;
		        atualiza(jogo_velha,1);  
		        sleep(1);
		    }
		    //jogador 2
		    else{
		        
		        ret2= -1 ;
		        send(jogador2, jogo_velha, sizeof(Tpacote) ,0);

		        while(ret2 < 0){
		            ret2 = read( jogador2 , pos, sizeof(pos));
		            }
		        ret2= -1 ;
		        sleep(1);
		        jogo_velha->pos= *pos ;
		        atualiza(jogo_velha,2);	        
		        sleep(1);
		    }
		    *flag_vencedor=verifica_jogo(jogo_velha);
		        if ((*flag_vencedor)!=0){
		            jogo_velha->encerrou=*flag_vencedor;
		            send(jogador1, jogo_velha   , sizeof(Tpacote) ,0);
		            sleep(1);
		            send(jogador2, jogo_velha, sizeof(Tpacote) ,0);

		        }
		    
		    num_jogadas++;
		}
		//após o resultado
		char * vencedor;
		char * perdedor;
		char * velha;
		vencedor = (char*)malloc(100*sizeof(char));
		perdedor = (char*)malloc(100*sizeof(char));
		velha    = (char*)malloc(100*sizeof(char));
		strcpy(vencedor, "voce venceu ");
		strcpy(perdedor, "voce perdeu ");
		strcpy(velha   , " DEU VELHA  ");
		if(*flag_vencedor == 1){
		    //jogador 1 venceu
		    //printf("jogador 1%s\n",vencedor );
		    send(jogador1,vencedor,100*sizeof(char),0);
		    sleep(2); 
		    send(jogador2,perdedor,100*sizeof(char),0);

		}else if(*flag_vencedor == 2){
		    //jogador 2
		    send(jogador2,vencedor,100*sizeof(char),0);
		    sleep(2); 
		    send(jogador1,perdedor,100*sizeof(char),0);
		}else if(*flag_vencedor==0){
		    // velha
		    send(jogador1,velha,100*sizeof(char),0);
		    sleep(2); 
		    send(jogador2,velha,100*sizeof(char),0);
		}
	}	


  
  

    return 0; 
} 
