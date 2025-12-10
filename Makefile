CXX = g++
CXXFLAGS = -g -std=c++17 -Wall -Wextra -MMD -MP
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

SRC_DIR = src
OBJ_DIR = build

SRC = $(wildcard $(SRC_DIR)/*.cc)
OBJ = $(patsubst $(SRC_DIR)/%.cc, $(OBJ_DIR)/%.o, $(SRC))
DEPS = $(OBJ:.o=.d)

game: $(OBJ)
	$(CXX) $^ $(LDFLAGS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

-include $(DEPS)

.PHONY: clean
clean:
	rm -f $(OBJ_DIR)/*.o $(OBJ_DIR)/*.d game
