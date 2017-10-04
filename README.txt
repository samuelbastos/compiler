/*
 * INF1715 - Compiladores
 * Samuel Bastos - 1311416
 */

/** MODO DE USO */

(I)  - utilizar o comando make para gerar o executável utilizando o bison e o flex
(II) - com o bash, utilizar ./run.sh para executar o programa e o script 
       python de teste para checar se o  o resultado obtido no output ao
       ler o input é o esperado.

OBS: Se houver problema de permissão com o script bash, utilizar chmod u+x run.sh .

/** SOURCE  */

Makefile   			: gera os analisadores léxico e sintático e compila eles com a main;
run.sh     			: executa a main e roda os scripts de testes;

a.out      			: programa executável que varre o stdin;

analyser.l 			: programa que é usado para gerar o analisador léxico
syntax.y            : programa que é usado para gerar o analisador sintático

xxx_input.txt  		: arquivo texto que é usado como stdin e da onde serão obtidos os tokens para o teste xxx;
xxx_output.txt      : arquivo texto contendo o resultado do parse do programa para o teste xxx;
xxx_expected.txt    : resultado esperado ao varrer o arquivo inteiro de entrada para o teste xxx;
result_xxx.txt      : arquivo texto que compara o resultado esperado com o resultado obtido para o teste xxx;

interface.h    		: interface do analisador sintático com o programa principal;
main.c     			: programa principal que roda o parser e varre o input até o fim do arquivo
lex.yy.c            : analisador léxico gerado pelo flex ao ler o arquivo analyser.l;

arquivos syntax.xxx : arquivos gerados pelo bison para uso do parser criado;

test_results.py     : script que irá fazer comparação entre os resultados esperados e os resultados obtidos da varredura do input;