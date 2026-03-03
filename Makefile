CC = clang++
CFLAGS  = -Wall -g -pedantic -I include
LD = clang++
LDFLAGS = -Wall -g -I include

SRC_DIR = src
INCLUDE_DIR = include

PROGRAMS = matrix

OBJECTS = $(SRC_DIR)/matrix.o

all: $(PROGRAMS)

clean:
	rm -f matrix $(SRC_DIR)/matrix.o

matrix: $(SRC_DIR)/matrix.o $(SRC_DIR)/main.o
	$(LD) $(LDFLAGS) -o matrix -c $(SRC_DIR)/matrix.o $(SRC_DIR)/main.o
	
$(SRC_DIR)/matrix.o: $(SRC_DIR)/matrix.cc $(INCLUDE_DIR)/matrix.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/matrix.cc -o $(SRC_DIR)/matrix.o

$(SRC_DIR)/main.o: $(SRC_DIR)/main.cc $(INCLUDE_DIR)/matrix.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.cc -o $(SRC_DIR)/main.o
	
