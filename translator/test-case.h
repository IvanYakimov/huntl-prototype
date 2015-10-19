#ifndef RUN_CASE_H_
#define RUN_CASE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "definitions.h"
#include "list.h"
#include "value.h"
#include "codegen.h"

typedef struct
{
	LIST_ITEM_DATA_HEADER
	TListItem *paramValueList;
	TListItem *returnValueList;
}TTestCase;

TTestCase *CreateTestCase(TListItem *paramValueList, TListItem *returnValueList);
void FreeTestCase(void *testCase);
void PrintTestCase(FILE *stream, TTestCase *testCase);

typedef struct
{
	FILE* stream;
	char functionName[NAME_LENGTH];
}TTestCaseContext;
TTestCaseContext* InitTestCaseContext(FILE* stream, char functionName[NAME_LENGTH]);
void FreeTestCaseContext(TTestCaseContext* context);
// <-- сигнатура функции --> Function(TListItemData* data, void* context);
void GenerateTestCase(TListItemData* data, void* context);

#endif /* RUN_CASE_H_ */
