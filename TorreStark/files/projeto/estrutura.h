#include <stdio.h>
#include <stdlib.h>


typedef struct pacote{
	char gate;
	char permissao;
	char nome[30];//[30]
	char credencial[4];//[4]
}*Ppacote,Tpacote;

Ppacote new_pacote();
