#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estrutura.h"

Ppacote new_pacote(){
	Ppacote pck 	=NULL;
	pck				=(Ppacote)malloc(1*sizeof(Tpacote));
	pck->gate		='0';
	pck->permissao	='N';
	strcpy (pck->nome,"none");//(char*)malloc(30*sizeof(char));
	strcpy (pck->credencial	,"none");//(char*)malloc(4*sizeof(char));
	return pck;
}