CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
TEST_FLAGS =

all: dungeon_crawler

dungeon_crawler: src/main.c
	$(CC) $(CFLAGS) $^ -o $@

test: tests/sample_test.c
	$(CC) $(CFLAGS) $(TEST_FLAGS) $^ -o test_runner
	./test_runner

clean:
	rm -f dungeon_crawler *.o

run:
	./dungeon_crawler