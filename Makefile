CC = mpic++
CFLAGS  = -Wall -g -pedantic -I include -std=c++20
LD = mpic++
LDFLAGS = -Wall -g -I include

SRC_DIR = src
INCLUDE_DIR = include

PROGRAMS = matrixseq matrixmpi

OBJECTS = $(SRC_DIR)/matrix.o

all: matrixseq

clean:
	rm -f matrix $(SRC_DIR)/*.o

matrixseq: $(SRC_DIR)/matrix.o $(SRC_DIR)/main.o
	$(LD) $(LDFLAGS) -o matrixseq $(SRC_DIR)/matrix.o $(SRC_DIR)/main.o

matrixmpi: $(SRC_DIR)/matrix.o $(SRC_DIR)/mainmpi.o
	mpic++ $(LDFLAGS) -o matrixmpi $(SRC_DIR)/matrix.o $(SRC_DIR)/mainmpi.o
	
$(SRC_DIR)/matrix.o: $(SRC_DIR)/matrix.cc $(INCLUDE_DIR)/matrix.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/matrix.cc -o $(SRC_DIR)/matrix.o

$(SRC_DIR)/main.o: $(SRC_DIR)/main.cc $(INCLUDE_DIR)/matrix.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.cc -o $(SRC_DIR)/main.o

$(SRC_DIR)/mainmpi.o: $(SRC_DIR)/mainmpi.cc $(INCLUDE_DIR)/matrix.hpp
	mpic++ $(CFLAGS) -c $(SRC_DIR)/mainmpi.cc -o $(SRC_DIR)/mainmpi.o

	
