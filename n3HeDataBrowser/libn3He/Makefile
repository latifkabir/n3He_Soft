#Makefile for compiling n3He library
#Update and Modified By: Latiful Kabir
#Date: 12/25/14
ROOTCINT  = rootcint
ROOTFLAGS = $(shell root-config --cflags)
ROOTLIBS  = $(shell root-config --glibs)
CXXFLAGS  += -fPIC

all: libn3He

clean: libn3He_clean
clear: libn3He_clear

# BEGIN libn3He

libn3He: lib/libn3He.so
libn3He_base	= TBranchBinary TTreeRaw ReadBinary CalOffset

libn3He_inc	= $(libn3He_base:=.h)
libn3He_obj	= $(addprefix src/,$(libn3He_base:=.o))

lib/libn3He.so: $(libn3He_obj) src/libn3He_Dict.o
	$(CXX) -o $@ $(CXXFLAGS) -shared -Wl,-soname,libn3He.so $^

src/%.o: src/%.cc
	$(CXX) -c -o $@ $(CPPFLAGS) $(CXXFLAGS) $(ROOTFLAGS) $<

src/libn3He_Dict.cc:
	cd src/; $(ROOTCINT) -f libn3He_Dict.cc -c $(libn3He_inc) LinkDef.h

libn3He_clean:
	rm -f $(libn3He_obj)
	rm -f src/*_Dict.*
	rm -f lib/libn3He.so

libn3He_clear:
	rm -f $(libn3He_obj)
	rm -f src/*_Dict.*


