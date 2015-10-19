#ifndef SUITE_H_
#define SUITE_H_

#include "definitions.h"
#include <string.h>
#include <stdio.h>
#include "list.h"
#include "test-case.h"
#include "codegen.h"

typedef struct
{
	LIST_ITEM_DATA_HEADER
	TListItem *caseList;
}TTestSuite;

TTestSuite *CreateTestSuite(char functionName[NAME_LENGTH], TListItem *caseList);
void FreeTestSuite(void *suite);
void PrintTestSuite(FILE *stream, void *suite);


typedef struct
{
	FILE* stream;
}TTestSuiteContext;
TTestSuiteContext* InitTestSuiteContext(FILE* stream);
void FreeTestSuiteContext(TTestSuiteContext* context);
// <-- сигнатура функции --> Function(TListItemData* data, void* context);
void GenerateSuite(TListItemData* data, void* context);
void GenerateSuitePointerDefinition(TListItemData* data, void* context);
void GenerateSuiteAdditition(TListItemData* data, void* context);
void GenerateTestAddition(TListItemData* data, void* context);

#endif /* TEST_SUITE_H_ */
