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

#include "test-case.h"

TTestCase *CreateTestCase(TListItem *paramValueList, TListItem *returnValueList)
{
  TTestCase *testCase = (TTestCase *)malloc(sizeof(TTestCase));
  testCase->paramValueList = paramValueList;
  testCase->returnValueList = returnValueList;
  return testCase;
}

void FreeTestCase(void *item)
{
  TTestCase *testCase = (TTestCase *)item;
  if (testCase)
    {
      if (testCase->paramValueList)
	ClearList(testCase->paramValueList, FreeValue);
      if (testCase->returnValueList)
	ClearList(testCase->returnValueList, FreeValue);
      free (testCase);
    }
}

void PrintTestCase(FILE *stream, TTestCase *item)
{
  TTestCase *testCase = (TTestCase *) item;
  if (testCase)
    {
      if (testCase->paramValueList)
	PrintList(testCase->paramValueList, stream, PrintValue);
      else
	fprintf( stream, "#\t" );
      fprintf(stream, "=>\t");
      if (testCase->returnValueList)
	PrintList(testCase->returnValueList, stream, PrintValue);
      else
	fprintf( stream, "#" );
    }
  else
    fprintf(stream, "#");
  fprintf(stream, "\n");
}

TTestCaseContext* InitTestCaseContext(FILE* stream, char functionName[NAME_LENGTH])
{
  TTestCaseContext* context = (TTestCaseContext *) malloc( sizeof( TTestCaseContext ) );
  context->stream = stream;
  strcpy(context->functionName, functionName);
  return context;
}

void FreeTestCaseContext(TTestCaseContext* context)
{
  if (context)
    free( context );
}

void GenerateTestCase(TListItemData* data, void* context_)
{
  /*
   * This function generates similar like this:
   * CU_ASSERT( K( pn1, pn2, ..., pnm ) == outn );
   */
  TTestCase *testCase = (TTestCase *) data;
  TTestCaseContext *context = (TTestCaseContext *) context_;
  FILE *stream = context->stream;

  //
  TAB();	fprintf(stream, "CU_ASSERT(");
  fprintf(stream, context->functionName);

  // Generate param list
  TParamValueContext *paramContext = InitParamValueContext(stream, GetListLength(testCase->paramValueList));
  fprintf(stream, "(");
  ProcessList(testCase->paramValueList, paramContext, GenerateParamValue);
  fprintf(stream, ")");
  FreeParamValueContext(paramContext);

  // Generate out
  TOutValueContext* outContext = InitOutValueContext(stream);
  fprintf(stream, " == ");
  ProcessList(testCase->returnValueList, outContext, GenerateOutValue);
  FreeOutValueContext(outContext);

  //
  fprintf(stream, ");");	ENDL();
}





















