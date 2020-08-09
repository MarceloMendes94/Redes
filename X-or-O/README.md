# X or O

## Trabalho de Redes com programação em socket

#### elaboração de um jogo da velha com a API socket na linguagem de programação C

### Alunos:
#### Andre Altivo
#### Marcelo Mendes

### Regras do jogo
[especificação do trabalho](https://github.com/MarceloMendes94/X-or-O/blob/master/files/2.Trabalho%2002%20-%20Programa%C3%A7%C3%A3o%20socket.pdf)<br>

### Arquivos do trabalho 
[pasta do projeto com arquivos](https://github.com/MarceloMendes94/X-or-O/tree/master/files/finalmente)<br>
A pasta é composta por 4 arquivos de codigo e 2 executaveis
após baixado é necessário compilar os arquivos.  

#### linhas de comando para compilação do trabalho.

Para compilar o servidor digite a linha a baixo<br>
gcc -o serverapp serve.c jogo.c

Para compilar o cliente digite a linha a baixo<br>
gcc -o clientapp client.c jogo.c

* Observação nenhuma mensagem de erro deve aparecer.

#### linhas de comando para execução 

Abra 3 terminais: 1 para o servidor e 2 para os clientes
em um terminal do servidor digite  o seguinte comando 

./serverapp


nos outros dois digite o seguinte comando 

./clientapp


a aplicação só começa apos esses passos serem feitos.

#### referências 
[tutorial com uso da biblioteca](https://www.geeksforgeeks.org/socket-programming-cc/)<br>
[material professor Volnys Borges Bernal USP](https://github.com/MarceloMendes94/X-or-O/blob/master/files/70-ClienteTCP-v9.pdf)