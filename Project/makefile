CC = g++
CFLAGS = -Wall -std=c++14
DEPS = screenPoint.h cmd_mode.h
OBJ =  projectfile.o screenPoint_c.o list_print.o pointer_move.o copy_file.o
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

projectfile: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

