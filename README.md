# Pratica-Estrutura-de-dados
O programa consiste em uma atividade pratica de estrutura de dados, em que serão recebidas linhas no input, e as mesmas serão pre-processadas e alocadas na memoria em alguma estrutura de dados.
A ideia do trabalho foi do prof. Flávio Assis, professor da UFBA.
Para utilizar o programa, seguem as instruções.

A entrada constará inicialmente de uma linha contendo um valor inteiro, seguida por uma seqüência
de linhas de texto, seguida de uma seção de comandos.
O número que aparece na primeira linha indica o número total de linhas de texto que aparecerão
em seguida. Cada linha de texto pode ter, no máximo, 50 caracteres (incluindo espaços). Considere
que o tamanho máximo de uma palavra é de 29 letras. Em uma palavra somente podem ocorrer letras
minúsculas, sem acento e sem cedilha.
Em seguida, os seguintes comandos e suas estruturas poderão ocorrer:
1. lista linhas em que uma determinada palavra ocorre: este comando consistirá de uma
linha contendo a letra ’l’, seguida por uma linha contendo uma palavra.
Este comando retorna, em uma única linha, os números das linhas em que a palavra ocorre. Um
número de linha deve estar separado por outro por um único espaço. Não deve haver espaço
após o último número de linha. Caso a palavra dada não ocorrer no texto, este comando não
gera nenhuma saída (nem uma linha em branco). Considere que a primeira linha de texto é a
linha de número 1.
2. lista palavras por número de letras: este comando consistirá de uma linha contendo a letra
’x’, seguida por uma linha contendo um número (qualquer valor inteiro positivo). O comando
lista as palavras que ocorrem no texto e que possuem exatamente o número de letras indicado
na segunda linha do comando.
Este comando apresenta na saída uma palavra por linha, em ordem alfabética, sem repetir
palavras. Caso não haja palavras com o número de letras dado, o programa não gera nenhuma
saída (nem uma linha em branco).
3. lista palavras em ordem alfabética: este comando será formado por quatro linhas. Na
primeira linha ocorrerá a letra ’o’. Na segunda, a letra ’c’ ou ’d’. Na terceira e na quarta linha,
ocorrerá, em cada uma, uma palavra. Seja palavralinha3 a palavra que ocorre na terceira linha
do comando e palavralinha4 a palavra que ocorre na quarta linha. Se a segunda linha contiver
a letra ’c’, o comando listará as palavras que ocorrem no texto em ordem crescente que sejam
maiores (de acordo com a ordem alfabética) ou iguais a palavralinha3 e menores (de acordo
com a ordem alfabética) ou iguais a palavralinha4. Se a segunda linha contiver a letra ’d’, o
comando listará as palavras que ocorrem no texto em ordem decrescente que sejam menores (de
1
acordo com a ordem alfabética) ou iguais a palavralinha3 e maiores (de acordo com a ordem
alfabética) ou iguais a palavralinha4.
Este comando retorna uma palavra por linha, na ordem solicitada, sem repetir palavras. Caso
não haja palavras a serem retornadas, o programa não gera nenhuma saída (nem uma linha em
branco).
4. número de vezes em que uma palavra ocorre: este comando consistirá de uma linha
contendo a letra ’n’, seguida por uma segunda linha contendo uma palavra.
Este comando gera uma linha, contendo a palavra, seguida de um espaço, seguido do número de
vezes em que a palavra ocorre. Caso a palavra dada não ocorra no texto, o comando gera zero
como sendo o número de vezes em que a palavra ocorre.
5. lista todas as palavras: este comando consistirá de uma única linha contendo a letra ’a’.
Este comando retorna uma palavra por linha, em ordem alfabética, sem repetir palavras. Caso o
texto não contenha palavras, o programa não gera nenhuma saída (nem uma linha em branco).
6. término da seqüência de comandos: a seqüência de comandos será terminada por uma linha
com a letra ’e
