CC = g++
CFLAGS = -Wall -std=c++1z
DEPS = module1.h module2.h
OBJ = module1.o module2.o dummyProject.o
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

dummyProject: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

