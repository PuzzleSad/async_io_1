CC=gcc
CFLAGS=-Wall -Wextra -O2

BIN=a.elf

HEADERDIR=.
SOURCEDIR=.
BUILDDIR=build


SOURCES= $(wildcard *.c)\
	$(wildcard src/*.c)\
	$(wildcard src/slowload/src/*.c)\
	$(wildcard src/uringload/src/*.c)\
	$(wildcard src/utils/src/*.c)



OBJECTS= $(patsubst %.c, $(BUILDDIR)/%.o, $(notdir $(SOURCES)) )


all: bin run

# all: 
# 	@echo $(SOURCES)
# 	@echo $(OBJECTS)

nrun: bin

bin: $(BIN)

run: $(BIN)
	./$(BIN)

$(BIN): $(OBJECTS)
	@echo "linking..."
	@$(CC) $(CFLAGS) -I$(HEADERDIR) -o $@ $^ -lm -lpthread -luring

$(BUILDDIR)/%.o: $(SOURCEDIR)/%.c
	@$(CC) $(CFLAGS) -I$(HEADERDIR) -c $< -o $@

$(BUILDDIR)/%.o: src/%.c
	@$(CC) $(CFLAGS) -I$(HEADERDIR) -c $< -o $@

$(BUILDDIR)/%.o: src/slowload/src/%.c
	@$(CC) $(CFLAGS) -I$(HEADERDIR) -c $< -o $@

$(BUILDDIR)/%.o: src/uringload/src/%.c
	$(CC) $(CFLAGS) -I$(HEADERDIR) -c $< -o $@

$(BUILDDIR)/%.o: src/utils/src/%.c
	@$(CC) $(CFLAGS) -I$(HEADERDIR) -c $< -o $@

