CXX = g++
CXXFLAGS = -g -std=c++17 -Wall -Wextra -MMD -MP
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

OBJ = build/main.o build/StateMachine.o build/Window.o build/Menu.o build/Menus.o build/Character.o build/Player.o build/point.o build/windowTextBuild.o
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

build/Character.o: src/Character.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
build/Player.o: src/Player.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/point.o: src/point.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(DEPS)

.PHONY: clean
clean:
	rm -f build/*.o build/*.d game
