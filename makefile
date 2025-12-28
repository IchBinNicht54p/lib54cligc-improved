CC=gcc

SRC=src
BIN=bin
BUILD=build
INCLUDE=include
INSTALL_DIR=/usr/local

TEST_BUILD=$(BIN)/build

INSTALL_DIR_LIB=$(INSTALL_DIR)/lib
INSTALL_DIR_BIN=$(INSTALL_DIR)/bin
INSTALL_DIR_INCLUDE=$(INSTALL_DIR)/include/lib54cligc_improved

SRC_FILES := $(wildcard $(SRC)/*.c)
SRC_FILES_COMPILED := $(patsubst $(SRC)/%.c,$(BUILD)/%.o,$(SRC_FILES))

TEST_FILES := $(wildcard $(BIN)/*.c)
TEST_FILES_COMPILED := $(patsubst $(BIN)/%.c,$(TEST_BUILD)/%,$(TEST_FILES))

CFLAGS=-I$(INCLUDE) 

.PHONY: default build clean install uninstall archive_source compile_source test make_directories

default: build install clean
build: make_directories compile_source archive_source

make_directories:
	mkdir -p $(BUILD)
	mkdir -p $(TEST_BUILD)

clean:
	rm build/*

install:
	sudo mkdir -p $(INSTALL_DIR_INCLUDE)
	sudo cp $(INCLUDE)/* $(INSTALL_DIR_INCLUDE)
	sudo cp $(BUILD)/lib54cligc.a $(INSTALL_DIR_LIB)/lib54cligc-improved.a

uninstall:
	sudo rm -rf $(INSTALL_DIR_INCLUDE)
	sudo rm $(INSTALL_DIR_LIB)/lib54cligc-improved.a

archive_source: $(SRC_FILES_COMPILED)
	ar rcs -v $(BUILD)/lib54cligc.a $(SRC_FILES_COMPILED)

test: $(TEST_FILES_COMPILED)
compile_source: $(SRC_FILES_COMPILED)

$(TEST_BUILD)/%: $(BIN)/%.c
	$(CC) $< -o $@ $(CFLAGS) -l54cligc-improved

$(BUILD)/%.o: $(SRC)/%.c
	$(CC) -c $< -o $@ $(CFLAGS)
