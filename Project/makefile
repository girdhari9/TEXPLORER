CC = g++
CFLAGS = -Wall -std=c++1z
DEPS = screenPoint.h 
OBJ =  projectfile.o screenPoint_c.o list_print.o pointer_move.o 
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

projectfile: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

