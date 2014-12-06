#Makefile for beam scan 
#Version:1
#Latiful Kabir
#Date: 09.24.14

CC        := g++
LD        := g++
CFLAG     := -std=c++11 -pthread

EXE	  :=bscan
MODULES   := xy daq avg 
SRC_DIR   := $(addprefix src/,$(MODULES))
BUILD_DIR := $(addprefix bin/,$(MODULES))

SRC       := $(foreach sdir,$(SRC_DIR),$(wildcard $(sdir)/*.cpp))
OBJ       := $(patsubst src/%.cpp,bin/%.o,$(SRC))
INCLUDES  := $(addprefix -I,$(SRC_DIR))

vpath %.cpp $(SRC_DIR)

define make-goal
$1/%.o: %.cpp
	$(CC) $(INCLUDES) $(CFLAG) -c $$< -o $$@
endef

.PHONY: all checkdirs clean

all: checkdirs bin/$(EXE)

bin/$(EXE): $(OBJ)
		$(LD) $^ $(CFLAG) -o $@
		@echo Finished Making Successfully!!!

checkdirs: $(BUILD_DIR)

$(BUILD_DIR):
	@mkdir -p $@

clean:
	@rm -rf $(BUILD_DIR)

$(foreach bdir,$(BUILD_DIR),$(eval $(call make-goal,$(bdir))))

