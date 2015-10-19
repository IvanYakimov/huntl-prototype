/* Based upon John Levine's book "flex&bison" */

#ifndef _SYMBOL_TABLE_H
#define _SYMBOL_TABLE_H

/* Структура элемента таблицы символов */
typedef struct
{
  char name;      /* Имя переменной. В текущей реализации один знак */
  int isDeclared; /* Объявлена ли переменная */
} TSymbolTableRecord;

#endif
