mkdir -p build/test
rm -rf build/test/*

g++ -c  interfaceGame.cpp -o  interfaceGame.o 
g++ -c  interfaceManager.cpp -o interfaceManager.o 
#g++ -o test_output build/test/test_main.o build/test/print_grid.o -lncurses 
