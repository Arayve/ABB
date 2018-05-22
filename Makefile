CC = gcc
CFLAGS = -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror -Wtype-limits -pedantic
EXEC = pruebas

compile: main.c abb.c abb.h pila.c pila.h testing.c testing.h
	$(CC) $(CFLAGS) main.c abb.c pila.c testing.c -o $(EXEC)

run: compile
	./$(EXEC)

valgrind: compile
	valgrind --track-origins=yes --leak-check=full ./$(EXEC) 

gdb: compile
	gdb ./$(EXEC) -tui

gui: compile
	gdbgui ./$(EXEC)
