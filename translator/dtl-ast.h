/* Based upon John Levine's book "flex&bison" */

#ifndef _ABSTRACT_SYNTAX_TREE_H
#define _ABSTRACT_SYNTAX_TREE_H

typedef enum {
  typeFunctionOp,
  typeConst, // integer value
  typeIdentifier, // TODO: "phantom" node?
  typeString, // c string
  typeList,           
  typeImplement,		
} NodeTypeEnum;

typedef struct /*TAbstractSyntaxTreeNode*/ {
  NodeTypeEnum nodetype;
  char* opValue;
  struct TAbstractSyntaxTreeNode* left;
  struct TAbstractSyntaxTreeNode* right;
} NodeAST;

typedef struct {
  NodeTypeEnum nodetype;        
  NodeAST* condition;
  NodeAST* trueBranch; 
  NodeAST* elseBranch; 
} TControlFlowNode;

typedef struct {
  NodeTypeEnum nodetype;
  int value;
} TNumericValueNode;

// malloc / free !!!
typedef struct {
  NodeTypeEnum nodetype;
  char *value;
} TStringNode;

#ifndef _SYMBOL_TABLE_H
#include "symtable.h"
#endif

typedef struct {
  NodeTypeEnum nodetype;
  TSymbolTableRecord* function;
} TSymbolTableReference;

typedef struct {
  NodeTypeEnum nodetype;
  TSymbolTableRecord* variable;
  NodeAST* value;
} TFunctionNode;

NodeAST* CreateNodeAST(NodeTypeEnum cmptype, char* opValue, NodeAST* left, NodeAST* right);
NodeAST* CreateIntegerNumberNode(int integerValue);
NodeAST* CreateStringNode(const char* string);
NodeAST* CreateFunctionNode(TSymbolTableRecord* symbol, NodeAST *rightValue);

void FreeAST(NodeAST *);

extern int dtl_lineno;
void ast_error(char* s, ...);

void PrintAST(NodeAST* aTree, int level);

#endif
