all:
	flex analyser.l
	bison -d syntax.y
	gcc main.c  ast.c syntax.tab.c lex.yy.c