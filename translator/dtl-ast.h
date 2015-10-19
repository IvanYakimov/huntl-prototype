/* Based upon John Levine's book "flex&bison" */

#ifndef _ABSTRACT_SYNTAX_TREE_H
#define _ABSTRACT_SYNTAX_TREE_H

//#include "dtl-scanner.h"

typedef enum
{
    typeFunctionOp,      	/* ������� */
    typeConst,            	/* ��������� */
    typeIdentifier,        	/* ���������� */
    typeList,               /* ������ ��������� ��� ���������� */
	typeImplement,			/* �������� ��������� */
} NodeTypeEnum;


/* ��������� ���� ������������ ��������������� ������ */
/* � ������ ���� ������ ���� ���������� �������� ��� */

typedef struct /*TAbstractSyntaxTreeNode*/
{
  NodeTypeEnum nodetype;
  char* opValue;
  struct TAbstractSyntaxTreeNode* left;
  struct TAbstractSyntaxTreeNode* right;
} NodeAST;

typedef struct
{
  NodeTypeEnum nodetype;        /* ��� typeIfStatement */
  NodeAST* condition;  /* ������� */
  NodeAST* trueBranch; /* ��������� true-����� */
  NodeAST* elseBranch; /* ��������� �������������� false-����� */
} TControlFlowNode;

typedef struct
{
  NodeTypeEnum nodetype;			/* ��� K */
  int value;
} TNumericValueNode;

#ifndef _SYMBOL_TABLE_H
#include "symtable.h"
#endif

typedef struct
{
  NodeTypeEnum nodetype;
  TSymbolTableRecord* function;
} TSymbolTableReference;

typedef struct
{
  NodeTypeEnum nodetype;
  TSymbolTableRecord* variable;
  NodeAST* value;
} TFunctionNode;

/* ��������� ������������ ������������ ��������������� ������ */
NodeAST* CreateNodeAST(NodeTypeEnum cmptype, char* opValue,
//					   SubexpressionValueTypeEnum valueType,
					   NodeAST* left, NodeAST* right
					  );

NodeAST* CreateIntegerNumberNode(int integerValue);
NodeAST* CreateFunctionNode(TSymbolTableRecord* symbol, NodeAST *rightValue);

/* �������� � ������������ ������ ������������ ��������������� ������ */
void FreeAST(NodeAST *);

/* ����������� ��������� � �������� */
extern int dtl_lineno;       /* ����� ������ �������� �� ������� */
void ast_error(char* s, ...);

/* ������ ������������ ��������������� ������ */
void PrintAST(NodeAST* aTree, int level);


#endif
