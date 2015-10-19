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

%code requires 
{
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "definitions.h"
	
#include "list.h"
#include "value.h"
#include "test-case.h"
#include "suite.h"
#include "global-scope.h"
#include "codegen.h"
	
  void dtl_error(char *s, ...);
}

%code top
{
  /* Based upon John Levine's book "flex&bison"*/
#include "dtl-parser.h"
	
#define MAX_TABLE_SIZE 256
  TSymbolTableRecord UserVariableTable[MAX_TABLE_SIZE];

  extern int dtl_lex();

  void dtl_error(char *s, ...)
  {
    va_list ap;
    va_start(ap, s);

    fprintf(stderr, "%d: error: ", dtl_lineno);
    vfprintf(stderr, s, ap);
    fprintf(stderr, "\n");
  }

  void dtl_warning(char *s, ...)
  {
    va_list ap;
    va_start(ap, s);

    fprintf(stderr, "%d: warning: ", dtl_lineno);
    vfprintf(stderr, s, ap);
    fprintf(stderr, "\n");
  }
}

%no-lines
%name-prefix "dtl_"
%output="dtl-parser.c"
%defines
%verbose

%union
{
  TListItem *list;
  int i;
  char string[NAME_LENGTH];
}

/* declare tokens */
%token <i> INTEGER
%token <string> ID

%token IMP
%token QMARK
%token MIN
%token MAX
%token DEFVAL
%token ENDL

%type <list> suite_list suite
%type <list> case_list test_case
%type <list> in_list value 

%start test

%%

test:
suite_list {
  SetTestSuiteList($1); }
| {}
;

suite_list:
suite_list suite {
  $$ = JoinListItem($1, $2); }
| suite {
  $$ = $1; }
;

suite:
ID ':' ENDL case_list {
  TTestSuite *suite = CreateTestSuite($1, $4);
  $$ = CreateListItem(suite); }
;

case_list:
case_list test_case {
  $$ = JoinListItem($1, $2); }
| test_case {
  $$ = $1; }
;

test_case:
in_list IMP value ENDL { 
  TTestCase *testCase = CreateTestCase($1, $3);
  $$ = CreateListItem(testCase); }
| in_list IMP QMARK ENDL {
  // todo: warning
  dtl_warning ("undefined function output, skip the test case");
  $$ = NULL; }
;

in_list:
in_list ',' value {
  $$ = JoinListItem($1, $3); }
| value {
  $$ = $1; }
;

value:
INTEGER {
  TValue *value = CreateIntValue($1);
  $$ = CreateListItem(value); }
| MIN {
  TValue *value = CreateMinValue();
  $$ = CreateListItem(value); }
| MAX {
  TValue *value = CreateMaxValue();
  $$ = CreateListItem(value); }
| DEFVAL {
  TValue *value = CreateDefValue();
  $$ = CreateListItem(value); }
;

%%
