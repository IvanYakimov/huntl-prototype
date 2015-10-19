#ifndef PARSER_H_
#define PARSER_H_

// Внешние зависимости
#include <stdio.h>

// Внутренние зависимости
#include "definitions.h"

BOOL parse(char* filename, int (*parser)(void));

#endif /* PARSER_H_ */
