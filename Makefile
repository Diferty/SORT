.PHONY: all clean run
PROGRAM = lab
FILES = main.c library.c
all:
	gcc $(FILES) -o $(PROGRAM)
clean:
	rm -f $(PROGRAM)
run:
	./$(PROGRAM) 
run_sort:
	./$(PROGRAM) --file sort.txt
run_graphics:
	./$(PROGRAM) --file graphics.txt