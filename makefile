
COMPILER := gcc
COMPILER_STANDARD := -std=c99
COMPILER_FLAGS := -pedantic -Wall -Wextra
LINKER_FLAGS :=

SRC_DIR := src
INC_DIR := src
BIN_DIR := bin
OBJ_DIR := bin-int

EXEC_NAME := SFR
ifeq ($(OS), Windows_NT)
	EXEC_NAME := $(EXEC_NAME).exe
endif

EXEC_FILE := $(BIN_DIR)/$(EXEC_NAME)

getfiles = $(foreach dir, $(wildcard $1/*), $(call getfiles, $(dir), $2) $(filter $(subst *, %, $2), $(dir)))

SRC_EXT := c
SRC_FILES := $(call getfiles, $(SRC_DIR), *.$(SRC_EXT))

HEADER_EXT := h
HEADER_FILES := $(call getfiles, $(SRC_DIR), *.$(HEADER_EXT))

OBJ_EXT := o
OBJ_FILES := $(patsubst $(SRC_DIR)/%.$(SRC_EXT), $(OBJ_DIR)/%.$(OBJ_EXT), $(SRC_FILES))



error: target-error



.PHONY: build
build: $(EXEC_FILE)

.PHONY: rebuild
rebuild: clean build



$(EXEC_FILE): $(OBJ_FILES)
	@ if [ ! -d $(@D) ]; then echo "Creating directory:" $(@D); mkdir -p $(@D); fi
	@ echo "Creating executable:" $@
	@ $(COMPILER) $(LINKER_FLAGS) $^ -o $@

$(OBJ_DIR)/%.$(OBJ_EXT): $(SRC_DIR)/%.$(SRC_EXT) $(HEADER_FILES)
	@ if [ ! -d $(@D) ]; then echo "Creating directory:" $(@D); mkdir -p $(@D); fi
	@ echo "Compiling:" $<
	@ $(COMPILER) $(COMPILER_STANDARD) $(COMPILER_FLAGS) -I $(INC_DIR) -c $< -o $@



.PHONY: clean
clean: clean-all

.PHONY: clean-all
clean-all: clean-bin clean-obj

.PHONY: clean-bin
clean-bin:
	@ if [ -d $(BIN_DIR) ]; then rm -r $(BIN_DIR); echo "Deleted directory:" $(BIN_DIR); else echo "Could not delete directory:" $(BIN_DIR); fi

.PHONY: clean-obj
clean-obj:
	@ if [ -d $(OBJ_DIR) ]; then rm -r $(OBJ_DIR); echo "Deleted directory:" $(OBJ_DIR); else echo "Could not delete directory:" $(OBJ_DIR); fi



TAB := "    "
list-files = $(foreach item, $(wildcard $1), $(TAB) $(item); echo)

.PHONY: list-files
list-files:
	@ echo "Source Files:"; echo $(call list-files, $(SRC_FILES))
	@ echo "Header Files:"; echo $(call list-files, $(HEADER_FILES))
	@ echo "Object Files:"; echo $(call list-files, $(OBJ_FILES))
	@ echo "Executable File:"; echo $(call list-files, $(EXEC_FILE))



TARGET_LIST := build rebuild clean list-files
list-strings = $(foreach item, $1, $(TAB) $(item); echo)

.PHONY: target-error
target-error:
	@ echo "Please specify one of the following targets:"; echo $(call list-strings, $(TARGET_LIST))
