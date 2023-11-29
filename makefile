# Name of the project
PROJ_NAME=example

C_SOURCE=$(wildcard *.c */*.c */*/*.c */*/*/*.c)
H_SOURCE=$(wildcard *.h */*.c */*/*.h */*/*/*.h)
OBJ=$(C_SOURCE:.c=.o)
CC=gcc

# Flags for compiler
CC_FLAGS= -pthread -lrt -Wall

# Compilation and linking
all: $(PROJ_NAME)

$(PROJ_NAME): $(OBJ)
	$(CC) -o $@ $^ $(CC_FLAGS)

%.o: %.c %.h
	$(CC) -o $@  $< -c $(CC_FLAGS)


main.o: main.c $(H_SOURCE)
	$(CC) -o $@ $< -c $(CC_FLAGS)

clean:
	find . -type f -name '*.o' -delete
	find . -type f -name '$(PROJ_NAME)' -delete

clean_all:
	find . -type f -name '*.o' -delete
	find . -type f -name '$(PROJ_NAME)' -delete
	find . -type f -name '*.log' -delete
