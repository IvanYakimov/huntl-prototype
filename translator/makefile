# Makefile - part of GenTesc Translator.
# Copyright (C) 2015 Ivan Yakimov, e-mail: ivan.yakimov.sibfu@yandex.ru

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

obj = 	program.o \
	scanner.o parser.o \
	dtl-ast.o dtl-scanner.o dtl-parser.o \
	codegen.o \
	value.o list.o \
	suite.o test-case.o \
	global-scope.o

compiler = cc

flags = -c -g -O0 -fdiagnostics-color=always -w

linker = cc -g

# Main target:
dtl: $(obj)
	@echo "\033[44m Link Translator \033[0m"
	$(linker) -o dtl $(obj)
	@echo "\033[46m Translator Completed \033[0m"

### Object files ###

# Program
program.o: program.c program.h \
	scanner.h parser.h \
	dtl-scanner.h dtl-parser.h \
	definitions.h global-scope.h 
	@echo "\033[44m Compile Program \033[0m"
	$(compiler) $(flags) program.c

# Scanner
scanner.o: scanner.c scanner.h \
	definitions.h
	@echo "\033[44m Compile Scanner \033[0m"
	$(compiler) $(flags) scanner.c

# Parser
parser.o: parser.c parser.h \
	definitions.h
	@echo "\033[44m Compile Parser \033[0m"
	$(compiler) $(flags) parser.c

# Code Generator
codegen.o: codegen.c codegen.h
	@echo "\033[44m Compile Code generator \033[0m"
	$(compiler) $(flags) codegen.c

# DTL-AST
dtl-ast.o: dtl-ast.c dtl-ast.h \
	symtable.h
	@echo "\033[44m Compile DLT-AST \033[0m"
	$(compiler) $(flags) dtl-ast.c

# Value
value.o: value.h value.h \
	definitions.h list.h
	@echo "\033[44m Compile Value \033[0m"
	$(compiler) $(flags) value.c

# List
list.o: list.c list.h \
	definitions.h
	@echo "\033[44m Compile List \033[0m"
	$(compiler) $(flags) list.c

# Suite
suite.o: suite.c suite.h \
	definitions.h \
	list.h \
	test-case.h codegen.h
	@echo "\033[44m Compile Suite \033[0m"
	$(compiler) $(flags) suite.c

# Test-Case
test-case.o: test-case.c test-case.h \
	definitions.h list.h \
	value.h codegen.h
	@echo "\033[44m Compile Test-Case \033[0m"
	$(compiler) $(flags) test-case.c

# Global-Scope
global-scope.o: global-scope.c global-scope.h \
	definitions.h list.h suite.h
	@echo "\033[44m Compile Global-Scope \033[m"
	$(compiler) $(flags) global-scope.c

### sweet FLEX - BISON couple ###

## DTL ANALYSER
# DTL Scanner
dtl-scanner.o: dtl-scanner.h \
	dtl-ast.h dtl-parser.h
	@echo "\033[44m Compile DTL-Scanner \033[0m"
	$(compiler) $(flags) dtl-scanner.c
dtl-scanner.h: dtl-scanner.l
	@echo "\033[44m Generate DTL-Scanner \033[0m"
	flex dtl-scanner.l

# DTL Parser
dtl-parser.o: dtl-parser.h \
	list.h value.h test-case.h \
	suite.h global-scope.h codegen.h \
	definitions.h
	@echo "\033[44m Compile DTL-Parser \033[0m"
	$(compiler) $(flags) dtl-parser.c
dtl-parser.h: dtl-parser.y
	bison -Wdeprecated dtl-parser.y

# Primitive way to analyse file dependencies
dep-list:
	@echo "\033[44m Generate dependencies list \033[0m"
	for f in $$(ls -d * | grep '\.[hcply]*'); do echo; echo $$f: ; cat $$f | grep "#include *"; done > dep-list

# Run program:
run:
	@echo "\033[44m Run program \033[0m"
	./dtl test.dtl > test.c
	cat test.c

# Clean Up
clean: 
	@echo "\033[41m Clean up Translator \033[0m"
	rm -f $(obj) \
	dtl \
	*~ *.output .*~ \
	dep-list \
	dtl-scanner.h dtl-scanner.c dtl-parser.h dtl-parser.c 











