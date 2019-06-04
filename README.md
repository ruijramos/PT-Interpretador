# LabProg---Interpreter-
Intrepetador de linguagem de programação definida.

Pretende-se escrever um interpretador para uma linguagem de programação definida por um conjunto de instruções relativamente pequeno.


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

- Terminar a execução do programa:
quit;



Um exemplo de uso desta linguagem:


ler(k);

p= 6 + k;

if p goto L1;

p = p/2;

escrever(p);

goto L2;

label L1;

p = 2*p;

escrever(p);

label L2;

quit;
