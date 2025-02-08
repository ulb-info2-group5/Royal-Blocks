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

Le projet nécessite l'installation des programmes et bibliothèques suivants
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
make release
```

```sh
make debug
```

## Exécution du jeu

**Pour afficher correctement le jeu Tetris avec la bibliothèque Ncurses dans
votre terminal, il faut que la variable d'environnement `TERM` soit bien mise
à `xterm-256color`**.

### Lancer le programme

Pour lancer Tetris, exécutez :

```sh
./build/tetris
```

### Les différentes commandes de déplacement

Voici une liste des différentes touches pour déplacer et tourner les pièces du
Tetris :

- **Rotation sens horlorique**  
  `g` ou `espace`

- **Rotation sens anti-horlogique**  
  `f`

- **Déplacement vers la gauche**  
  `h` ou `←`

- **Déplacement vers la droite**  
  `l` ou `→`

- **Descendre plus rapidement**  
  `j` ou `↓`

- **Placer le tetromino en bas**  
  `G` ou `↑`
