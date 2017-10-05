#include <stdlib.h>
#include <stdio.h>

#define NEW(T) ((T*)mymalloc(sizeof(T)))

typedef enum {

    EXP_VAR,
    EXP_CALL,
    EXP_INT,
    EXP_FLT,
    EXP_STR,
    EXP_NEW,
    EXP_AND,
    EXP_OR,
    EXP_EQ,
    EXP_NEQ,
    EXP_LESS,
    EXP_GREATER,
    EXP_LEQ,
    EXP_GEQ,
    EXP_SUM,
    EXP_SUB,
    EXP_MULT,
    EXP_DIV,
    EXP_NOT,
    EXP_MINUS,
    EXP_AS,

} EXP_TAG;

typedef enum {

    TYPE_INT,
    TYPE_FLOAT,
    TYPE_CHAR,
    TYPE_VOID,

} TYPE_TAG;

typedef enum {

    VAR_ID,
    VAR_INDEXED,

} VAR_TAG;

typedef enum {

    STAT_BLOCK,
    STAT_RETURN,
    STAT_ATTRIB,
    STAT_PRINT,
    STAT_CALL,
    STAT_WHILE,
    STAT_IF,

} STAT_TAG;

typedef enum {

    DEF_VAR,
    DEF_FUNC,

} DEF_TAG;

typedef union AST_EXP AST_EXP;
typedef union AST_TYPE AST_TYPE;
typedef union AST_VAR AST_VAR;
typedef struct AST_EXPLIST AST_EXPLIST;
typedef struct AST_CALL AST_CALL;
typedef union AST_STAT AST_STAT;
typedef struct AST_DEFVAR AST_DEFVAR;
typedef struct AST_DEFVARLIST AST_DEFVARLIST;
typedef struct AST_STATLIST AST_STATLIST;
typedef struct AST_BLOCK AST_BLOCK;
typedef struct AST_ELSE AST_ELSE;
typedef struct AST_PARAM AST_PARAM;
typedef struct AST_PARAMLIST AST_PARAMLIST;
typedef struct AST_DEFFUNC AST_DEFFUNC;
typedef union AST_DEF AST_DEF;
typedef struct AST_PROGRAM AST_PROGRAM;

union AST_EXP {

    EXP_TAG tag;

    struct {
        EXP_TAG tag;
        AST_EXP *e1, *e2;
    } binop;

    struct {
        EXP_TAG tag;
        AST_EXP *e1;
    } unaryop;

    struct {
        EXP_TAG tag;
        AST_EXP* e1;
        AST_TYPE* type;
    } suffixedop;

    struct {
        EXP_TAG tag;
        int val;
    } expint;

    struct {
        EXP_TAG tag;
        float val;
    } expfloat;

    struct {
        EXP_TAG tag;
        char* string;
    } expstring;

    struct {
        EXP_TAG tag;
        AST_EXP* e1;
        AST_TYPE* type;
    } expnew;

    struct {
        EXP_TAG tag;
        AST_VAR* var;
    } expvar;

    struct {
        EXP_TAG tag;
        AST_CALL* call;
    } expcall;

};

union AST_TYPE {

    TYPE_TAG tag;

    struct {
        TYPE_TAG tag;
        int indexed;
    } typeint;

    struct {
        TYPE_TAG tag;
        int indexed;
    } typefloat;

    struct {
        TYPE_TAG tag;
        int indexed;
    } typechar;

    struct {
        TYPE_TAG tag;
        int indexed;
    } typevoid;
};

union AST_VAR {

    VAR_TAG tag;

    struct {
        VAR_TAG tag;
        char* id;
    } varid;

    struct {
        VAR_TAG tag;
        AST_EXP* outter;
        AST_EXP* inner;
    }  varindexed;
};

struct AST_EXPLIST {

    AST_EXP* exp;
    AST_EXPLIST* next;
    AST_EXPLIST* last;
};

struct AST_CALL {

    char* id;
    AST_EXPLIST* list;
};

union AST_STAT {

    STAT_TAG tag;

    struct {
        STAT_TAG tag;
        AST_EXP* exp;
    } statreturn;

    struct {
        STAT_TAG tag;
        AST_VAR* var;
        AST_EXP* exp;
    } statattrib;

    struct {
        STAT_TAG tag;
        AST_EXP* exp;
    } statprint;

    struct {
        STAT_TAG tag;
        AST_CALL* call;
    } statcall;

    struct {
        STAT_TAG tag;
        AST_BLOCK* block;
    } statblock;

    struct {
        STAT_TAG tag;
        AST_EXP* exp;
        AST_BLOCK* block;
    } statwhile;

    struct {
        STAT_TAG tag;
        AST_EXP* exp;
        AST_BLOCK* block;
        AST_ELSE* elseNode;
    } statif;
};


struct AST_DEFVAR {

    char* id;
    AST_TYPE* type;
};

struct AST_DEFVARLIST {

    AST_DEFVAR* defvar;
    AST_DEFVARLIST* next;
    AST_DEFVARLIST* last;
};

struct AST_STATLIST {

    AST_STAT* stat;
    AST_STATLIST* next;
    AST_STATLIST* last;
};

struct AST_BLOCK {

    AST_DEFVARLIST* defvarlist;
    AST_STATLIST* statlist;
};

struct AST_ELSE {

    AST_BLOCK* block;
};

struct AST_PARAM {

    char* id;
    AST_TYPE* type;
};

struct AST_PARAMLIST {

    AST_PARAM* param;
    AST_PARAMLIST* next;
    AST_PARAMLIST* last;
};

struct AST_DEFFUNC {

    char* id;
    AST_PARAMLIST* params;
    AST_TYPE* type;
    AST_BLOCK* block;
};

union AST_DEF {
    DEF_TAG tag;

    struct {
        DEF_TAG tag;
        AST_DEFVAR* defvar1;
    } defvar;

    struct {
        DEF_TAG tag;
        AST_DEFFUNC* deffunc1;
    } deffunc;
};

struct AST_PROGRAM {

    AST_DEF* def;
    AST_PROGRAM* next;
    AST_PROGRAM* last;
};

AST_EXP* expBinNode(EXP_TAG tag, AST_EXP *e1, AST_EXP *e2);
AST_EXP* expUnaryNode(EXP_TAG tag, AST_EXP *e1);
AST_EXP* expSuffixedNode(EXP_TAG tag, AST_EXP *e1, AST_TYPE* type);
AST_EXP* expIntNode(EXP_TAG tag, int val);
AST_EXP* expFloatNode(EXP_TAG tag, float val);
AST_EXP* expStringNode(EXP_TAG tag, char* string);
AST_EXP* expNewNode(EXP_TAG tag, AST_EXP *e1, AST_TYPE* type);
AST_EXP* expVarNode(EXP_TAG tag, AST_VAR* var);
AST_EXP* expCallNode(EXP_TAG tag, AST_CALL* call);

AST_TYPE* typeIntNode(TYPE_TAG tag);
AST_TYPE* typeFloatNode(TYPE_TAG tag);
AST_TYPE* typeCharNode(TYPE_TAG tag);
AST_TYPE* typeVoidNode(TYPE_TAG tag);
void typeIndexedNode(AST_TYPE* type);

AST_VAR* varIdNode(VAR_TAG tag, char* id);
AST_VAR* varIndexedNode(VAR_TAG tag, AST_EXP* outter, AST_EXP* inner);

AST_EXPLIST* expListNode(AST_EXPLIST* list, AST_EXP* exp);

AST_CALL* callNode(char* id, AST_EXPLIST* list);

AST_STAT* statReturnNode(STAT_TAG tag, AST_EXP* exp);
AST_STAT* statAttribNode(STAT_TAG tag, AST_VAR* var, AST_EXP* exp);
AST_STAT* statPrintNode(STAT_TAG tag, AST_EXP* exp);
AST_STAT* statCallNode(STAT_TAG tag, AST_CALL* call);
AST_STAT* statBlockNode(STAT_TAG tag, AST_BLOCK* block);
AST_STAT* statWhileNode(STAT_TAG tag, AST_EXP* exp, AST_BLOCK* block);
AST_STAT* statIfNode(STAT_TAG tag, AST_EXP* exp, AST_BLOCK* block, AST_ELSE* elseNode);

AST_DEFVAR* defvarNode(char* id, AST_TYPE* type);

AST_DEFVARLIST* defvarListNode(AST_DEFVARLIST* list, AST_DEFVAR* defvar);

AST_STATLIST* statListNode(AST_STATLIST* list, AST_STAT* stat);

AST_BLOCK* blockNode(AST_DEFVARLIST* defvarlist, AST_STATLIST* statlist);

AST_ELSE* elseNode(AST_BLOCK* block);

AST_PARAM* paramNode(char* id, AST_TYPE* type);

AST_PARAMLIST* paramListNode(AST_PARAMLIST* list, AST_PARAM* param);

AST_DEFFUNC* defFuncNode(char* id, AST_PARAMLIST* params, AST_TYPE* type, AST_BLOCK* block);

AST_DEF* deffVarNode(DEF_TAG tag, AST_DEFVAR* defvar);
AST_DEF* deffFuncNode(DEF_TAG tag, AST_DEFFUNC* deffunc);

AST_PROGRAM* programNode(AST_PROGRAM* program, AST_DEF* def);