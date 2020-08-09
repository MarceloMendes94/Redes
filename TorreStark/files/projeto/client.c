#include <unistd.h> 
#include <stdio.h> 
#include <time.h>
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <arpa/inet.h>
#include "estrutura.h"
#define PORT 8080 





int main(int argc, char const *argv[])
{
	
    
    // conexao feita
    while(1){
	    	//redes 
		struct sockaddr_in address;
		struct sockaddr_in serv_addr; 
		int sock = 0;
		int retorno_sock = -1;

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
	  	

    	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){ 
       		 	printf("\nConnection Failed \n"); 
        		return -1; 
    		}  
    //estrutura
		Ppacote pck=NULL;
		pck=new_pacote();
		retorno_sock =-1;
		if (argc<2){
			printf("parametros invalidos\n");	
		}else{
			

			pck->gate = *argv[1];
			char aux[4];
			printf("Entre coma credencial : ");
			scanf("%s", aux);
			strcpy(pck->credencial,aux);
			send(sock , pck , sizeof(Tpacote) , 0 );
		    printf("numero do portao %c\n" , pck->gate      );
		    printf("numero credencial %s\n", pck->credencial);
		    while(retorno_sock <0){
		        retorno_sock =read( sock , pck, sizeof(Tpacote));         
		    }
		    retorno_sock =-1;
		   	if(pck->permissao=='A'){
		   		printf("Acesso autorizado. Bem-vindo%s\n",pck->nome);
		   	}else{
		   		printf("Acesso negado.%s suas credencias não permitem acesso a esta sala\n",pck->nome);
		   	}   

		    free(pck);
		}
		close(sock);
	}

	return 0;
}