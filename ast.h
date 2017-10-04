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
	EXPLIST_EMPTY,
	EXPLIST_UNIQUE,
	EXPLIST_ADD,
} EXPLIST_TAG;

typedef union AST_EXP AST_EXP;
typedef union AST_TYPE AST_TYPE;
typedef union AST_VAR AST_VAR;
typedef struct AST_EXPLIST AST_EXPLIST;
typedef struct AST_CALL AST_CALL;

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
};

struct AST_CALL {

	char* id;
	AST_EXPLIST* list;
};

void* mymalloc(size_t size);

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

AST_EXPLIST* expListNode(EXPLIST_TAG tag, AST_EXPLIST* list, AST_EXP* exp);

AST_CALL* callNode(char* id, AST_EXPLIST* list);