#include "ast.h"

void* mymalloc(size_t size)
{
	void* out = malloc(size);
	if(!out) printf("Malloc error\n");
	return out;
}

AST_EXP* expBinNode(EXP_TAG tag, AST_EXP *e1, AST_EXP *e2)
{
	AST_EXP* result = NEW (AST_EXP);
	result->tag = tag;
	result->binop.e1 = e1;
	result->binop.e2 = e2;

	return result;
}

AST_EXP* expUnaryNode(EXP_TAG tag, AST_EXP *e1)
{
	AST_EXP* result = NEW (AST_EXP);
	result->tag = tag;
	result->unaryop.e1 = e1;

	return result;
}

AST_EXP* expSuffixedNode(EXP_TAG tag, AST_EXP *e1, AST_TYPE* type)
{
	AST_EXP* result = NEW(AST_EXP);
	result->tag = tag;
	result->suffixedop.e1 = e1;
	result->suffixedop.type = type;

	return result;
}

AST_EXP* expIntNode(EXP_TAG tag, int val)
{
	AST_EXP* result = NEW (AST_EXP);
	result->tag = tag;
	result->expint.val = val;

	return result;
}

AST_EXP* expFloatNode(EXP_TAG tag, float val)
{
	AST_EXP* result = NEW (AST_EXP);
	result->tag = tag;
	result->expfloat.val = val;

	return result;
}

AST_EXP* expStringNode(EXP_TAG tag, char* string)
{
	AST_EXP* result = NEW (AST_EXP);
	result->tag = tag;
	result->expstring.string = string;

	return result;
}


AST_EXP* expNewNode(EXP_TAG tag, AST_EXP *e1, AST_TYPE* type)
{
	AST_EXP* result = NEW(AST_EXP);
	result->tag = tag;
	result->expnew.e1 = e1;
	result->expnew.type = type;

	return result;
}

AST_EXP* expVarNode(EXP_TAG tag, AST_VAR* var)
{
	AST_EXP* result = NEW(AST_EXP);
	result->tag = tag;
	result->expvar.var = var;

	return result;
}

AST_EXP* expCallNode(EXP_TAG tag, AST_CALL* call)
{
	AST_EXP* result = NEW(AST_EXP);
	result->tag = tag;
	result->expcall.call = call;

	return result;
}

AST_TYPE* typeIntNode(TYPE_TAG tag)
{
	AST_TYPE* result = NEW(AST_TYPE);
	result->tag = tag;
	result->typeint.indexed = 0;

	return result;
}

AST_TYPE* typeFloatNode(TYPE_TAG tag)
{
	AST_TYPE* result = NEW(AST_TYPE);
	result->tag = tag;
	result->typefloat.indexed = 0;

	return result;
}

AST_TYPE* typeCharNode(TYPE_TAG tag)
{
	AST_TYPE* result = NEW(AST_TYPE);
	result->tag = tag;
	result->typechar.indexed = 0;

	return result;
}

AST_TYPE* typeVoidNode(TYPE_TAG tag)
{
	AST_TYPE* result = NEW(AST_TYPE);
	result->tag = tag;
	result->typevoid.indexed = 0;

	return result;
}

void typeIndexedNode(AST_TYPE* type)
{
	switch(type->tag)
	{
		case TYPE_INT:
			type->typeint.indexed += 1;
			break;

		case TYPE_FLOAT:
			type->typefloat.indexed += 1;
			break;

		case TYPE_CHAR:
			type->typefloat.indexed +=1;
			break;

		case TYPE_VOID:
			type->typevoid.indexed +=1;
			break;
	}
}

AST_VAR* varIdNode(VAR_TAG tag, char* id)
{
	AST_VAR* result = NEW(AST_VAR);
	result->tag = tag;
	result->varid.id = id;

	return result;
}

AST_VAR* varIndexedNode(VAR_TAG tag, AST_EXP* outter, AST_EXP* inner)
{
	AST_VAR* result = NEW(AST_VAR);
	result->tag = tag;
	result->varindexed.inner = inner;
	result->varindexed.outter = outter;

	return result;
}

AST_EXPLIST* expListNode(EXPLIST_TAG tag, AST_EXPLIST* list, AST_EXP* exp)
{
	AST_EXPLIST* result = NEW(AST_EXPLIST);

	if(list == NULL)
	{
		list = NEW(AST_EXPLIST);
		list->exp = exp;
		list->next= NULL;
	}
	else
	{
		AST_EXPLIST* newNode = NEW(AST_EXPLIST);
		newNode->next = NULL;
		newNode->exp = exp;
		list->next = newNode;
	}

	result = list;
	return result;
}

AST_CALL* callNode(char* id, AST_EXPLIST* list)
{
	AST_CALL* result = NEW(AST_CALL);

	result->id = id;
	result->list = list;

	return result;
}