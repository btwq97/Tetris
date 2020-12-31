EXE = tetris.exe

SRC_DIR = Source
INC_DIR = Include
OBJ_DIR = Obj
LIB_DIR = Lib
BIN_DIR = Bin

SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

INC_FLAG := -I$(INC_DIR)
C_FLAG = -std=c++11 -Wall
LINKER := -L$(LIB_DIR) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
DEL = DEL
RM = RMDIR

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJ)
	if not exist $(BIN_DIR) mkdir $(BIN_DIR)
	$(CXX) $^ $(LINKER) -o $(BIN_DIR)/$@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)
	$(CXX) $(INC_FLAG) $(C_FLAG) -c $< -o $@

clean:
	$(RM) /S /Q $(OBJ_DIR) $(BIN_DIR)