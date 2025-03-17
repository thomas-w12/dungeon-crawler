CC = gcc
CFLAGS = -Wall -Wshadow -Wextra -Iinclude
EXE = dungeon_crawler
SRCS = src/main.c src/room.c src/item.c src/player.c
OBJS = $(SRCS:%.c=%.o)
TEST_FLAGS =

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXE)

.c.o:
	$(CC) $(CFLAGS) -c $*.c

test: tests/sample_test.c
	$(CC) $(CFLAGS) $(TEST_FLAGS) $^ -o test_runner
	./test_runner

clean:
	rm -f $(EXE) *.o

run:
	./$(EXE)