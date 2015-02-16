# this is the gui makefile 
-include ../VERSION

ROOT_INCLUDE 	= $(shell  root-config  --incdir)
PRG_INCLUDE 	= ./include
PRG_SOURCE  	= ./source
#LIB_INCLUDE  	= /home/kabir/libn3He/src/libn3He  ####<===remove
LIB_INCLUDE	= /home/npdg/n3He/libn3He/src ####<===add


OBJECTS       	= n3HeMain.o
DICTS	      	= $(OBJECTS:.o=Dict.o)
APPLIC        	= n3HeData$(VERS)

DEBUGFLAGS    	= #-Dn3He_DEBUG
CXX           	= g++
CXXFLAGS      	= -fPIC
LD            	= g++
LDFLAGS       	= -O2 -Wl,-rpath,$(LIB_INCLUDE)
SOFLAGS       	= -shared

ROOTCFLAGS   	:= $(shell root-config --cflags)
ROOTLIBS     	:= $(shell root-config --libs)
ROOTGLIBS    	:= $(shell root-config --glibs)

CXXFLAGS     	+= $(DEBUGFLAGS) $(ROOTCFLAGS)# -Wno-deprecated
LIBS          	= $(ROOTLIBS)
#GLIBS         	= $(ROOTGLIBS) -L/home/kabir/libn3He/lib -ln3He  ####<===remove
GLIBS         	= $(ROOTGLIBS) -L/home/npdg/n3He/libn3He/lib -ln3He  ####<===add



#-------------------------------------------------------

all:            $(APPLIC)


$(APPLIC):     	$(OBJECTS) $(DICTS)
		$(LD) $(LDFLAGS) $^ \
		-L/usr/X11R6/lib64 $(GLIBS) -lX11 -o $@	
	#	ln -sf n3HeData$(VERS) n3HeData
		@echo "$@ done"

%.o : $(PRG_SOURCE)/%.cxx
	$(CXX) -c $(CXXFLAGS) $< \
	-I$(ROOT_INCLUDE) -I$(PRG_INCLUDE) -I$(LIB_INCLUDE) 	

%Dict.o : %Dict.cxx
	$(CXX) -c $(CXXFLAGS) $< \
	-I$(ROOT_INCLUDE) -I$(PRG_INCLUDE) -I$(LIB_INCLUDE) 

%Dict.cxx : $(PRG_INCLUDE)/%.h #LinkDef.h
	@echo "Generating dictionary $@..."
	rootcint -f $@ -c $^

clean:
	rm -f ./*.o ./core ./*~ ./*Dict.cxx ./*Dict.h ./~* ./n3HeDataexported \
	./G__*.* source/*~ \
	include/*~
