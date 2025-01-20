TARGET = bin/main
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))

run: clean default

	./$(TARGET) "printf(\"Hola mundo!\");"
	./$(TARGET) "Printf(\"Hola mundo!\");"

default: $(TARGET)

clean:
				rm -f obj/*.o 
				rm -f bin/*
				rm -f *.db

$(TARGET): $(OBJ)
				gcc -o $@ $?

obj/%.o : src/%.c 
				gcc -c $< -o $@ -Iinclude
