.PHONY: all clean build run

all: build

# Étape de configuration et compilation avec CMake
build:
	mkdir -p build
	cd build && cmake .. && make -j$(nproc)

# Supprimer les fichiers générés
clean:
	rm -rf build

# Exécuter le programme après compilation
run: build
	./build/my_program
