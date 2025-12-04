CXX = g++
CXXFLAGS = -g -std=c++17 -Wall -Wextra -MMD -MP
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

OBJ = build/projectile.o build/weapon.o build/projectileWeapon.o
DEPS = $(OBJ:.o=.d)

game: $(OBJ)
	$(CXX) $(OBJ) $(LDFLAGS) -o $@

# Compile rules
build/projectile.o: src/projectile.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/weapon.o: src/weapon.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/projectileWeapon.o: src/projectileWeapon.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(DEPS)

.PHONY: clean
clean:
	rm -f build/*.o build/*.d game
