
vpath %.c ./src

#TARGET=build/csv
LIBRARY=build/libcsv.a

IDIR =include
ODIR=build/obj
LDIR =lib


SOURCES=$(wildcard src/**/*.c src/*.c)

OBJ=$(patsubst src/%,%,$(SOURCES))
OBJECTS=$(patsubst %.c,$(ODIR)/%.o,$(OBJ))

LIB_SOURCES=$(filter-out src/main.c,${SOURCES})
LIB_OBJECTS=$(filter-out $(ODIR)/main.o,${OBJECTS})


TEST_SRC=$(wildcard tests/*_tests.c)
TESTS=$(patsubst %.c,%,$(TEST_SRC))

#-------------------

#CFLAGS= -O2 -Wall -Wextra -Isrc $(INCLUDES) $(LDFLAGS) -rdynamic -DNDEBUG $(OPTFLAGS) -D_FILE_OFFSET_BITS=64
CC=gcc
CFLAGS=-I$(IDIR)
LIBS=-lm

#-------------------
	
release: all
debug: dev

dev: CFLAGS=$CFLAGS   -DDEBUG 
dev: all

#-------------------

# The Target Build
#all: $(TARGET) tests
all: $(LIBRARY) tests

# all:
#	@echo "ALL:"
#	@echo " " $(SOURCES)
#	@echo " " $(OBJ)
#	@echo " " $(OBJECTS)
#	@echo "LIBRARY:"
#	@echo " " $(LIB_SOURCES)
#	@echo " " $(LIB_OBJECTS)


$(LIBRARY): CFLAGS += -fPIC	
$(LIBRARY): build $(LIB_OBJECTS) 
	    ar rcs $@ $(LIB_OBJECTS)
	    ranlib $@
		


$(TARGET): $(LIBRARY) $(ODIR)/main.o
	$(CC) $(CFLAGS) $(ODIR)/main.o -o $@ $< $(LIBS)

#-------------------
	
$(LIB_OBJECTS):	$(LIB_SOURCES)
	$(CC) -c -o $@ $< $(CFLAGS)
	
#$(ODIR)/%.o: %.c $(DEPS)
#$(ODIR)/%.o: %.c $(SOURCES)
#	$(CC) -c -o $@ $< $(CFLAGS)

#hellomake: $(OBJ)
#	gcc -o $@ $^ $(CFLAGS) $(LIBS)

	
#-------------------

build:
	@mkdir -p build/obj/
#	@mkdir -p bin

	
.PHONY: clean


clean: 
	@echo "----------------------------------------------------------------"
	@echo " Clean up "
	@echo ""
	@rm -rf build $(OBJECTS) $(TESTS)
	@rm -f *.o src/*.o
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 

	

# The Checker
BADFUNCS='[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)|stpn?cpy|a?sn?printf|byte_)'
check:
	@echo Files with potentially dangerous functions.
	@egrep $(BADFUNCS) $(SOURCES) || true
	
valgrind:
	VALGRIND="valgrind --log-file=/tmp/valgrind-%p.log" $(MAKE)	