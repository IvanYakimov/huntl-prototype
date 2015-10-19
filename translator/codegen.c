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

#include "codegen.h"
#include "CUnit/Basic.h"

#define CUNIT_FILE_HEADER "CUnit/Basic.h"
#define LIMITS_FILE_HEADER "limits.h"

void GenerateFile(FILE *stream)
{
  const TListItem *suiteList = GetTestSuiteList();
  TTestSuiteContext *suiteContext = InitTestSuiteContext(stream);

  LINE();
  COMMENT();	fprintf(stream, "Automatically-generated file. Do not edit!");	ENDL();
  LINE();
  INCLUDE(TARGET_FILE_HEADER); ENDL();
  INCLUDE(CUNIT_FILE_HEADER); ENDL();
  INCLUDE(LIMITS_FILE_HEADER); ENDL();

  // Generate suite functions
  ProcessList(suiteList, suiteContext, GenerateSuite);

  fprintf(stream, "int main()");	ENDL();
  fprintf(stream, "{");	ENDL();
  // int main()
  // {
  fprintf(stream, "\tif (CUE_SUCCESS != CU_initialize_registry())");	ENDL();
  TAB();	TAB();	fprintf(stream, "return CU_get_error();");	ENDL();

  ProcessList(suiteList, suiteContext, GenerateSuitePointerDefinition);
  ProcessList(suiteList, suiteContext, GenerateSuiteAdditition);
  ProcessList(suiteList, suiteContext, GenerateTestAddition);

  TAB();	COMMENT();	fprintf(stream, "Add tests to the suite");	ENDL();
  TAB();	fprintf(stream, "CU_basic_set_mode(CU_BRM_VERBOSE);");	ENDL();
  TAB();	COMMENT(); fprintf(stream, "Run all tests using the CUnit Basic interface"); ENDL();
  TAB();	fprintf(stream, "CU_basic_run_tests();");	ENDL();
  TAB();	fprintf(stream, "CU_cleanup_registry();");	ENDL();
  TAB();	fprintf(stream, "return CU_get_error();");	ENDL();

  fprintf(stream, "}");	TAB(); ENDL();
  // }

  FreeTestSuiteContext(suiteContext);
}


























