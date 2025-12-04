CXX = g++
CXXFLAGS = -g -std=c++17 -Wall -Wextra -MMD -MP
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

OBJ = build/main.o build/GameState.o build/Window.o build/Menu.o build/Menus.o build/projectile.o build/weapon.o build/textureManager.o build/point.o build/entity.o

DEPS = $(OBJ:.o=.d)

game: $(OBJ)
	$(CXX) $(OBJ) $(LDFLAGS) -o $@

# Compile rules
build/main.o: src/main.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/GameState.o: src/GameState.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/Window.o: src/Window.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/Menu.o: src/Menu.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/Menus.o: src/Menus.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/projectile.o: src/projectile.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/weapon.o: src/weapon.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/textureManager.o: src/textureManager.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/point.o: src/point.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/entity.o: src/entity.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(DEPS)

.PHONY: clean
clean:
	rm -f build/*.o build/*.d game
