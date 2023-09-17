CC=g++
LDFLAGS=
CFLAGS=-c -Wall -ggdb
SRC_DIR=src
SOURCES_LIST=dnf.cpp impl.cpp main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=lab

SOURCES=$(addprefix $(SRC_DIR)/,$(SOURCES_LIST))

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) -g $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf build
