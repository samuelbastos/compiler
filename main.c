/*
 * INF1715 - Compiladores
 * Samuel Bastos - 1311416
 */

#include <stdio.h>
#include "interface.h"

int main(void)
{
	int flag;
	AST_PROGRAM* iter;

	if(!yyparse())
	{
		printf("SUCCESS\n");

		for(iter = tree; iter != NULL; iter = iter->last)
		{
			flag = iter->def->tag;

			printf("FLAG: %d ", flag);			
			printf("ola\n");
		}
	} 
	else 
		printf("FAILURE");

	return 0;
}