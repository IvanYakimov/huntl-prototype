/* 
Распространяется под лицензией zlib,
см. http://www.gzip.org/zlib/zlib_license.html
Разработчик - Иван Якимов.
*/

#ifndef _DEFINITIONS_H_
#define _DEFINITIONS_H_

#define STD_OUT

#ifndef NULL
#define NULL	0
#endif

#define TRUE	1
#define FALSE	0
#define EQ_STRINGS 0
typedef int BOOL;

/* Настройки компиляции */
#define DEBUG

#define PRINT_TABLES
#define PRINT_TREES

#ifdef DEBUG

#ifdef PRINT_TABLES
#define PRINT_VAR_TABLE
#define PRINT_TMP_VAR_TABLE
#define PRINT_TYPE_TABLE
#define PRINT_LABEL_TABLE
#define PRINT_LITERAL_TABLE
#define PRINT_TYPE_SIZE
#define PRINT_VARIABLE_MEMORY_ALLOCATE
#endif /* PRINT_TABLES */

#define PRINT_3AC_AST
#define PRINT_AST

#define NO_PROPAGATION
#define NO_FOLDING

#endif 

/* Настройка языка */
#ifndef LANG_DEFINED
#define LANG_ENG
#define LANG_DEFINED
#endif

/* Настройка длины имен */
#define NAME_LENGTH	64

#endif /* _DEFINITIONS_H_ */
