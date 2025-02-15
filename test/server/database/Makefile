# Répertoires des fichiers sources
SRC_DIR = ../../../src/server/database
TEST_DIR = ../../../test/server/database/test_account_manager

# Répertoire de construction
BUILD_DIR = build
BUILD_SRC_DIR = $(BUILD_DIR)/account_manager
BUILD_TEST_DIR = $(BUILD_DIR)/test_account_manager

# Fichiers source
SRC_FILES = $(SRC_DIR)/account_manager/account_manager.cpp $(SRC_DIR)/database_manager/database_manager.cpp
TEST_FILES = $(TEST_DIR)/test_account_manager.cpp

# Fichiers objets et exécutables dans le répertoire de construction
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.cpp=$(BUILD_SRC_DIR)/%.o) $(TEST_FILES:$(TEST_DIR)/%.cpp=$(BUILD_TEST_DIR)/%.o)
TEST_EXEC = $(BUILD_DIR)/test_account_manager

# Bibliothèques et options de compilation
CPPFLAGS = -std=c++17 -I$(SRC_DIR) -I$(TEST_DIR) -Wall -g
CXX = g++
CXXFLAGS = $(CPPFLAGS) -fPIC

# CppUnit
CPPUNIT_LIBS = -lcppunit

# Créer le répertoire de construction si nécessaire
$(shell mkdir -p $(BUILD_SRC_DIR) $(BUILD_TEST_DIR))

# Définition de DATABASE_PATH (ajustez le chemin selon votre projet)
DATABASE_PATH = "/path/to/database"

# Règle par défaut
all: $(TEST_EXEC)

# Lier les fichiers objets pour créer l'exécutable
$(TEST_EXEC): $(OBJ_FILES)
	$(CXX) $(OBJ_FILES) -o $(TEST_EXEC) $(CPPUNIT_LIBS)

# Compiler les fichiers source en fichiers objets
$(BUILD_SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

# Compiler les fichiers de test en fichiers objets
$(BUILD_TEST_DIR)/%.o: $(TEST_DIR)/%.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

# Nettoyer les fichiers générés
clean:
	rm -rf $(BUILD_DIR)

# Exécuter les tests après compilation
run_tests: $(TEST_EXEC)
	./$(TEST_EXEC)

.PHONY: all clean run_tests
