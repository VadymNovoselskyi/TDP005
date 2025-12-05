CXX = g++
CXXFLAGS = -g -std=c++17 -Wall -Wextra -MMD -MP
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

OBJ = build/main.o build/StateMachine.o build/Window.o build/Menu.o build/Menus.o build/Projectile.o build/Weapon.o build/TextureManager.o build/Point.o build/Entity.o

DEPS = $(OBJ:.o=.d)

game: $(OBJ)
	$(CXX) $(OBJ) $(LDFLAGS) -o $@

# Compile rules
build/main.o: src/main.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/StateMachine.o: src/StateMachine.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/Window.o: src/Window.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/Menu.o: src/Menu.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/Menus.o: src/Menus.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/Projectile.o: src/Projectile.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/Weapon.o: src/Weapon.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/TextureManager.o: src/TextureManager.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/Point.o: src/Point.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/Entity.o: src/Entity.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(DEPS)

.PHONY: clean
clean:
	rm -f build/*.o build/*.d game
