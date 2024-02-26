CFLAGS = -Wall -g

TARGET1 = build/main_skiplist 
TARGET2 = build/skiplist_unit_test

OBJ1 = src/skiplist.o src/main_skiplist.o
OBJ2 = src/skiplist.o src/skiplist_unit_test.o

$(TARGET1): $(OBJ1)
	$(CC) $(OBJ1) $(LDFLAGS) -o $(TARGET1)

$(TARGET2): $(OBJ2)
	$(CC) $(OBJ2) $(LDFLAGS) -o $(TARGET2)

all: $(TARGET1) $(TARGET2)
