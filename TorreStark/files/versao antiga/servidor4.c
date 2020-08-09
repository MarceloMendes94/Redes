// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <time.h>
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#define PORT 8080 
int main(int argc, char const *argv[]) 
{ 

    // definindo a estrutura do pacote a ser recebido
    typedef struct pacote{
        char id[5];
        int sala;
    }Tpacote,*Ppacote;
    Ppacote pck_cliente=NULL;
    pck_cliente=(Ppacote)malloc(sizeof(Tpacote));
    struct mensagem{
		time_t td; /* Data e hora atual */
		char nome[128]; /* nome do servidor */
	};


    int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[1024] = {0}; 
    char *hello = "Hello from server"; 
    int *cred_cli;
    cred_cli=(int*)malloc(sizeof(int));
    time_t td; /* Data e hora atual */
	char dtbuf[128]; /* Informações de data e hora */
	struct mensagem msg; /* variagem utilizada para armazernar os dados da estrutura */
    int n;   
    int sair=1;
    char *id;
    char *nivel;
    char *nome;
   
    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    // Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
                       (socklen_t*)&addrlen))<0) 
    { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    } 
    while(1){
	    valread = read( new_socket , pck_cliente, sizeof(Tpacote)); 
	   /* altivo insira a busca no aquivo aqui */
	    FILE *arq;
	    FILE *log;
	    arq= fopen("vingadores.txt","r");
	    log= fopen("teste.txt","a");
	    if(arq==NULL){
	        printf("erro\n");
	        return 1;
	    }
	    char txt[100];
		char delim[] = ",";
	    fscanf(arq,"%49[^\n]",txt);
	    fgetc(arq);
		char *ptr = strtok(txt, delim);
		int cont=0;
		while(ptr != NULL)
		{	
			if(cont==0){
				id=ptr;
				cont=1;
			}else if(cont==1){
				nome=ptr;
				cont=2;
			}else if(cont==2){
				nivel=ptr;
			}
			ptr = strtok(NULL, delim);
		}
		strcat(id,"\0");
	    while(strcmp(id,pck_cliente->id)!=0 && strlen(txt)!=0){
			strcpy(id,"");
			strcpy(nome,"");
			strcpy(nivel,"");
			strcpy(txt,"");
			fscanf(arq,"%49[^\n]",txt);
	    	fgetc(arq);
			ptr = strtok(txt, delim);
			cont=0;
			while(ptr != NULL)
			{	
				if(cont==0){
					id=ptr;
					cont=1;
				}else if(cont==1){
					nome=ptr;
					cont=2;
				}else if(cont==2){
					nivel=ptr;
				}
				ptr = strtok(NULL, delim);
			}
			strcat(id,"\0");
	    }
	    time(&msg.td);
		n = (int) strftime(dtbuf,sizeof dtbuf, "%d/%b/%Y - %H:%M:%S", localtime(&msg.td));
		dtbuf[n] = 0;
	    int nivelN=atoi(nivel);
	    if(strlen(txt)!=0 && nivelN>=pck_cliente->sala){
	        printf("Acesso autorizado. Bem vindo %s\n", nome);
	        fprintf(log,"%s,p%d,%s,autorizado\n", dtbuf,pck_cliente->sala,pck_cliente->id);
	    }else{
	    	if(strlen(txt)!=0){
	    		printf("Acesso negado.%s suas crendenciais nao permitem acesso a essa sala\n", nome);
	    	}else{
	    		printf("Acesso negado. Desconhecido suas crendenciais nao permitem acesso a essa sala\n");
	    	}
	        fprintf(log,"%s,p%d,%s,negado\n", dtbuf,pck_cliente->sala,pck_cliente->id);
	    }
	    printf(" a sala que vc deseja acessar %d\n",pck_cliente->sala ); 
	    printf(" seu id %s\n",pck_cliente->id ); 
	    fclose(arq);
	    fclose(log);
	}
    //send(new_socket , hello , strlen(hello) , 0 ); 
    //printf("Hello message sent\n"); 
    return 0; 
} 
