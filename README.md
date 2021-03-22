# INTERPRETADOR

Interpretador para uma linguagem de programação definida por um conjunto de instruções relativamente pequeno.

- Expressões: expressões aritméticas com um único operador. (exemplos: 2 + 3 , 4*x , y/z ).

- Inserção dum valor para uma variável: para que o utilizador possa indicar um valor para a variável identificada pela string referida na instrução. Caso a variável já tenha valor, esse valor será substituído pelo novo.
ler(<variável>);

- Escrever o valor de uma variável:
escrever(<variável>);

- Atribuir o valor duma expressão a uma variável: todas as variáveis que ocorram na expressão deverão ter já um valor definido; o valor da expressão será atribuído à variável que se encontra do lado esquerdo.
<variável> = <expressão>;

- labels: label <string>

- instruções goto: goto label

- comandos condicionais da forma: if <variável> goto <label>

- Terminar a execução do programa: QUIT

Para compilar o trabalho basta executar o seguinte comando num terminal Linux, no respetivo diretório:
gcc -Wall -o mainT1 mainT1.c Trabalho1.c

Para executar:
./mainT1

Feito isto, basta introduzir instruções, concluíndo, cada uma, com ENTER ('\n'). A leitura de instruções acaba quando é digitado "QUIT".
É importante referir que devem ser deixados espaços no Input das instruções, para que o programa funcione da maneira correta.

Tipos de instrunções aceites:

-> Atribuições.
Exemplo: x = 2

-> Leituras.
Exemplo: LER x 2 (em que x fica com o valor 2)

-> Prints.
Exemplo: PRINT x

-> Somas, Subtrações, Multiplicações e Divisões.
Exemplo: x = 2 + 2, x = x - 4, y = x * 2, k = x / y

-> Labels.
Exemplo: LABEL L1, LABEL L2

-> Condições (saltos condicionais).
Exemplo: IF x GOTO L1 

-> Saltos.
Exemplo: GOTO L1

