#ifndef SCANNER_H_
#define SCANNER_H_

// ������� �����������
#include <stdio.h>

// ���������� �����������
#include "definitions.h"

void lprint(char* token, char* type, int line);
void lerror(char* text, int line);
BOOL scan(char* filename, FILE* *scanner_in, int (*scanner)(void));

#endif /* SCANNER_H_ */
