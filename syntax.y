%{
	#include <stdio.h>
	#include "ast.h"
	int yylex();
	int yyerror(char* s){ /*fprintf(stderr, "error: %s\n", s); */}
	int yydebug = 1;
%}

%union {
	int _int;
	float _float;
	char* _string;
	char* _id;
	AST_EXP* _exp;
	AST_TYPE* _type;
	AST_VAR* _var;
	AST_EXPLIST* _explist;
	AST_CALL* _call;
};

%token <_int> TK_AS
%token <_int> TK_CHAR
%token <_int> TK_ELSE
%token <_int> TK_FLOATR
%token <_int> TK_IF
%token <_int> TK_INTR
%token <_int> TK_NEW
%token <_int> TK_RETURN
%token <_int> TK_VOID
%token <_int> TK_WHILE
%token <_int> TK_SUM
%token <_int> TK_SUB
%token <_int> TK_MULT
%token <_int> TK_DIV
%token <_int> TK_EQ
%token <_int> TK_NEQ
%token <_int> TK_LEQ
%token <_int> TK_GEQ
%token <_int> TK_LESS
%token <_int> TK_GREATER
%token <_int> TK_NOT
%token <_int> TK_AND
%token <_int> TK_OR
%token <_int> TK_BLANK
%token <_int> TK_INT
%token <_int> TK_HEXA
%token <_float> TK_FLOAT
%token <_int> TK_COMMENT
%token <_string> TK_STRING
%token <_id> TK_ID

%type <_exp> exp op_prec and_exp arith_pm arith_dm cmp_exp prefixed suffixed var_exp number new_exp
%type <_type> base_type type
%type <_var> var
%type <_explist> exp_list
%type <_call> call

%%

program : program def
		| def

def : def_var 
	| def_func 


def_var : TK_ID ':' type ';' { printf("DEF_VAR\n"); }

base_type  : TK_INTR   {$$ = typeIntNode(TYPE_INT);}
	  	   | TK_CHAR   {$$ = typeCharNode(TYPE_CHAR);}
	       | TK_FLOATR {$$ = typeFloatNode(TYPE_FLOAT);}
	       | TK_VOID   {$$ = typeVoidNode(TYPE_VOID);}

type : base_type    {$$ = $1;}
 	 | type '[' ']' {typeIndexedNode($1); $$ = $1;}

def_func : TK_ID '(' params ')' ':' type block { printf("DEF_FUNC\n"); }

params : /* vazio */
	   | param
	   | params ',' param

param : TK_ID ':' type {printf("PARAM\n");}

block : '{' def_vars statements '}'

def_vars : /* vazio */
		 | def_vars def_var

statement : block 			    	 { printf("BLOCK_BEGINS\n"); }
		  | TK_RETURN exp ';'   	 { printf("RETURN_EXP\n");   }
		  | TK_RETURN ';'	    	 { printf("RETURN_NULL\n");  }
		  | var '=' exp ';'     	 { printf("ATTRIB\n");       }
		  | '@' exp ';'		    	 { printf("PRINT_EXP\n");    }
		  | call ';'		    	 { printf("FUNC_CALL\n");    }
		  | TK_WHILE exp block  	 { printf("WHILE_BEGINS\n"); }
		  | TK_IF exp block else_opt { printf("IF_BEGINS\n");    }

else_opt : /* empty */
		 | TK_ELSE block { printf("ELSE_BEGINS\n"); }

call : TK_ID '(' exp_list ')' {$$ = callNode(yylval._id, $3);}

exp_list : /* vazio */       {$$ = expListNode(EXPLIST_EMPTY, NULL, NULL);} /* verificar esse cara direito */
		 | exp               {$$ = expListNode(EXPLIST_UNIQUE, NULL, $1); }
		 | exp_list ',' exp  {$$ = expListNode(EXPLIST_ADD, $1, $3);      }

var : TK_ID               {$$ = varIdNode(VAR_ID, yylval._id);}
	| var_exp '[' exp ']' {$$ = varIndexedNode(VAR_INDEXED, $1, $3);}


statements : /* vazio */
		   | statement statements

exp : op_prec {$$ = $1;}

new_exp : TK_NEW type '[' exp ']' {$$ = expNewNode(EXP_NEW, $4, $2);}

op_prec : op_prec TK_OR and_exp  {$$ = expBinNode(EXP_OR, $1, $3);}
	    | and_exp                {$$ = $1;}

and_exp : and_exp TK_AND cmp_exp {$$ = expBinNode(EXP_AND, $1, $3);}
		| cmp_exp 			     {$$ = $1;}

cmp_exp : cmp_exp TK_EQ arith_pm      {$$ = expBinNode(EXP_EQ, $1, $3);     }
		| cmp_exp TK_NEQ arith_pm     {$$ = expBinNode(EXP_NEQ, $1, $3);    } 
		| cmp_exp TK_LESS arith_pm    {$$ = expBinNode(EXP_LESS, $1, $3);   }
		| cmp_exp TK_GREATER arith_pm {$$ = expBinNode(EXP_GREATER, $1, $3);} 
		| cmp_exp TK_LEQ arith_pm     {$$ = expBinNode(EXP_LEQ, $1, $3);    }
		| cmp_exp TK_GEQ arith_pm     {$$ = expBinNode(EXP_GEQ, $1, $3);    }
		| arith_pm                    {$$ = $1;}

arith_pm : arith_pm TK_SUM arith_dm {$$ = expBinNode(EXP_SUM, $1, $3);} 
		 | arith_pm TK_SUB arith_dm {$$ = expBinNode(EXP_SUB, $1, $3);}
		 | arith_dm                 {$$ = $1;}
 
arith_dm : arith_dm TK_MULT prefixed {$$ = expBinNode(EXP_MULT, $1, $3);}
		 | arith_dm TK_DIV prefixed  {$$ = expBinNode(EXP_DIV, $1, $3);}
		 | prefixed                  {$$ = $1;}

prefixed : TK_NOT suffixed {$$ = expUnaryNode(EXP_NOT, $2);}
		 | TK_SUB suffixed {$$ = expUnaryNode(EXP_MINUS, $2);}
		 | suffixed        {$$ = $1;}

suffixed : var_exp TK_AS type {$$ = expSuffixedNode(EXP_AS, $1, $3);}
		 | var_exp 			  {$$ = $1;}

var_exp : call        {$$ = expCallNode(EXP_CALL, $1);}
		| number      {$$ = $1;}
		| TK_STRING   {$$ = expStringNode(EXP_STR, yylval._string);}
		| '(' exp ')' {$$ = $2;}
		| new_exp     {$$ = $1;}
		| var         {$$ = expVarNode(EXP_VAR, $1);}

number : TK_INT   {$$ = expIntNode(EXP_INT, yylval._int); }
	   | TK_FLOAT {$$ = expFloatNode(EXP_FLT, yylval._float);}