obj = 	target.o test.o
compiler = cc
flags = -c -g -O0 -fdiagnostics-color=always -Wno-deprecated
linker = cc -g
libs = -lcunit

# Main target:
tester: $(obj)
	@echo "\033[44m Link Objects \033[0m"
	$(linker) $(obj) $(libs) -o tester

# Program
target.o: target.c target.h 
	@echo "\033[44m Compile Program \033[0m"
	./generator target.c | vipe | ./dtl - > test.c
	$(compiler) $(flags) target.c

test.o: test.c
	@echo "\033[44m Compile Test File \033[0m"
	$(compiler) $(flags) test.c

# Run
run: tester
	@echo "\033[44m Run Project \033[0m"
	./tester | nano -

# Clean Up
clean: 
	@echo "\033[41m Clean up project \033[0m"
	rm -f $(obj) \
	tester \
	*~

