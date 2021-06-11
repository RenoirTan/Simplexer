# ~~ Variables Catalogue ~~
# Commands, prefixed with C
# Directories, prefixed with D
# File extensions, prefixed with F

CC := gcc
CCXX := g++
CFLEX := flex
CYACC := yacc

DSRC := src
DBIN := bin
DINC := include

FC := .c
FCXX := .cpp
FL := .l
FY := .y
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
CYACCFLAGS := -d
CYACCC := $(CYACC) $(CYACCFLAGS)
CFLEXC := $(CFLEX)

.PHONY: all mkdir cleanobj clear

all: helloworld$(FL)$(FC)

mkdir:
	@mkdir -p $(DSRC) $(DBIN) $(DINC)

cleanobj:
	@rm -rf $(DBIN)/*$(FO) $(DBIN)/*$(FA) $(DBIN)/*$(FARSO)

clear: cleanobj
	@rm -rf $(DBIN)/*$(FSO) $(DBIN)/*$(FX)


helloworld$(FL)$(FC): helloworld$(FL)
	$(CFLEXC) $^
