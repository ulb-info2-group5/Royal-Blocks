# Compiler et lier les fichiers
CXX = g++
CXXFLAGS = -std=c++17 -Wall -g
LDFLAGS = -lcppunit

# Répertoires de source et de test (avec chemin relatif depuis le dossier de test)
SRC_DIR = ../../../../src/server/database/
TEST_DIR = .
INCLUDE_DIR = ../../../../include

# Fichiers source et objets
SRC_FILES = $(SRC_DIR)/friends_manager/friends_manager.cpp $(SRC_DIR)/database_manager/database_manager.cpp  # ajoutez ici d'autres fichiers source si nécessaires
TEST_FILES = $(TEST_DIR)/test_friends_manager.cpp  # ajoutez d'autres fichiers de test si nécessaires

OBJ_FILES = $(SRC_FILES:.cpp=.o) $(TEST_FILES:.cpp=.o)

# Nom des fichiers exécutables
TARGET = test_friends_manager

# Commande de compilation
$(TARGET): $(OBJ_FILES)
	$(CXX) $(OBJ_FILES) -o $(TARGET) $(LDFLAGS)

# Compilations des fichiers .cpp en fichiers .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Règle de nettoyage
clean:
	rm -f $(OBJ_FILES) $(TARGET)

# Exécuter les tests après la compilation
test: $(TARGET)
	./$(TARGET)

.PHONY: clean test

# Temp compile script for mac
# g++ -I$(brew --prefix cppunit)/include -L$(brew --prefix cppunit)/lib -lcppunit -lsqlite3 -o test test_friends_manager.cpp ../../../../src/server/database/friends_manager/friends_manager.cpp ../../../../src/server/database/database_manager/database_manager.cpp ../../../../src/server/database/config.cpp -std=c++17
