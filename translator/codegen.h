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

#ifndef CODEGEN_H_
#define CODEGEN_H_

#include "definitions.h"
#include "dtl-ast.h"

#include "global-scope.h"
#include "suite.h"
#include "list.h"
#include <stdio.h>

#define TAB()			fprintf(stream, "\t")
#define ENDL()			fprintf(stream, "\n")
#define LINE()			fprintf(stream, "//*****************************************************************\n")
#define COMMENT()		fprintf(stream, "//")
#define INCLUDE(name)	fprintf(stream, "#include \"%s\"", name)

void GenerateFile(FILE* stream);

#endif /* CODEGEN_H_ */

// Structure of generated file:

//---------------------- File Prefix --------------------------------
// *** Included files ***
// --> include header of the target file
// #include "target-file-name.h"
// #include "CUnit/Basic.h"
//-------------------------------------------------------------------

//---------------------- File Infix ---------------------------------
// --> Test init and clean functions definitions <--
// -> Test suite 1
// int init_suite_1( void ) {...}
// int clean_suite_1( void ) {...}
// void test_1( void ) {...}
// ...
// .
// .
// .
// -> Test suite N
// int init_suite_N( void ) {...}
// int clean_suite_N( void ) {...}
// void test_N( void ) {...}
// ...
//
// *Note: here 1..N are names of functions under tests
/*
--> Test case function:
void test_K( void )
{
	CU_ASSERT( K( p11, p12, ..., p1m ) == out1 );
	CU_ASSERT( K( p21, p22, ..., p2m ) == out2 );
	...
	CU_ASSERT( K( pn1, pn2, ..., pnm ) == outn );
}
*/
//-------------------------------------------------------------------

//---------------------- File Postfix -------------------------------
/*

int main()
{
	--> This variable represents status of the operation
	int status;

	--> Test suites
	CU_pSuite pSuite1 = NULL;
	...
	CU_pSuite pSuiteN = NULL;

	--> Initialize the CUnit test registry
	if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

	--> Add suites to the registry
	pSuite1 = CU_add_suite("Suite_1", init_suite1, clean_suite1);
	if (NULL == pSuite1)
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	...
	pSuiteN = CU_add_suite("Suite_N", init_suiteN, clean_suiteN);
	if (NULL == pSuiteN)
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	--> Add the tests to the suite
	//TODO:

	--> Run all tests using the CUnit Basic interface
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}

*/
// *Note: here 1..N are names of functions under tests
//-------------------------------------------------------------------
