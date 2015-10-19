all:
	@echo "\033[44m Make Translator, please wait. \033[0m"
	$(MAKE) -C ./translator #2>&1 > /dev/null
	@echo "\033[46m Successuful: Translator Completed \033[0m"
	@echo "\033[44m Make Generator, please wait.  \033[0m"
	$(MAKE) -C ./generator #2>&1 > /dev/null
	@echo "\033[46m Successuful: Generator Completed \033[0m"
	@echo "\033[44m Make Tester, please wait.  \033[0m"
	$(MAKE) -C ./tester #2>&1 > /dev/null

clean:
	$(MAKE) -C ./translator clean
	$(MAKE) -C ./generator clean
	$(MAKE) -C ./tester clean
	@rm -v *~
