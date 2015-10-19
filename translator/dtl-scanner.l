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

%{
#include "scanner.h"
#include "dtl-ast.h"
#include "dtl-parser.h"
%}

%option yylineno
%option noyywrap
%option outfile="dtl-scanner.c" header-file="dtl-scanner.h"
%option prefix="dtl_"
%option yylineno

DIGIT [0-9]
SIGN [\+\-]
POSITIVE {DIGIT}+
INTEGER {SIGN}?{POSITIVE}
ID [a-zA-Z][a-zZ-Z0-9_]*

%%

\n       { return ENDL; }

\t	 |
\r	 |
"//".*\n |
" "	 {;}

{ID}    {
  //lprint(yytext, "id", yylineno);
  strcpy(dtl_lval.string, yytext);
  //lprint(yytext, "id", yylineno);
  return ID;}

{INTEGER} { dtl_lval.i = atoi(yytext);
  return INTEGER;}

"=>"    { return IMP;}
"?"     { return QMARK;}
"$min"  { return MIN;}
"$max"  { return MAX;}
"_"     { return DEFVAL; }

":"	|
","	|
";"     { return yytext[0];}

.       {}

%%
