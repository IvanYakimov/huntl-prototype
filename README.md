# Readme
This is a first prototype of the [**Huntl**](https://github.com/IvanYakimov/huntl) test generation infrastructure project. 

## About
The main feature of this prototype is a **translator** which provides translation from a **dtl** (*declarative testing language*) files to test-suites written in C with support of ctest framework. The **generator** is rather simple in this version, but it has been improved drammatically in modern version of the [**Huntl**](https://github.com/IvanYakimov/huntl).

## Details
The frond-end of this tool is built on top of **flex/bison** tools. The frond-end is very simple set of C procedures (this is rather raw implementation and the main issue is to implement the back-end on top of the **clang** tool).

## Example
Suppose we have a simple function which tests whether its argument is an even natural number.
```C
int f (int x)
{
  if ((x % 2) == 0 && (x > 0))
    return 1;
  else
    return 0;
}

```
The **generator** would produce two test-cases:
```
f:
1 => 0;
2 => 1;
```
Which than would be translated into an appropriate C file:
```C
//*****************************************************************
//Automatically-generated file. Do not edit!
//*****************************************************************
#include "target.h"
#include "CUnit/Basic.h"
#include "limits.h"
//Test for "f"
int init_suite_f( void )
{return 0;}
int clean_suite_f(void)
{return 0;}
void test_f(void)
{
}
int main()
{
	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();
	CU_pSuite pSuite_f = NULL;
	pSuite_f = CU_add_suite("Suite_f", init_suite_f, clean_suite_f);
	if( NULL == pSuite_f )
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (!CU_add_test( pSuite_f, "test of f function", test_f ))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	//Add tests to the suite
	CU_basic_set_mode(CU_BRM_VERBOSE);
	//Run all tests using the CUnit Basic interface
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}	

```
