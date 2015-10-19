[44m Run program [0m
./dtl test.dtl
//*****************************************************************
//Automatically-generated file. Do not edit!
//*****************************************************************
#include "target.h"
#include "CUnit/Basic.h"
//Test for "f"
int init_suite_f( void )
{return 0;}
int clean_suite_f(void)
{return 0;}
void test_f(void)
{
	CU_ASSERT(f(2, 3) == 4 );
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
