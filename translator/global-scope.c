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

#ifndef GLOBAL_SCOPE_C_
#define GLOBAL_SCOPE_C_

#include <stdio.h>
#include <stdarg.h>
#include "global-scope.h"

TListItem* testSuiteList;
FILE* outputFile;

const TListItem* GetTestSuiteList()
{
  return testSuiteList;
}

void SetTestSuiteList(TListItem *header)
{
  if (testSuiteList != NULL)
    testSuiteList = ClearList(testSuiteList, FreeTestSuite);
  testSuiteList = header;
}

BOOL OpenOutputFile(char *fileName)
{
  if ((outputFile = fopen(fileName, "w")) == NULL)
    {
      Error("Can't open output file: %s", fileName);
      return FALSE;
    }
  else
    return TRUE;
}

void InitGlobalScope()
{
  testSuiteList = NULL;
}

void ClearGlobalScope()
{
  testSuiteList = ClearList(testSuiteList, FreeTestSuite);
}

void FatalError(char* s, ...)
{
  va_list ap;
  va_start(ap, s);

  fprintf(stderr, "fatal error: ");
  vfprintf(stderr, s, ap);
  fprintf(stderr, "\n");

  ClearGlobalScope();

  exit(EXIT_FAILURE);
}

void Error(char* s, ...)
{
  va_list ap;
  va_start(ap, s);

  fprintf(stderr, "fatal error: ");
  vfprintf(stderr, s, ap);
  fprintf(stderr, "\n");
}

#endif /* GLOBAL_SCOPE_C_ */
