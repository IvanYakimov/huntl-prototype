# Makefile - the part of GenTesc generator.
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

obj = main.o kernel.o scanner.o parser.o solver.o limit-generator.o
gxx = g++
flags = -g -O0 -fdiagnostics-color=always -Wno-deprecated -std=c++11
libs = -lcvc4 -lgmp

# Target
generator: $(obj)
	@echo "\033[44m Link Generator \033[0m"
	$(gxx) -o generator $(flags) $(obj) $(libs)
	@echo "\033[46m Generator Completed! \033[0m"

# Cacl 
main.o: main.cpp kernel.hh parser.hh
	@echo "\033[44m Compile Main \033[0m"
	$(gxx) $(flags) -c main.cpp

# Kernel
kernel.o: kernel.cpp kernel.hh \
	parser.hh solver.hh limit-generator.hh
	@echo "\033[44m Compile Kernel \033[0m"
	$(gxx) $(flags) -c kernel.cpp

# Parser
parser.o: parser.hh \
	kernel.hh scanner.cc
	@echo "\033[44m Compile Papser \033[0m"
	$(gxx) $(flags) -c parser.cc
parser.hh: parser.yy
	@echo "\033[44m Generate Parser source \033[0m"
	bison --output-file="parser.cc" --verbose parser.yy
# Scanner
scanner.o: scanner.cc \
	kernel.hh parser.hh
	@echo "\033[44m Compile Scanner \033[0m"
	$(gxx) $(flags) -c scanner.cc
scanner.cc: scanner.ll 
	@echo "\033[44m Generate Scanner source \033[0m"
	flex --outfile="scanner.cc" scanner.ll

# Solver
solver.o: solver.cpp solver.hh
	@echo "\033[44m Compile Solver \033[0m"
	$(gxx) $(flags) -c solver.cpp

# Limit Generator
limit-generator.o: limit-generator.cpp limit-generator.hh
	@echo "\033[44m Generate Limit Generator\033[0m"
	$(gxx) $(flags) -c limit-generator.cpp

# Primitive way to analyse file dependencies
dep-list:
	@echo "\033[44m Generate dependencies list \033[0m"
	for f in $$(ls -d * | grep '\.[hcply]*'); do echo; echo $$f: ; cat $$f | grep "# include *"; done > dep-list

# Clean Up
clean: 
	@echo "\033[41m Clean up Generator \033[0m"
	rm -f $(obj) scanner.cc parser.hh parser.cc \
	position.hh stack.hh location.hh *~ dep-list generator *.output

# Verbose mode:
verbose:
	@echo "\033[45m \"input:\" \033[0m";
	@cat target.cpp
	@echo "\033[42m \"output:\" \033[0m";
	@./generator -i target.cpp

# Run program:
run:
	@echo "\033[45m \"input:\" \033[0m";
	@cat target.c
	@echo "\033[42m \"output:\" \033[0m";
	@./generator target.c > test.dtl
	@cat test.dtl

