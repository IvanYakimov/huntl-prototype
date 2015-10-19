#ifndef SCANNER_H_
#define SCANNER_H_

// Внешние зависимости
#include <stdio.h>

// Внутренние зависимости
#include "definitions.h"

void lprint(char* token, char* type, int line);
void lerror(char* text, int line);
BOOL scan(char* filename, FILE* *scanner_in, int (*scanner)(void));

#endif /* SCANNER_H_ */
