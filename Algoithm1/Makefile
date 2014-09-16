# Include files
SOURCES=initializer.c helper.c ProbCalculator.c main.c 

# Compiler
# --------
CC=gcc

CFLAGS= -Werror -pedantic -Wall -std=gnu99 

# Linker flags
# ------------
LDFLAGS=-lm

OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=Example

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS) 

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)


$(OBJECTS): %.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@
