/* Based upon John Levine's book "flex&bison" */

#ifndef _ABSTRACT_SYNTAX_TREE_H
#define _ABSTRACT_SYNTAX_TREE_H

//#include "dtl-scanner.h"

typedef enum
{
    typeFunctionOp,      	/* функция */
    typeConst,            	/* константа */
    typeIdentifier,        	/* переменная */
    typeList,               /* список выражений или операторов */
	typeImplement,			/* оператор следствия */
} NodeTypeEnum;


/* Структура узла Абстрактного синтаксического дерева */
/* У кажого узла должен быть изначально заданный тип */

typedef struct /*TAbstractSyntaxTreeNode*/
{
  NodeTypeEnum nodetype;
  char* opValue;
  struct TAbstractSyntaxTreeNode* left;
  struct TAbstractSyntaxTreeNode* right;
} NodeAST;

typedef struct
{
  NodeTypeEnum nodetype;        /* Тип typeIfStatement */
  NodeAST* condition;  /* условие */
  NodeAST* trueBranch; /* операторы true-ветки */
  NodeAST* elseBranch; /* операторы необязательной false-ветки */
} TControlFlowNode;

typedef struct
{
  NodeTypeEnum nodetype;			/* Тип K */
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

/* Процедуры формирования Абстрактного синтаксического дерева */
NodeAST* CreateNodeAST(NodeTypeEnum cmptype, char* opValue,
//					   SubexpressionValueTypeEnum valueType,
					   NodeAST* left, NodeAST* right
					  );

NodeAST* CreateIntegerNumberNode(int integerValue);
NodeAST* CreateFunctionNode(TSymbolTableRecord* symbol, NodeAST *rightValue);

/* Удаление и освобождения памяти Абстрактного синтаксического дерева */
void FreeAST(NodeAST *);

/* Программный интерфейс с лексером */
extern int dtl_lineno;       /* номер строки приходит от лексера */
void ast_error(char* s, ...);

/* Печать абстрактного синтаксического дерева */
void PrintAST(NodeAST* aTree, int level);


#endif
