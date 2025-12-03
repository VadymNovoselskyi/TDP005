CXXFLAGS = -g -std=c++17 -Wall -Wextra
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

game: build/Window.o build/main.o
	g++ $(CXXFLAGS) $^ $(LDFLAGS) -o $@


build/main.o: src/main.cc
	g++ -c $(CXXFLAGS) $< -o $@

build/Window.o: src/Window.cc src/Window.h
	g++ -c $(CXXFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -f build/*.o sfml
