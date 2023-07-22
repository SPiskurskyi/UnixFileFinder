# VARIABLES

INCLUDE_DIR = include
SOURCE_DIR = src
BUILD_DIR = build

CXX = g++
CXX_STANDARD = c++17
CXXFLAGS = -Wall -Wextra -Wpedantic -std=$(CXX_STANDARD)
CPPFLAGS = -I $(INCLUDE_DIR)

LIB_NAME = libfilefinder.a
LIB_OBJS = $(BUILD_DIR)/filefinder.o

INCLUDE_DIR = include
SOURCE_DIR = src

# TARGETS
all : create build

create:
	@mkdir -p build

build: $(LIB_NAME)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) app.cpp -L. -lfilefinder -o $(BUILD_DIR)/app

$(LIB_NAME): $(LIB_OBJS)
	ar rcs $(LIB_NAME) $(LIB_OBJS)

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.cpp $(INCLUDE_DIR)/%.h
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@
clean:
	rm -f $(BUILD_DIR)/app
	rm -f $(BUILD_DIR)/*.o
