CXX      := g++
CXXFLAGS := -std=c++17 -pedantic-errors -Wall -Wextra -Werror -no-pie
EASYFLAGS := -std=c++17 -g
LDFLAGS  := -L/usr/lib -lstdc++ -lm
BUILD    := ./build
OBJ_DIR  := $(BUILD)/objects
APP_DIR  := .
SUBDIRS := $(wildcard */.)
TARGET   := main
TARGETS   := all build clean
INCLUDE  := -Iinclude/
SRC      := 	\
	$(filter-out SignalHandler/main.cpp, $(wildcard SignalHandler/*.cpp)) \
	$(filter-out ActionManager/main.cpp, $(wildcard ActionManager/*.cpp)) \
	$(wildcard *.cpp) \

CPP_OBJ  := $(SRC:%.cpp=$(OBJ_DIR)/%.o)
OBJECTS  := $(CPP_OBJ:%.asm=$(OBJ_DIR)/%.o)
DEPENDENCIES \
				:= $(OBJECTS:.o=.d)
SUBDIRS_TARGETS := \
    $(foreach t, $(TARGETS) ,$(addsuffix $t,$(SUBDIRS)))

all: build $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(EASYFLAGS) $(INCLUDE) -c $< -MMD -o $@
# 	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@

# # $(OBJ_DIR)/%.o: %.asm
# # 	@mkdir -p $(@D)
# # 	yasm -f elf64 $< -o $@

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(EASYFLAGS) -o $(APP_DIR)/$(TARGET) $^ $(LDFLAGS)
# 	$(CXX) $(CXXFLAGS) -o $(APP_DIR)/$(TARGET) $^ $(LDFLAGS)

-include $(DEPENDENCIES)

# .PHONY : $(TARGETS) $(SUBDIRS_TARGETS)
.PHONY: all build clean debug release info

# $(SUBDIRS_TARGETS) : $(MAKE) -C $(@D) $(@F:.%=%)

build:
# 	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

debug: CXXFLAGS += -DDEBUG -g
debug: all

release: CXXFLAGS += -O2
release: all

clean:
	-@rm -rvf $(OBJ_DIR)/*
# 	-@rm -rvf $(APP_DIR)/*

info:
	@echo "[*] Application dir: ${APP_DIR}     "
	@echo "[*] Object dir:      ${OBJ_DIR}     "
	@echo "[*] Sources:         ${SRC}         "
	@echo "[*] Objects:         ${OBJECTS}     "
	@echo "[*] Dependencies:    ${DEPENDENCIES}"

run:
	$(APP_DIR)/$(TARGET)
