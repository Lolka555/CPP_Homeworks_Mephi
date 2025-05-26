SOURCES := $(wildcard *.cpp)
RESULT := main
SCRIPTS := $(wildcard *.sh)
SCRIPT_TARGETS := $(SCRIPTS:.sh=_run)

ifeq ($(OS), Windows_NT)
    USER_OS := Windows
    RM := del
    EXE := .exe
    RUN_CMD := $(RESULT)$(EXE)
else
    USER_OS := $(shell uname -s)
    RM := rm -f
    EXE :=
    RUN_CMD := ./$(RESULT)$(EXE)
    ifneq ($(USER_OS), Darwin)
        ASAN_CFLAGS := -fsanitize=address
        ASAN_LDFLAGS := -fsanitize=address
        ASAN_OPTIONS := detect_leaks=1
    else
        ASAN_CFLAGS :=
        ASAN_LDFLAGS :=
    endif
endif

OBJECTS := $(SOURCES:.cpp=.o)
CFLAGS := -g $(ASAN_CFLAGS) -std=c++20 -Wall -Werror
LDFLAGS := $(ASAN_LDFLAGS)

all: run

run: compile
	$(if $(ASAN_OPTIONS), ASAN_OPTIONS=$(ASAN_OPTIONS)) $(RUN_CMD) 

%_run: %.sh
	/bin/bash $< 

compile: $(RESULT) $(SCRIPT_TARGETS)

%.o: %.cpp $(wildcard *.h)
	g++ -c $(CFLAGS) $< -o $@ 

$(RESULT): $(OBJECTS)
	g++ $(OBJECTS) $(LDFLAGS) -o $(RESULT)$(EXE) 

clean:
	$(RM) $(OBJECTS) $(RESULT)$(EXE)