/*
Parser.
Copyright (C) 2007 Free Software Foundation, Inc. http://fsf.org/
modified: 2015, Ivan Yakimov, e-mail: ivan.yakimov.sibfu@yandex.ru

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

%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.0.2"
%defines
%define parser_class_name {Parser}
%define api.token.constructor
%define api.value.type variant
%define parse.assert
%code requires
{
# include <string>
# include <cvc4/cvc4.h>
# include "solver.hh"
  class Kernel;
}
// The parsing context.
%param { Kernel& kernel }
%locations
%initial-action
{
  // Initialize the initial location.
  @$.begin.filename = @$.end.filename = &kernel.file;
};
%define parse.trace
%define parse.error verbose
%code
{
# include "kernel.hh"
# include <list>
  using std::string;
  using std::cout;
  using std::endl;
}
%define api.token.prefix {TOK_}

%token
END 0  "end of file"
IF     "if"
ELSE   "else"
RETURN "return"
INT    "int"
MINUS  "-"
PLUS   "+"
STAR   "*"
SLASH  "/"
MOD    "%"
AND    "&&"
OR     "||"
LPAREN "("
RPAREN ")"
LBRACE "{"
RBRACE "}"
EQUAL  "=="
NOT_EQUAL "!="
NOT "!"
LESS   "<"
LESS_OR_EQUAL "<="
GREATER   ">"
GREATER_OR_EQUAL ">="
COMMA ","
SEMICOLON ";"
ASSIGNMENT "="
;

%token <std::string> IDENTIFIER "identifier"
%token <int> NUMBER "number"

%type <int> func_def
%type <int> func_body
%type <int> func_head func_head_name func_head_params
%type <std::string> param
%type <int> param_list
%type <int> type
%type <int> if_stmt  
%type <int> stmt_list stmt block
%type <CVC4::Expr> expr

%%
%start program;
%left "||";
%left "&&";
%left "+" "-";
%left "*" "/" "%";
%left "<" "<=" ">" ">=";
%left "==" "!=";
%left "!";

program: func_def
| "end of file"
;

func_def: func_head func_body {
      // generate skeleton:
      kernel.GenerateTestHeader();
      kernel.GenerateTestCases();
      if (kernel.min_max_generation)
	kernel.GenerateLimits();
 }
;

func_head: func_head_name func_head_params
;

func_head_name:
type "identifier" {
  kernel.functionName = $2;}
;

func_head_params:
"(" ")" {}
| "(" param_list ")" {}
;

func_body: "{" stmt_list "}" {}
;

if_stmt: "if" "(" expr ")"  stmt "else" stmt {
  if (kernel.if_stmt_exists)
    {
      kernel.error("only one if-opertor supported");
      exit (-1);
    }
  else
    {
      kernel.solutionSet = kernel.solver.GetSolutionSet($expr);
      kernel.if_stmt_exists = true;
    }
}
;

stmt_list:
stmt {}
| stmt_list stmt {}
;

stmt:
block {}
| "return" expr ";" {}
| "identifier" "=" expr ";" {}
| expr ";" {}
| "int" "identifier" ";" {}
| if_stmt {}
;

block:
"{" "}" {}
| "{" stmt_list "}" {}
;

param:
type "identifier" {
  $$ = $2;}
;

type:
"int" {}
;

param_list:
param {
  kernel.paramList.push_back($param);}
| param_list "," param {
  kernel.paramList.push_back($param);}
;

expr:
"(" expr ")" {
  std::swap ($$, $2); }
| expr "+" expr {
  $$ = kernel.solver.CreatePlusExpr($1, $3); }
| expr "-" expr {
  $$ = kernel.solver.CreateMinusExpr($1, $3);}
| expr "*" expr {
  $$ = kernel.solver.CreateMultExpr($1, $3);}
| expr "/" expr {
  $$ = kernel.solver.CreateDivExpr($1, $3);}
| expr "%" expr {
  $$ = kernel.solver.CreateModExpr($1, $3);}
| expr "&&" expr {
  $$ = kernel.solver.CreateAndExpr($1, $3);}
| expr "||" expr {
  $$ = kernel.solver.CreateOrExpr($1, $3);}
| "identifier"{
  $$ = kernel.solver.CreateVarExpr($1); }
| "number"    {
  $$ = kernel.solver.CreateConstExpr($1); }
| expr "==" expr {
  $$ = kernel.solver.CreateEqualExpr($1, $3); }
| expr "!=" expr {
  $$ = kernel.solver.CreateNotEqualExpr($1, $3); }
| expr "<" expr {
  $$ = kernel.solver.CreateLessExpr($1, $3);}
| expr "<=" expr {
  $$ = kernel.solver.CreateLessOrEqualExpr($1, $3);}
| expr ">" expr {
  $$ = kernel.solver.CreateGreaterExpr($1, $3);}
| expr ">=" expr {
  $$ = kernel.solver.CreateGreaterOrEqualExpr($1, $3);}
| "!" expr {
  $$ = kernel.solver.CreateNotExpr($2);}
;

%%
void yy::Parser::error (const location_type& l,
			       const std::string& m)
{
  kernel.error (l, m);
}
