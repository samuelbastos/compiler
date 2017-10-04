/*
 * INF1715 - Compiladores
 * Samuel Bastos - 1311416
 */

%option noyywrap

%{
#include "ast.h"
#include "syntax.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** Converte escape */
static char convertEscape(char escape);

/** converte string para literal (sem escape e aspas) */
static char* convertToLiteral(char* string);

%}

/* palavras reservadas */
as as
char char
else else
floatr float
if if
intr int
new new
return return
void void
while while

/* operadores */
sum \+
sub -
mult \*
div \/
eq ==
neq ~=
leq <=
geq >=
less <
greater >
not !
and &&
or \|\|

/* other stuff */

/* expressões regulares */
blank    [ \n\t]+
int      [0-9]+
hexa     0[Xx][0-9a-fA-F]+
float    [0-9]*\.[0-9]+([Ee][-+]?[0-9]+)?
comment  "#".*\n
string   \"([^\n\\"]|\\.)*\"
id       ([a-z]|[A-Z])([a-z]|[A-Z]|[0-9])*
any      .

%%
{as}      {return TK_AS;}
{char}    {return TK_CHAR;}
{else}    {return TK_ELSE;}
{floatr}  {return TK_FLOATR;}
{if}      {return TK_IF;}
{intr}    {return TK_INTR;}
{new}     {return TK_NEW;}
{return}  {return TK_RETURN;}
{void}    {return TK_VOID;}
{while}   {return TK_WHILE;}

{sum}     {return TK_SUM;}
{sub}     {return TK_SUB;}
{mult}    {return TK_MULT;}
{div}     {return TK_DIV;}
{eq}      {return TK_EQ;}
{neq}     {return TK_NEQ;}
{leq}     {return TK_LEQ;}
{geq}     {return TK_GEQ;}
{less}    {return TK_LESS;}
{greater} {return TK_GREATER;}
{not}     {return TK_NOT;}
{and}     {return TK_AND;}
{or}      {return TK_OR;}

{int}     {yylval._int = (int)strtol(yytext, 0, 10); return TK_INT;}
{hexa}    {yylval._int = (int)strtol(yytext, 0, 16); return TK_INT;}
{blank}   {}
{float}   {yylval._float = (float)strtod(yytext, NULL); return TK_FLOAT;}
{comment} {return TK_COMMENT;}
{id}      {yylval._id = yytext; return TK_ID;}
{string}  {yylval._string = convertToLiteral(yytext); return TK_STRING;}
{any}     {return yytext[0];}
%%


static char convertEscape(char escape)
{
    switch (escape)
    {
        case '\\':
        case '"':
            return escape;
        case 'n':
            return '\n';
        case 't':
            return '\t';
    }
    return 0;
}

static char* convertToLiteral(char* string)
{
    size_t len = strlen(string) - 2;
    char* out = (char*)malloc(len + 1);
    int i = 0;
    string++;
    while (*string != '"')
    {
        char c = *string++;
        if (c == '\\')
            c = convertEscape(*string++);
        out[i++] = c;
    }
    out[i] = '\0';
    return out;
}
