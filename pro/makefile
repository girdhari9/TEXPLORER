CC = g++
CFLAGS = -Wall -std=c++1z
DEPS = header.h 
OBJ = first_code.o header.o
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

first_code: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

