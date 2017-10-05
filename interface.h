#include "ast.h"
#include "syntax.tab.h"
/** Parser function */
int yyparse();

/** AST generated */
extern AST_PROGRAM* tree;