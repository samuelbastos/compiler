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

AST_EXPLIST* expListNode(AST_EXPLIST* list, AST_EXP* exp)
{
    AST_EXPLIST* result = NEW(AST_EXPLIST);

    if(!list && exp)
    {
        list = NEW(AST_EXPLIST);
        list->exp = exp;
        list->next = NULL;
        list->last = NULL;
        result = list;
    }
    else if(list && exp)
    {
        AST_EXPLIST* newNode = NEW(AST_EXPLIST);
        newNode->next = NULL;
        newNode->last = list;
        newNode->exp = exp;
        list->next = newNode;
        result = list->next;
    }

    return result;
}

AST_CALL* callNode(char* id, AST_EXPLIST* list)
{
    AST_CALL* result = NEW(AST_CALL);

    result->id = id;
    result->list = list;

    return result;
}

AST_STAT* statReturnNode(STAT_TAG tag, AST_EXP* exp)
{
    AST_STAT* result = NEW(AST_STAT);

    result->tag = tag;
    result->statreturn.exp = exp;

    return result;
}

AST_STAT* statAttribNode(STAT_TAG tag, AST_VAR* var, AST_EXP* exp)
{
    AST_STAT* result = NEW(AST_STAT);

    result->tag = tag;
    result->statattrib.var = var;
    result->statattrib.exp = exp;

    return result;
}

AST_STAT* statPrintNode(STAT_TAG tag, AST_EXP* exp)
{
    AST_STAT* result = NEW(AST_STAT);

    result->tag = tag;
    result->statprint.exp = exp;

    return result;
}

AST_STAT* statCallNode(STAT_TAG tag, AST_CALL* call)
{
    AST_STAT* result = NEW(AST_STAT);

    result->tag = tag;
    result->statcall.call = call;

    return result;
}

AST_STAT* statBlockNode(STAT_TAG tag, AST_BLOCK* block)
{
    AST_STAT* result = NEW(AST_STAT);

    result->tag = tag;
    result->statblock.block = block;

    return result;
}

AST_STAT* statWhileNode(STAT_TAG tag, AST_EXP* exp, AST_BLOCK* block)
{
    AST_STAT* result = NEW(AST_STAT);

    result->tag = tag;
    result->statwhile.exp = exp;
    result->statwhile.block = block;

    return result;
}

AST_STAT* statIfNode(STAT_TAG tag, AST_EXP* exp, AST_BLOCK* block, AST_ELSE* elseNode)
{
    AST_STAT* result = NEW(AST_STAT);

    result->tag = tag;
    result->statif.exp = exp;
    result->statif.block = block;
    result->statif.elseNode = elseNode;

    return result;
}

AST_DEFVAR* defvarNode(char* id, AST_TYPE* type)
{
    AST_DEFVAR* result = NEW(AST_DEFVAR);

    result->id = id;
    result->type = type;

    return result;
}

AST_DEFVARLIST* defvarListNode(AST_DEFVARLIST* list, AST_DEFVAR* defvar)
{
    AST_DEFVARLIST* result = NEW(AST_DEFVARLIST);

    if(list && defvar)
    {
        AST_DEFVARLIST* newNode = NEW(AST_DEFVARLIST);
        newNode->next = NULL;
        newNode->last = list;
        newNode->defvar = defvar;
        list->next = newNode;
        result = list->next;
    }
    
    else if(!list && defvar)
    {
        AST_DEFVARLIST* newNode = NEW(AST_DEFVARLIST);
        newNode->next = NULL;
        newNode->last = NULL;
        newNode->defvar = defvar;
        list = newNode;
        result = list;
    }

    return result;
}

AST_STATLIST* statListNode(AST_STATLIST* list, AST_STAT* stat)
{
    AST_STATLIST* result = NEW(AST_STATLIST);

    if(list && stat)
    {
        AST_STATLIST* newNode = NEW(AST_STATLIST);
        newNode->next = NULL;
        newNode->last = list;
        newNode->stat = stat;
        list->next = newNode;
        result = list->next;
    }
    else if(!list && stat)
    {
        AST_STATLIST* newNode = NEW(AST_STATLIST);
        newNode->next = NULL;
        newNode->last = NULL;
        newNode->stat = stat;
        list = newNode;
        result = list;
    }

    return result;
}

AST_BLOCK* blockNode(AST_DEFVARLIST* defvarlist, AST_STATLIST* statlist)
{
    AST_BLOCK* result = NEW(AST_BLOCK);

    result->defvarlist = defvarlist;
    result->statlist = statlist;

    return result;
}

AST_ELSE* elseNode(AST_BLOCK* block)
{
    AST_ELSE* result = NEW(AST_ELSE);

    if(block)
        result->block = NULL;
    else
        result->block = block;

    return result;
}

AST_PARAM* paramNode(char* id, AST_TYPE* type)
{
    AST_PARAM* result = NEW(AST_PARAM);

    result->id = id;
    result->type = type;

    return result;
}

AST_PARAMLIST* paramListNode(AST_PARAMLIST* list, AST_PARAM* param)
{
    AST_PARAMLIST* result = NEW(AST_PARAMLIST);

    if(!list && param)
    {
        list = NEW(AST_PARAMLIST);
        list->param = param;
        list->next = NULL;
        list->last = NULL;
        result = list;
    }
    else if(list && param)
    {
        AST_PARAMLIST* newNode = NEW(AST_PARAMLIST);
        newNode->next = NULL;
        newNode->last = list;
        newNode->param = param;
        list->next = newNode;
        result = list->next;
    }

    return result;
}

AST_DEFFUNC* defFuncNode(char* id, AST_PARAMLIST* params, AST_TYPE* type, AST_BLOCK* block)
{
    AST_DEFFUNC* result = NEW(AST_DEFFUNC);
    result->id = id;
    result->params = params;
    result->type = type;
    result->block = block;

    return result;
}

AST_DEF* deffVarNode(DEF_TAG tag, AST_DEFVAR* defvar)
{
    AST_DEF* result = NEW(AST_DEF);
    result->tag = tag;
    result->defvar.defvar1 = defvar;

    return result;
}

AST_DEF* deffFuncNode(DEF_TAG tag, AST_DEFFUNC* deffunc)
{
    AST_DEF* result = NEW(AST_DEF);
    result->tag = tag;
    result->deffunc.deffunc1 = deffunc;

    return result;
}

AST_PROGRAM* programNode(AST_PROGRAM* program, AST_DEF* def)
{
    AST_PROGRAM* result = NEW(AST_PROGRAM);
    
    if(program && def)
    {
        AST_PROGRAM* newNode = NEW(AST_PROGRAM);
        newNode->next = NULL;
        newNode->last = program;
        newNode->def = def;
        program->next = newNode;
        result = program->next;
    }

    else if(!program && def)
    {
        AST_PROGRAM* newNode = NEW(AST_PROGRAM);
        newNode->next = NULL;
        newNode->last = NULL;
        newNode->def = def;
        program = newNode;
        result = program;
    }

    return result;  
}