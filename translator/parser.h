#ifndef PARSER_H_
#define PARSER_H_

// ������� �����������
#include <stdio.h>

// ���������� �����������
#include "definitions.h"

BOOL parse(char* filename, int (*parser)(void));

#endif /* PARSER_H_ */
