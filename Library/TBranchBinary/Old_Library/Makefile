ROOTCINT  = rootcint
ROOTFLAGS = $(shell root-config --cflags)
ROOTLIBS  = $(shell root-config --glibs)
CXXFLAGS  += -fPIC

all: libN3HE

clean: libN3HE_clean

# BEGIN libN3HE

libN3HE: lib/libN3HE.so
libN3HE_base	= TBranchBinary

libN3HE_inc	= $(libN3HE_base:=.h)
libN3HE_obj	= $(addprefix src/libN3HE/,$(libN3HE_base:=.o))

lib/libN3HE.so: $(libN3HE_obj) src/libN3HE/libN3HE_Dict.o
	$(CXX) -o $@ $(CXXFLAGS) -shared -Wl,-soname,libN3HE.so $^

src/libN3HE/%.o: src/libN3HE/%.cc src/libN3HE/%.h
	$(CXX) -c -o $@ $(CPPFLAGS) $(CXXFLAGS) $(ROOTFLAGS) $<
	
src/libN3HE/libN3HE_Dict.o: src/libN3HE/libN3HE_Dict.cc
	$(CXX) -c -o $@ $(CPPFLAGS) $(CXXFLAGS) $(ROOTFLAGS) $<

src/libN3HE/libN3HE_Dict.cc:
	cd src/libN3HE; $(ROOTCINT) -f libN3HE_Dict.cc -c $(libN3HE_inc) LinkDef.h

libN3HE_clean:
	rm -f $(libN3HE_obj)
	rm -f src/libN3HE/*_Dict.*
	rm -f lib/libN3HE.so

