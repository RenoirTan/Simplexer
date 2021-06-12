# ~~ Variables Catalogue ~~
# Commands, prefixed with C
# Directories, prefixed with D
# File extensions and prefixes, prefixed with F

CC := gcc
CCXX := g++

DSRC := src
DBIN := bin
DINC := include
DTES := tests

FTEST := test-
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

.PHONY: all mkdir cleanobj clear rmtests

all:

mkdir:
	@mkdir -p $(DSRC) $(DBIN) $(DINC) $(DTES)

cleanobj:
	@rm -rf $(DBIN)/*$(FO) $(DBIN)/*$(FA) $(DBIN)/*$(FARSO)

rmtests:
	@rm -rf $(DBIN)/$(FTEST)*

clear: cleanobj
	@rm -rf $(DBIN)/*$(FSO) $(DBIN)/*$(FX)
