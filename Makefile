########################################################################
# Compiler settings
CC = gcc
RM = rm
CFLAGS = -Iinclude -DDEBUG -w -g -O  -MMD

########################################################################
# Makefile settings
LIBNAME = libtools.a

########################################################################
# Generate the file lists
SRC = $(wildcard */*.c)
OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

########################################################################
# Build dependant files, Compile everything, and build the library
all: $(LIBNAME)

$(LIBNAME): $(OBJ)
	@echo "BUILD THE LIBRARY:"
	ar cr $@ $(OBJ)

-include $(DEP)

########################################################################
# Cleans object and library file(s)
clean:
	@echo "CLEAN:"
	$(RM) -f $(OBJ) $(LIBNAME)

########################################################################
# Cleans dependent file(s)
cleandep:
	@echo "CLEANDEP:"
	$(RM) -f $(DEP)
