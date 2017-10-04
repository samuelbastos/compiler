/*
 * INF1715 - Compiladores
 * Samuel Bastos - 1311416
 */

#include <stdio.h>
#include "interface.h"

int main(void)
{
	if(!yyparse()) printf("SUCCESS");
	else printf("FAILURE");

	return 0;
}