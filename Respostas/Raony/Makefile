comp: 
	clear
	gcc *.c -o prog 

run:
	clear
	./prog

comp_run:
	clear
	gcc *.c -o prog 
	./prog

valgrind:
	clear
	valgrind ./prog

leak:
	clear
	valgrind --leak-check=full ./prog

origins: 
	clear
	valgrind --track-origins=yes ./prog