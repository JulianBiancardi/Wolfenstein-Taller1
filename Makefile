SOURCES = $(wildcard src/main/*.cpp) $(wildcard src/main/editor/*.cpp)

TESTS_SOURCES = $(filter-out src/main/main.cpp, $(wildcard src/*/*.cpp) $(wildcard src/main/editor/*.cpp)) 

## COMPILER FLAGS ##
CC = g++
std = c++11
all_errors = yes
# optimize = yes
# debug = yes

CFLAGS = -std=$(std)

ifdef all_errors
CFLAGS += -Wall -Werror -pedantic -pedantic-errors
endif

ifdef optimize
CFLAGS += -O3
endif

ifdef debug
-ggdb -DDEBUG -fno-inline
endif

## END OF COMPILER ##

## LINKER FLAGS ##
threads = yes
# threadsan = yes
# math = yes
graphics = yes

LDFLAGS = 

ifdef threads
LDFLAGS += -pthread
endif

ifdef threadsan
LDFLAGS += -fsanitize=thread
endif

ifdef math
LDFLAGS += -lm
endif

ifdef graphics
LDFLAGS += -lSDL2
endif

## END OF LINKER ## 

.PHONY: all
all: tp0

tp0: $(SOURCES)
	$(CC) $(CFLAGS) $(LDFLAGS) $(SOURCES) -o tp

tests: $(TESTS_SOURCES)
	$(CC) $(CFLAGS) $(LDFLAGS) $(TESTS_SOURCES) -o tests.exe

clean: 
	rm tests.exe tp