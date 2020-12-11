EXE = tetris

SRC_DIR = src
INC_DIR = inc
OBJ_DIR = obj
BINPATH = bin

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

CPPFLAGS += -I$(INC_DIR)
CFLAGS += -std=c++11 #-Wall
LDLIBS += -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
RM = rm -rf

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJ)
	mkdir -p $(BINPATH)
	$(CXX) $^ $(LDLIBS) -g -o $(BINPATH)/$@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR) $(BINPATH)
