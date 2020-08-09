#include <unistd.h> 
#include <stdio.h> 
#include <time.h>
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <time.h>
#include "estrutura.h"
#define PORT 8080 

int main(int argc, char const *argv[])
{
	int server_fd;
    int cliente1 , cliente2 ;
    int ret_c1=-1;
    struct sockaddr_in address; 
    
    int opt = 1; 
    int addrlen = sizeof(address); 

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
    if (listen(server_fd, 5) < 0) //trocar para 2
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    }
    
    while(1){

        Ppacote pck=NULL;
        pck=new_pacote();


        //aceitando jogador 1
        if ((cliente1 = accept(server_fd, (struct sockaddr *)&address,(socklen_t*)&addrlen))<0) 
        { 
            perror("accept"); 
            exit(EXIT_FAILURE); 
        }

        // recendo estrutura   
        while(ret_c1<0){
            ret_c1=read( cliente1 , pck, sizeof(Tpacote));         
        }

        ret_c1=-1;
        //printf("numero do portao %c\n" , pck->gate      );
        char aux[4];
        strcpy(aux,pck->credencial);
       // printf("numero credencial %s\n", pck->credencial);

        // abrindo o arquivo de registro
        FILE *reg_f;
        reg_f  = fopen("registro.txt","a");

        // abrindo a base de dados       
        FILE *arq;
        arq= fopen("dados.txt","r");
        

        //variaves locais de loop   observação não são maolcadas
        char *id;
        char *nivel;
        char *nome;
       

        //verificandeo se há erros
        if(arq==NULL){
            printf("erro\n");
            return 1;
        }
        
        char txt[100];
        char delim[] = ",";
        while( fscanf(arq,"%49[^\n]",txt)!=EOF){
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
            int porta_permitida;
            int porta_desejada;
            porta_permitida = atoi(nivel);
            porta_desejada  = atoi(&pck->gate);
                
            if ((strcmp(id,pck->credencial)==0) && porta_desejada <= porta_permitida){
                pck->permissao='A';
                strcpy(pck->nome,nome);
                break;
            } 
              

        }
        //lido todo arquivo feche-o
        fclose(arq); 
        
        time_t mytime;
        mytime = time(NULL);
        struct tm tm = *localtime(&mytime);

        if(pck->permissao=='A'){
            fprintf(reg_f,"%d/%d/%d - %d:%d:%d, p%c, %s, Autorizado.\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900,   tm.tm_hour, tm.tm_min, tm.tm_sec, pck->gate, pck->credencial);   
        }else{
            fprintf(reg_f,"%d/%d/%d - %d:%d:%d, p%c, %s, Negado.\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900,       tm.tm_hour, tm.tm_min, tm.tm_sec, pck->gate, pck->credencial);   
        }
        
        //enviando permissao pro cliente
        send(cliente1 , pck , sizeof(Tpacote) , 0 );
        fclose(reg_f);
        close(cliente1);
    }






	return 0;
}
