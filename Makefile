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

test: $(TEST_OBJS)
	$(CC) $(CFLAGS) $(TEST_OBJS) -o $(OBJDIR)/test_runner.exe
	$(OBJDIR)/test_runner.exe

clean:
	@if exist $(EXE) del /f /q $(EXE)
	@if exist $(OBJDIR) rmdir /s /q $(OBJDIR)

run:
	./$(EXE)

debug:
	$(CDEBUGER) ./$(EXE)