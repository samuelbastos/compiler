/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_SYNTAX_TAB_H_INCLUDED
# define YY_YY_SYNTAX_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TK_AS = 258,
    TK_CHAR = 259,
    TK_ELSE = 260,
    TK_FLOATR = 261,
    TK_IF = 262,
    TK_INTR = 263,
    TK_NEW = 264,
    TK_RETURN = 265,
    TK_VOID = 266,
    TK_WHILE = 267,
    TK_SUM = 268,
    TK_SUB = 269,
    TK_MULT = 270,
    TK_DIV = 271,
    TK_EQ = 272,
    TK_NEQ = 273,
    TK_LEQ = 274,
    TK_GEQ = 275,
    TK_LESS = 276,
    TK_GREATER = 277,
    TK_NOT = 278,
    TK_AND = 279,
    TK_OR = 280,
    TK_BLANK = 281,
    TK_INT = 282,
    TK_HEXA = 283,
    TK_FLOAT = 284,
    TK_COMMENT = 285,
    TK_STRING = 286,
    TK_ID = 287
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 10 "syntax.y" /* yacc.c:1909  */

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

#line 111 "syntax.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SYNTAX_TAB_H_INCLUDED  */
