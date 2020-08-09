#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "jogo.h"
#include <string.h>
#define clear() printf("\033[H\033[J")
/**
 * cria um novo pacote zerado
 * 
 * */
Ppacote novo_pacote(){
    Ppacote jogo = (Ppacote)malloc(1*sizeof(Tpacote));
    for (int i=0;i<3;i++){
        for (int j=0;j<3;j++){
            jogo->mat[i][j]=0;
        }
    }
    jogo->pos=0;
    jogo->encerrou=0;
    return jogo;
}
/**
 * 
 * atualiza o tabuleiro com o char val, zera pos, colocar o valor na matriz com numero do jogador 
 */
void atualiza(Ppacote jogo, int jogador){
    
   if(jogo->pos==1){
        jogo->mat[0][0]=jogador;
   }else if(jogo->pos==2){
        jogo->mat[0][1]=jogador;
   }else if(jogo->pos==3){
        jogo->mat[0][2]=jogador;
   }
   else if(jogo->pos==4){
        jogo->mat[1][0]=jogador;       
   }
   else if(jogo->pos==5){
        jogo->mat[1][1]=jogador;
   }
   else if(jogo->pos==6){
        jogo->mat[1][2]=jogador;
   }
   else if(jogo->pos==7){
        jogo->mat[2][0]=jogador;   
   }
   else if(jogo->pos==8){
       jogo->mat[2][1]=jogador;
   }
   else if(jogo->pos==9){
       jogo->mat[2][2]=jogador;
   }else{
       printf("posição invalida");
   }   
}
/**
 * retorna 1 caso a joga seja possivel 
 * retorna 0 caso não se possa jogar
 * */
int verifica_jogada(Ppacote jogo){
    int ret = 0;
    if(jogo->pos==1){
        if(jogo->mat[0][0]==0){
            ret=1;
        }
   }else if(jogo->pos==2){
        if(jogo->mat[0][1]==0){
            ret=1;
        }
   }else if(jogo->pos==3){
        if(jogo->mat[0][2]==0){
            ret=1;
        }
   }
   else if(jogo->pos==4){
        if(jogo->mat[1][0]==0){
            ret=1;
        }
   }
   else if(jogo->pos==5){
        if(jogo->mat[1][1]==0){
            ret=1;
        }
   }
   else if(jogo->pos==6){
        if(jogo->mat[1][2]==0){
            ret=1;
        }

   }
   else if(jogo->pos==7){
        if(jogo->mat[2][0]==0){
            ret=1;
        }
   }
   else if(jogo->pos==8){
       if(jogo->mat[2][1]==0){
           ret=1;
       }
   }
   else if(jogo->pos==9){
       if(jogo->mat[2][2]==0){
           ret=1;
       }
   }else{
       printf("posição invalida");
   }   
 
    return ret;
}
/**
 * verifica se ha ganhador 
 * 
 * */
int verifica_jogo(Ppacote jogo){
    int col_1[3];
    int col_2[3];
    int col_3[3];
    int lin_1[3];
    int lin_2[3];
    int lin_3[3];
    int dia_p[3];
    int dia_s[3];

    for (int i = 0 ; i<3 ; i++){
        for (int j=0;j<3;j++){
            //pegando colunas
            if(i==0){
                col_1[j]=jogo->mat[i][j];
            }
            if(i==1){
                col_2[j]=jogo->mat[i][j];
            }
            if(i==2){
                col_3[j]=jogo->mat[i][j];
            }
            //pegando linhas
            if(j==1){
                lin_1[i]=jogo->mat[i][j];
            }if(j==2){
                lin_1[i]=jogo->mat[i][j];
            }if(j==3){
                lin_1[i]=jogo->mat[i][j];
            }
            //diagonal principal
            if(i==j){
                dia_p[i]=jogo->mat[i][j];
            }

        }
    }
    dia_s[2]=jogo->mat[0][2];
    dia_s[1]=jogo->mat[1][1];
    dia_s[0]=jogo->mat[2][0];

    int flag_vencedor=0;
    if(col_1[0]==col_1[1]  && col_1[0]==col_1[2]){
        if (col_1[0]==1){
        	return 1;
        }else if (col_1[0]==2){
        	return 2;
        }

    }
    else if(col_2[0]==col_2[1] && col_2[0]==col_2[2]){
        if (col_2[0]==1){
        	return 1;
        }else if (col_2[0]==2){
        	return 2;
        }
    }
    else if(col_3[0]==col_3[1] && col_3[0]==col_3[2]){
        if (col_3[0]==1){
        	return 1;
        }else if (col_3[0]==2){
        	return 2;
        }
    }
    else if(lin_1[0]==lin_1[1]  && lin_1[0]==lin_1[2]){
        if (lin_1[0]==1){
        	return 1;
        }else if (lin_1[0]==2){
        	return 2;
        }
    }
    else if(lin_2[0]==lin_2[1] && lin_2[0]==lin_2[2]){
        if (lin_2[0]==1){
        	return 1;
        }else if (lin_2[0]==2){
        	return 2;
        }
    }
    else if(lin_3[0]==lin_3[1] && lin_3[0]==lin_3[2]){
        if (lin_3[0]==1){
        	return 1;
        }else if (lin_3[0]==2){
        	return 2;
        }
    }
    else if(dia_p[0]==dia_p[1] && dia_p[0]==dia_p[2]){
        if (dia_p[0]==1){
        	return 1;
        }else if (dia_p[0]==2){
        	return 2;
        }
    }else if(dia_s[0]==dia_s[1] && dia_s[0]==dia_s[2]){
        if (dia_s[0]==1){
        	return 1;
        }else if (dia_s[0]==2){
        	return 2;
        }
    }
 return 0;
}



void show(Ppacote jogo){
  //  printf("\nposicao %d\n\n\n tabuleiro\n\n\n%s",jogo->pos,jogo->tabuleiro);
    for (int i=0;i<3;i++){
        printf("\n");
        for (int j=0;j<3;j++){
            if (j==2){
                printf(" %d ", jogo->mat[i][j]);
            }else{
                printf(" %d |", jogo->mat[i][j]);
            }
            
        }
        if (i!=2){
            printf("\n-----------");
        }
    }
    printf("\n");   
}
/*
int main(){
    Ppacote pck=NULL;
    pck=novo_pacote();
    show(pck);
    int jogadas=0;
    // show(pck);
    int flag_permissao_jogada=0;//caso ele queira jogar no mesma posicao
    int vencedor;    
    while(jogadas<9){
        vencedor=verifica_jogo(pck);
        if(vencedor !=0 ){
            printf(" vencedor jogador numero %d",vencedor);
            break;
        }
        if(jogadas%2==0){
            while(flag_permissao_jogada==0){
                printf("digite a posicao  ");
                scanf("%d",&pck->pos);
                flag_permissao_jogada=verifica_jogada(pck);
            }            
            atualiza(pck,'x',1);
            flag_permissao_jogada=0;
        }else{
            
            while(flag_permissao_jogada==0){
                printf("digite a posicao  ");
                scanf("%d",&pck->pos);
                flag_permissao_jogada=verifica_jogada(pck);
            }            
            atualiza(pck,'x',2);
            flag_permissao_jogada=0;
        }
        
        show(pck);
        jogadas++;
    }
    if(verifica_jogo(pck)==0){
        printf("end game\n empate");
    }
    
    show(pck);
 
    return 0;
}*/