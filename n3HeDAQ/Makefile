#Makefile for n3HeDAQ Control Program 
#Version:2
#Latiful Kabir

CC        := g++
GC        := gcc
LD        := g++
CFLAG     := -std=c++11 -pthread -lncurses -lmenu

EXE	  :=n3he
MODULES   := core gui lib
SRC_DIR   := $(addprefix src/,$(MODULES))
BUILD_DIR := $(addprefix bin/,$(MODULES))

SRC       := $(foreach sdir,$(SRC_DIR),$(wildcard $(sdir)/*.cpp))
OBJ       := $(patsubst src/%.cpp,bin/%.o,$(SRC))
INCLUDES  := $(addprefix -I,$(SRC_DIR))

vpath %.cpp $(SRC_DIR)
vpath %.c $(SRC_DIR)

define make-goal
$1/%.o: %.cpp
	$(CC) $(INCLUDES) $(CFLAG) -c $$< -o $$@
$1/libmenu.o: libmenu.c
	$(GC) $(INCLUDES) -lncurses -lmenu -c $$< -o $$@
endef

.PHONY: all checkdirs clean

all: checkdirs bin/$(EXE)

bin/$(EXE): $(OBJ) bin/lib/libmenu.o
		$(LD) $^ $(CFLAG) -o $@
		@echo Finished Making Successfully!!!

checkdirs: $(BUILD_DIR)

$(BUILD_DIR):
	@mkdir -p $@

clean:
	@rm -rf $(BUILD_DIR)

$(foreach bdir,$(BUILD_DIR),$(eval $(call make-goal,$(bdir))))

