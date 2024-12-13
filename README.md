# Tetris Royale


## Membres du groupe
| Prénom    | Nom                 | Matricule |
| --------- | ------------------- | --------- |
| Tao       | CHAU                | 000567638 |
| Juliette  | Cornu-Besser        | 000581723 |
| Quentin   | Bernard Bouissières | 000572078 |
| Jonas     | Schellekens         | 000590985 |
| Ethan     | Van Ruyskenvelde    | 000589640 |
| Lucas     | Verbeiren           | 000591223 | 
| Ernest    | Malysz              | 000514682 |
| Rafaou    | Gajewicz            | 000569354 |

## Build le projet
### Dépendances
Pour que le projet puisse fonctionner, vous aurez besoin des libraires suivantes (les commandes suivantes fonctionnent pour Debian) :

- **Make**  
  `sudo apt install make`
- **CMake**  
  `sudo apt install cmake`
- **CppUnit**  
  `sudo apt install libcppunit-dev`
- **Ncurses**  
  `sudo apt install libncurses5-dev libncursesw5-dev`


### Compilation
Pour compiler le projet, vous avez le choix entre le mode RELEASE:
```
make
```
et le mode DEBUG:
```
make debug
```


## Exécution du jeu
Pour lancer le jeu Tetris, vous devez vous trouver dans la racine projet et faire:
```
./build/tetris
```
Sinon, vous devez vous rendre manuellement dans le dossier `build` et faire:
```
./tetris
```