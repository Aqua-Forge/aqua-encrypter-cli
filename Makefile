# Aqua Template project makefile

# Compiler / Linker configs
CC          := g++
CPP_VERSION := 17
CC_FLAGS    := -c         \
               -W         \
               -std=c++$(CPP_VERSION) \
            #    -Wall     \
            #    -ansi     \
            #    -pedantic \

# Directories
SRC_DIR      := src
INCLUDE_DIR  := include
LIB_DIR      := lib
BIN_DIR      := bin
OBJ_DIR      := build
TESTS_DIR    := tests
CFGS_DIR     := configs
PREFIX       := /usr/local

# Filenames
TARGET       := aqua-template
TEST_TARGET  := main_tests
SRC          := $(wildcard $(SRC_DIR)/*.cpp)
H_SRC        := $(wildcard $(INCLUDE_DIR)/*.hpp)
OBJ          := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

#
# Compilation and linking
#
all: binFolder objFolder $(TARGET)

$(TARGET): $(OBJ)
	@echo "🚀 Building binary \"$@\" using G++ linker..."
	@$(CC) $^ -o $(BIN_DIR)/$@
	@echo "🎇 Build complete!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "🪛  Compiling object file: $@..."
	@$(CC) $(CC_FLAGS) $< -I $(INCLUDE_DIR)/ -o $@

objFolder:
	@mkdir -p $(OBJ_DIR)

binFolder:
	@mkdir -p $(BIN_DIR)

# Cleaning binaries and static libraries (object files)
clean:
	@echo "🧹 Cleaning..."
	@rm -r $(OBJ_DIR)
	@rm -r $(BIN_DIR)
	@echo "🧹 Done!"

# Running the project
run:
	@./$(BIN_DIR)/$(TARGET)

# Installing the project locally
install:
	@install -m 777 $(BIN_DIR)/$(TARGET) $(PREFIX)/bin
	@install -d $(PREFIX)/etc/$(TARGET)/$(CFGS_DIR)

# Building tests
test: $(TEST_TARGET)
	@echo "🚙 Running tests:"
	@./$(TESTS_DIR)/$(TEST_TARGET)

# Executing tests
$(TEST_TARGET): 
	@echo "🛠️  Building tests..."
	@$(CC) $(TESTS_DIR)/*.cpp -I$(INCLUDE_DIR) --std=c++17 -o $(TESTS_DIR)/$@

.PHONY: all clean run test install
