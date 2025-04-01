CC = gcc
CDEBUGER = gdb
CFLAGS = -g -Wall -Wshadow -Wextra -I./include
EXE = dungeon_crawler.exe

SRCDIR = src
TESTDIR = tests
OBJDIR = build
SRCS = $(wildcard $(SRCDIR)/*.c)
TEST_SRCS = $(wildcard $(TESTDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.obj, $(SRCS))
TEST_OBJS = $(patsubst $(TESTDIR)/%.c, $(OBJDIR)/%.obj, $(TEST_SRCS))

VPATH = $(SRCDIR) $(TESTDIR)

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXE)

$(OBJDIR)/%.obj: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	@if not exist $(OBJDIR) mkdir $(OBJDIR)

layout_save_load_test: $(OBJDIR)/layout_save_load_test.o $(OBJS)
	$(CC) $(CFLAGS) $(OBJDIR)/layout_save_load_test.o $(OBJS) -o $(OBJDIR)/layout_save_load_test_runner
	$(OBJDIR)/layout_save_load_test_runner

player_save_load_test: $(OBJDIR)/player_save_load_test.o $(OBJS)
	$(CC) $(CFLAGS) $(OBJDIR)/player_save_load_test.o $(OBJS) -o $(OBJDIR)/player_save_load_test_runner
	$(OBJDIR)/player_save_load_test_runner

player_health_test: $(OBJDIR)/player_health_test.o $(OBJS)
	$(CC) $(CFLAGS) $(OBJDIR)/player_health_test.o $(OBJS) -o $(OBJDIR)/player_health_test_runner
	$(OBJDIR)/player_health_test_runner

item_pickup_inventory_test: $(OBJDIR)/item_pickup_inventory_test.o $(OBJS)
	$(CC) $(CFLAGS) $(OBJDIR)/item_pickup_inventory_test.o $(OBJS) -o $(OBJDIR)/item_pickup_inventory_test_runner
	$(OBJDIR)/item_pickup_inventory_test_runner

test: player_save_load_test layout_save_load_test item_pickup_inventory_test

clean:
	@if exist $(EXE) del /f /q $(EXE)
	@if exist $(OBJDIR) rmdir /s /q $(OBJDIR)

run:
	./$(EXE)

debug:
	$(CDEBUGER) ./$(EXE)