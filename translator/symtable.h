/* Based upon John Levine's book "flex&bison" */

#ifndef _SYMBOL_TABLE_H
#define _SYMBOL_TABLE_H
typedef struct {
  char name;      
  int isDeclared; 
} TSymbolTableRecord;

#endif
