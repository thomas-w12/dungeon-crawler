CC = gcc
CFLAGS = -Wall -Wshadow -Wextra -I./include
EXE = dungeon_crawler
SRCS = src/main.c src/room.c src/item.c src/player.c src/fileio.c
OBJS = $(SRCS:%.c=%.o)
TEST_FLAGS =

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXE)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

test: tests/sample_test.c
	$(CC) $(CFLAGS) $(TEST_FLAGS) $^ -o test_runner
	./test_runner

clean:
	rm -f $(EXE) src/*.o test_runner

run:
	./$(EXE)
