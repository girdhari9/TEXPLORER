CC = g++ 
CFLAGS = -Wall -std=c++14 -g
DEPS = normal_mode.h cmd_mode.h
OBJ =  projectfile.o screen_point.o list_print.o pointer_move.o cmd_functions.o cmd_main.o
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

file_explorer: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

