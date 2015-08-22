SOURCES=$(wildcard src/*.cc)
CONTENT=$(wildcard content/*)
BUILDDIR=build
OBJECTS=$(patsubst %.cc,$(BUILDDIR)/%.o,$(SOURCES))

CC=clang++
CFLAGS=-g --std=c++14
CFLAGS+=-Wall -Wextra

LDLIBS=`sdl2-config --cflags --libs` -lSDL2_mixer

EXECUTABLE=$(BUILDDIR)/game

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJECTS) $(LDLIBS)

$(BUILDDIR)/%.o: %.cc
	@mkdir -p $(BUILDDIR)/src
	$(CC) -c $(CFLAGS) -o $@ $<

run: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm -rf $(BUILDDIR)

.PHONY: all clean run
