/*
Lexer.
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

%{ /* -*-C++ -*- */
# include <cerrno>
# include <climits>
# include <cstdlib>
# include <string>
# include "kernel.hh"
# include "parser.hh"

// Work around an incompatibility in flex (at least versions
// 2.5.31 through 2.5.33): it generates code that does
// not conform to C89. See Debian bug 333231
// <http://bugs.debian.org/cgi-bin/bugreport.cgi?bug=333231>.
# undef yywrap
# define yywrap() 1
// The location of the current token.
static yy::location loc;
%}

%option noyywrap nounput batch debug noinput
id    [a-zA-Z][a-zA-Z_0-9]*
integer   -?[0-9]+
blank [ \t]
%{
  // Code run each time a pattern is matched.
# define YY_USER_ACTION loc.columns (yyleng);
%}
%%
%{
  // Code run each time yylex is called.
  loc.step ();
%}

{blank}+  loc.step ();
[\n]+     loc.lines (yyleng); loc.step ();

"#".*\n    {}

"if"    return yy::Parser::make_IF(loc);
"else"  return yy::Parser::make_ELSE(loc);
"return"   return yy::Parser::make_RETURN(loc);
"int"   return yy::Parser::make_INT(loc);
"-"     return yy::Parser::make_MINUS(loc);
"+"     return yy::Parser::make_PLUS(loc);
"*"     return yy::Parser::make_STAR(loc);
"/"     return yy::Parser::make_SLASH(loc);
"%"     return yy::Parser::make_MOD(loc);
"||"    return yy::Parser::make_OR(loc);
"&&"    return yy::Parser::make_AND(loc);
"("     return yy::Parser::make_LPAREN(loc);
")"     return yy::Parser::make_RPAREN(loc);
"{"     return yy::Parser::make_LBRACE(loc);
"}"     return yy::Parser::make_RBRACE(loc);
"=="    return yy::Parser::make_EQUAL(loc);
"="     return yy::Parser::make_ASSIGNMENT(loc);
"!="    return yy::Parser::make_NOT_EQUAL(loc);
"!"     return yy::Parser::make_NOT(loc);
"<"     return yy::Parser::make_LESS(loc);
"<="    return yy::Parser::make_LESS_OR_EQUAL(loc);
">"     return yy::Parser::make_GREATER(loc);
">="    return yy::Parser::make_GREATER_OR_EQUAL(loc);
","     return yy::Parser::make_COMMA(loc);
";"     return yy::Parser::make_SEMICOLON(loc);

{integer} {
  errno = 0;
  long n = strtol (yytext, NULL, 10);
  if (! (INT_MIN <= n && n <= INT_MAX && errno != ERANGE))
    driver.error (loc, "integer is out of range");
  return yy::Parser::make_NUMBER(n, loc);
}

{id}        return yy::Parser::make_IDENTIFIER(yytext, loc);
.           driver.error (loc, "invalid character");
<<EOF>>     return yy::Parser::make_END(loc);
%%

void Kernel::scan_begin ()
{
  yy_flex_debug = trace_scanning;
  if (file.empty () || file == "-")
    yyin = stdin;
  else if (!(yyin = fopen (file.c_str (), "r")))
    {
      error ("cannot open " + file + ": " + strerror(errno));
      exit (EXIT_FAILURE);
    }
}
void Kernel::scan_end ()
{
  fclose (yyin);
}
