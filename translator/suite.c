/*
Part of GenTesc translator.
Copyright (C) 2015 Ivan Yakimov, e-mail: ivan.yakimov.sibfu@yandex.ru

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "suite.h"

// <-- Start of private declaration

#define INIT_FUNC_TYPE						"int"
#define INIT_FUNC_NAME_PREFIX				"init_suite_"
#define INIT_FUNC_PARAMS					"void"
#define CLEAN_FUNC_TYPE						"int"
#define CLEAN_FUNC_NAME_PREFIX				"clean_suite_"
#define CLEAN_FUNC_PARAMS					"void"
#define TEST_FUNC_TYPE						"void"
#define TEST_FUNC_NAME_PREFIX				"test_"
#define TEST_FUNC_PARAMS					"void"
#define SUITE_NAME_PREFIX					"Suite_"
#define SUITE_POINTER_TYPE					"CU_pSuite"
#define SUITE_POINTER_NAME_PREFIX			"pSuite_"
#define ADD_SUITE_FUNC						"CU_add_suite"
#define ADD_TEST_FUNC						"CU_add_test"

void GenerateSuiteComment(TTestSuite* suite, FILE* stream);
void GenerateSuiteInitFunction(TTestSuite* suite, FILE* stream);
void GenerateSuiteCleanFunction(TTestSuite* suite, FILE* stream);
void GenerateSuiteTestFunction(TTestSuite* suite, FILE* stream);
void GenerateErrorHandling(TTestSuite* suite, FILE* stream);



// --> End of private declaration

TTestSuite *CreateTestSuite(char functionName[NAME_LENGTH], TListItem *caseList)
{
  TTestSuite *suite = (TTestSuite *) malloc( sizeof(TTestSuite) );
  strcpy(suite->name, functionName);
  suite->caseList = caseList;
  return suite;
}

void FreeTestSuite(void *item)
{
  TTestSuite *suite = item;
  if (suite)
    {
      if (suite->caseList)
	ClearList(suite->caseList, FreeTestCase);
      free(suite);
    }
}

void PrintTestSuite(FILE *stream, void *item)
{
  TTestSuite *suite = item;
  if (suite)
    {
      fprintf( stream, "%s:\n", suite->name);
      if (suite->caseList)
	PrintList(suite->caseList, stream, PrintTestCase);
      else
	fprintf(stream, "#");
    }
  else
    fprintf(stream, "#");
  fprintf(stream, "\n");
}

TTestSuiteContext* InitTestSuiteContext(FILE* stream)
{
  TTestSuiteContext* context = (TTestSuiteContext *) malloc( sizeof( TTestSuiteContext ) );
  context->stream = stream;
  return context;
}

void FreeTestSuiteContext(TTestSuiteContext* context)
{
  if (context)
    free(context);
}

void GenerateSuite(TListItemData* data, void* context)
{
  FILE* stream = ((TTestSuiteContext *) context)->stream;
  TTestSuite* suite = (TTestSuite *) data;
  //TODO: Проверка тестируемой функции (сверка с объявлением, определением)
  // ...
  // На вход функции GenerateTestCase (должны) подаются проверенные данные
  GenerateSuiteComment(suite, stream);
  GenerateSuiteInitFunction(suite, stream);
  GenerateSuiteCleanFunction(suite, stream);
  GenerateSuiteTestFunction(suite, stream);
}

void GenerateSuiteInitFunction(TTestSuite* suite, FILE* stream)
{
  fprintf(stream, "%s %s%s( %s )", INIT_FUNC_TYPE, INIT_FUNC_NAME_PREFIX, suite->name, INIT_FUNC_PARAMS);		ENDL();
  fprintf(stream, "{return 0;}");	ENDL();

}

void GenerateSuiteCleanFunction(TTestSuite* suite, FILE* stream)
{
  fprintf(stream, "%s %s%s(%s)",CLEAN_FUNC_TYPE, CLEAN_FUNC_NAME_PREFIX, suite->name, CLEAN_FUNC_PARAMS);		ENDL();
  fprintf(stream, "{return 0;}");	ENDL();
}

void GenerateSuiteComment(TTestSuite* suite, FILE* stream)
{
  fprintf(stream, "//Test for \"%s\"", suite->name); 	ENDL();
}

void GenerateSuiteTestFunction(TTestSuite* suite, FILE* stream)
{
  fprintf(stream, "%s %s%s(%s)", TEST_FUNC_TYPE, TEST_FUNC_NAME_PREFIX, suite->name, TEST_FUNC_PARAMS);	ENDL();
  fprintf(stream, "{");	ENDL();
  TTestCaseContext* testCaseContext = InitTestCaseContext(stream, suite->name);
  ProcessList(suite->caseList, testCaseContext, GenerateTestCase);
  FreeTestCaseContext(testCaseContext);
  fprintf(stream, "}");	ENDL();
}

void GenerateSuitePointerDefinition(TListItemData* data, void* context)
{
  FILE* stream = ((TTestSuiteContext *) context)->stream;
  TTestSuite* suite = (TTestSuite *) data;
  TAB();
  fprintf(stream, "%s %s%s = NULL;",SUITE_POINTER_TYPE, SUITE_POINTER_NAME_PREFIX, suite->name);
  ENDL();
}

void GenerateSuiteAdditition(TListItemData* data, void* context)
{
  FILE* stream = ((TTestSuiteContext *) context)->stream;
  TTestSuite* suite = (TTestSuite *) data;
  const char* funcName = suite->name;
  TAB();
  fprintf(stream, "%s%s = ", SUITE_POINTER_NAME_PREFIX, funcName);
  fprintf(stream, "%s(", ADD_SUITE_FUNC);
  fprintf(stream, "\"%s%s\"", SUITE_NAME_PREFIX, funcName);
  fprintf(stream, ", ");
  fprintf(stream, "%s%s", INIT_FUNC_NAME_PREFIX, funcName);
  fprintf(stream, ", ");
  fprintf(stream, "%s%s", CLEAN_FUNC_NAME_PREFIX, funcName);
  fprintf(stream, ");");
  ENDL();
  TAB();
  fprintf(stream, "if( NULL == %s%s )", SUITE_POINTER_NAME_PREFIX, funcName);		ENDL();
  GenerateErrorHandling(suite, stream);
}

void GenerateTestAddition(TListItemData* data, void* context)
{
  FILE* stream = ((TTestSuiteContext *) context)->stream;
  TTestSuite* suite = (TTestSuite *) data;
  TAB();
  fprintf(stream, "if (!");
  fprintf(stream, "CU_add_test( ");
  fprintf(stream, "%s%s", SUITE_POINTER_NAME_PREFIX, suite->name);
  fprintf(stream, ", ");
  fprintf(stream, "\"test of %s function\"", suite->name);
  fprintf(stream, ", ");
  fprintf(stream, "%s%s", TEST_FUNC_NAME_PREFIX, suite->name);
  fprintf(stream, " )");
  fprintf(stream, ")");
  ENDL();
  GenerateErrorHandling(suite, stream);
}

void GenerateErrorHandling(TTestSuite* suite, FILE* stream)
{
  TAB(); 	fprintf(stream, "{");	ENDL();
  TAB(); TAB();	fprintf(stream, "CU_cleanup_registry();");	ENDL();
  TAB(); TAB();	fprintf(stream, "return CU_get_error();");	ENDL();
  TAB();	fprintf(stream, "}");	ENDL();
}
























