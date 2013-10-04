# This makefile is a wrapper for cmake-generated makefile.
# Run `./configure` before using it.

RM = rm -rf

all: ./build/Makefile
		@ $(MAKE) -C build

./build/Makefile:
		@ (cd build && cmake ..)

distclean:
		@- $(MAKE) -C build clean || true
		@- $(RM) ./build/*
