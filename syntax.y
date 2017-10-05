%{
    #include <stdio.h>
    #include "ast.h"
    int yylex();
    int yyerror(char* s){ /*fprintf(stderr, "error: %s\n", s); */}
    int yydebug = 1;
    AST_PROGRAM* tree = NULL;
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
    AST_STAT* _stat;
    AST_DEFVAR* _defvar;
    AST_DEFVARLIST* _defvarlist;
    AST_STATLIST* _statlist;
    AST_BLOCK* _block;
    AST_ELSE* _else;
    AST_PARAM* _param;
    AST_PARAMLIST* _paramlist;
    AST_DEFFUNC* _deffunc;
    AST_DEF* _def;
    AST_PROGRAM* _program;
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
%type <_stat> statement
%type <_defvar> def_var
%type <_defvarlist> def_vars
%type <_statlist> statements
%type <_block> block
%type <_else> else_opt
%type <_param> param
%type <_paramlist> params
%type <_deffunc> def_func
%type <_def> def
%type <_program> program
%type <_program> start

%%

start : program {tree = $1;}

program : /* empty */  {$$ = NULL;}
        | program def  {$$ = programNode($1, $2);    }

def : def_var           {$$ = deffVarNode(DEF_VAR, $1);  }
    | def_func          {$$ = deffFuncNode(DEF_FUNC, $1);}

def_var : TK_ID ':' type ';' {$$ = defvarNode(yylval._id, $3);}

base_type  : TK_INTR   {$$ = typeIntNode(TYPE_INT);}
           | TK_CHAR   {$$ = typeCharNode(TYPE_CHAR);}
           | TK_FLOATR {$$ = typeFloatNode(TYPE_FLOAT);}
           | TK_VOID   {$$ = typeVoidNode(TYPE_VOID);}

type : base_type    {$$ = $1;}
     | type '[' ']' {typeIndexedNode($1); $$ = $1;}

def_func : TK_ID '(' params ')' ':' type block {$$ = defFuncNode(yylval._id, $3, $6, $7); }

params : /* vazio */            {$$ = NULL;                    }
       | param                  {$$ = paramListNode(NULL, $1); }
       | params ',' param       {$$ = paramListNode($1, $3);   }

param : TK_ID ':' type {$$ = paramNode($1, $3);}

block : '{' def_vars statements '}' {$$ = blockNode($2, $3);}

def_vars : /* vazio */      {$$ = NULL;                     }
         | def_vars def_var {$$ = defvarListNode($1, $2);   }

statement : block                    {$$ = statBlockNode(STAT_BLOCK, $1);      }
          | TK_RETURN exp ';'        {$$ = statReturnNode(STAT_RETURN, $2);    }
          | TK_RETURN ';'            {$$ = statReturnNode(STAT_RETURN, NULL);  }
          | var '=' exp ';'          {$$ = statAttribNode(STAT_ATTRIB, $1, $3);}
          | '@' exp ';'              {$$ = statPrintNode(STAT_PRINT, $2);      }
          | call ';'                 {$$ = statCallNode(STAT_CALL, $1);        }
          | TK_WHILE exp block       {$$ = statWhileNode(STAT_WHILE, $2, $3);  }
          | TK_IF exp block else_opt {$$ = statIfNode(STAT_IF, $2, $3, $4);    }

else_opt : /* empty */   {$$ = elseNode(NULL); }
         | TK_ELSE block {$$ = elseNode($2);   }

call : TK_ID '(' exp_list ')' {$$ = callNode(yylval._id, $3);}

exp_list : /* vazio */       {$$ = NULL;                    }
         | exp               {$$ = expListNode(NULL, $1);   }
         | exp_list ',' exp  {$$ = expListNode($1, $3);     }

var : TK_ID               {$$ = varIdNode(VAR_ID, yylval._id);}
    | var_exp '[' exp ']' {$$ = varIndexedNode(VAR_INDEXED, $1, $3);}


statements : /* vazio */          {$$ = NULL;                    }
           | statement statements {$$ = statListNode($2, $1);    }

exp : op_prec {$$ = $1;}

new_exp : TK_NEW type '[' exp ']' {$$ = expNewNode(EXP_NEW, $4, $2);}

op_prec : op_prec TK_OR and_exp  {$$ = expBinNode(EXP_OR, $1, $3);}
        | and_exp                {$$ = $1;}

and_exp : and_exp TK_AND cmp_exp {$$ = expBinNode(EXP_AND, $1, $3);}
        | cmp_exp                {$$ = $1;}

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
         | var_exp            {$$ = $1;}

var_exp : call        {$$ = expCallNode(EXP_CALL, $1);}
        | number      {$$ = $1;}
        | TK_STRING   {$$ = expStringNode(EXP_STR, yylval._string);}
        | '(' exp ')' {$$ = $2;}
        | new_exp     {$$ = $1;}
        | var         {$$ = expVarNode(EXP_VAR, $1);}

number : TK_INT   {$$ = expIntNode(EXP_INT, yylval._int); }
       | TK_FLOAT {$$ = expFloatNode(EXP_FLT, yylval._float);}