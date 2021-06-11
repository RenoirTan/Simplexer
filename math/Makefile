# ~~ Variables Catalogue ~~
# Commands, prefixed with C
# Directories, prefixed with D
# File extensions, prefixed with F

CC := gcc
CCXX := g++

DSRC := src
DBIN := bin
DINC := include

FC := .c
FCXX := .cpp
FO := .o
FAR := .a
ifeq ($(OS), Windows_NT)
	FX := .exe
	FSO := .dll
else
	FX :=
	FSO :=.dll
endif
FARSO := $(FSO)$(FAR)

CDEF := 
CINC := -I$(DINC)
CCSTD := c11
CCXXSTD := c++17
CFLAGS := $(CINC) -m64 -Wall -fPIC -O2 $(CDEF)
CCFLAGS := $(CFLAGS) $(CCSTD)
CCXXFLAGS := $(CFLAGS) $(CCXXSTD)
CCC := $(CC) $(CCFLAGS)
CCXXC := $(CCXX) $(CXXFLAGS)

.PHONY: all mkdir cleanobj clear

all: token$(FO)

mkdir:
	@mkdir -p $(DSRC) $(DBIN) $(DINC)

cleanobj:
	@rm -rf $(DBIN)/*$(FO) $(DBIN)/*$(FA) $(DBIN)/*$(FARSO)

clear: cleanobj
	@rm -rf $(DBIN)/*$(FSO) $(DBIN)/*$(FX)


token$(FO): token$(FCXX)
	$(CCXXC) -c $^ -o $@
