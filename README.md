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

Le projet nécessite l'installation des programmes et bibliothèques suivantes
(les commandes fonctionnent pour Debian) :

- **Make**  
  `sudo apt install make`
- **CMake**  
  `sudo apt install cmake`
- **CppUnit**  
  `sudo apt install libcppunit-dev`
- **Ncurses**  
  `sudo apt install libncurses5-dev libncursesw5-dev`

### Compilation

Le projet peut être compilé en mode **Release** ou **Debug** :

```sh
make -C build
```

```sh
make -C build debug
```

## Exécution du jeu

Pour lancer Tetris, exécutez :

```sh
./build/tetris
```
