/*
 * Based upon John Levine's book "flex&bison"
 */
#  include <stdio.h>
#  include <stdlib.h>
#  include <stdarg.h>
#  include <string.h>
#  include <math.h>
#include "dtl-ast.h"

void ast_error(char *s, ...) {
  va_list ap;
  va_start(ap, s);

  fprintf(stderr, "%d: error: ", dtl_lineno);
  vfprintf(stderr, s, ap);
  fprintf(stderr, "\n");
}

void check_node(void* node) {
    if(node == NULL) {
    ast_error("out of space");
    exit(0);
  }
}

NodeAST* CreateNodeAST(NodeTypeEnum nodetype, char* opValue, NodeAST* left, NodeAST* right) {
  NodeAST* a = malloc(sizeof(NodeAST));
  check_node(a);
  a->nodetype = nodetype;
  a->opValue = opValue;
  a->left = left;
  a->right = right;
  return a;
}

NodeAST* CreateIntegerNumberNode(int integerValue) {
  TNumericValueNode* a = malloc(sizeof(TNumericValueNode));
  check_node(a);
  a->nodetype = typeConst;
  a->value = integerValue;
  return (NodeAST*)a;
}

NodeAST* CreateStringNode(const char* string) {
  TStringNode* node = malloc(sizeof(TStringNode));
  check_node(node);
  node->nodetype = typeString;
  node->value = strdup(string);
  return (NodeAST*)node;
}

NodeAST* CreateFunctionNode(TSymbolTableRecord* symbol, NodeAST *rightValue) {
  TFunctionNode* a = malloc(sizeof(TFunctionNode));
  check_node(a);
  a->nodetype = typeFunctionOp;
  a->variable = symbol;
  a->value = rightValue;
  return (NodeAST *)a;
}

void FreeAST(NodeAST* a) {
  if(!a)
    return;
  switch(a->nodetype) {
  case typeList:
    FreeAST(a->right);
  case typeConst:
  case typeIdentifier:
    break;
  case typeString:
    free(((TStringNode*)a)->value);
    break;
  case typeFunctionOp:
    free(((TFunctionNode *)a)->value);
    break;
  default: printf("internal error: free bad node %c\n", a->nodetype);
  }
  free(a); 
}

void PrintAST(NodeAST* a, int level) {
  printf("%*s", 2 * level, "");	/* indent to this level */
  ++level;
  if(!a) {
    printf("NULL\n");
    return;
  }

  switch(a->nodetype) {
  case typeConst:
    printf("number %d\n", ((TNumericValueNode *)a)->value);
    break;

  case typeIdentifier:
    printf("ref %c\n", ((TSymbolTableReference *)a)->function->name);
    break;

  case typeString:
    printf("string %s\n", ((TStringNode*)a)->value);
    break;

  case typeList:
  case typeImplement:
    printf("binop %s\n", a->opValue);
    PrintAST(a->left, level);
    PrintAST(a->right, level);
    return;

  case typeFunctionOp:
    printf("func: %c\n", ((TSymbolTableReference *)a)->function->name);
    PrintAST( ((TFunctionNode *)a)->value, level);
    return;
	              
  default: printf("bad %c\n", a->nodetype);
    return;
  }
}
