# Torre stark
### Trabalho da disciplina de redes
#### Alunos
Andre Altivo<br>
Marcelo Mendes<br>
[especificação do trabalho](https://github.com/MarceloMendes94/Torre-stark/blob/master/files/1.Trabalho%2001%20-%20Programa%C3%A7%C3%A3o%20socket.pdf)

#### Projeto é composto de 8 arquivos sendo eles 

server.c  			para servidor.
client.c  	 		para cliente.
dados.txt 			base de dados dos usuarios comforme a especificação do professor.
registro.txt 		aondde ficarão os registro de tentativa de acesso.
estrutura .h & .c 	arquivos com estrutura usada para envio de mensagens.
cliente 			arquivo client ja compilado.
servidor 			arquivo server ja compilado.
[pasta com o projeto](https://github.com/MarceloMendes94/Torre-stark/tree/master/files/projeto)<br>

#### compilação dos arquivos deve ser feita da seguinte forma
##### Servidor
gcc -o server servidor.c estrutura.c
##### Cliente
gcc -o cliente client.c estrutura.c

após a compilação o comando de execução deve ser  feito da seguinte forma
./servidor 


./cliente [numero do portão]
exemplo:<br>
./cliente 1

lembre-se primeiro deve ser executado servido e dps o cliente o servidor suporta até 5 clientes simultaneos