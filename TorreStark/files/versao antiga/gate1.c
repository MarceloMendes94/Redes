
// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#define PORT 8080 
   
int main(int argc, char const *argv[]) 
{ 
	typedef struct pacote{
		char id[5];
		int sala;
	}Tpacote,*Ppacote;
	// declaração
		Ppacote pck=NULL;
		char* 	aux_id=NULL;
		



    struct sockaddr_in address; 
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
//    char *hello = "Hello from client"; //
	int *cred=NULL;
    char buffer[1024] = {0}; 
	


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
    while(1){
	    //criação do pacote
		pck=(Ppacote)malloc(sizeof(Tpacote));
		aux_id=(char*)malloc(5*sizeof(char));
		int portaid;
		scanf("%d",&portaid);
		pck->sala=portaid;	
		printf("digite o numero de sua crendecial\n");
		scanf("%s",aux_id);
		strcpy(pck->id,aux_id);
		printf("dados do pacote ID (%s) GATE(%d)\n ",pck->id,pck->sala);


		// pacote feito

		//enviar o pacote ao servidor
		send(sock,pck,sizeof(Tpacote),0);
		printf("Crendenciais enviada ao servidor\n");	
	}
    //valread = read( sock , buffer, 1024); 
    //printf("%s\n",buffer ); 
    return 0; 
} 

