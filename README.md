# Tetris Royale

## Membres du groupe

| Prénom    | Nom                 | Matricule |
| --------- | ------------------- | --------- |
| Tao       | Chau                | 000567638 |
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
- **Git**
  `sudo apt install git`
- **CppUnit**  
  `sudo apt install libcppunit-dev`
- **SQLite3**
  `sudo apt install libsqlite3-dev`
- **Qt5**
  `sudo apt install qtbase5-dev`
- **Boost**
  `sudo apt install libboost-all-dev`

D'autres bibliothèques, comme ftxui et nlohmann, sont également nécessaires pour la compilation, mais elles sont ajoutées automatiquement grâce à CMake via la fonctionnalité FetchContent.

#### Remarque

**Le projet nécessite également :**

- **GCC 14** ou supérieur
- ainsi que **C++23**

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

Pour lancer Tetris, vous avez le choix entre deux interfaces :

- Interface graphique :

  ```sh
  ./tetris_gui
  ```

- Interface en terminal :

  ```sh
  ./tetris_tui
  ```

Pour lancer le serveur, exécutez :

```sh
./tetris_royal_server
```

### Information importante concernant l'affichage du jeu dans le terminal

Si vous ne voyez pas toutes les informations du jeu à l'écran, vous devez dézoomer l'écran de votre terminal.

### Les différentes commandes de Tetris Royale

Voici une liste des différentes touches pour déplacer et tourner les pièces du
Tetris :

- **Rotation dans le sens horaire**  
  `g`

- **Rotation dans le sens antihoraire**  
  `f`

- **Déplacement vers la gauche**  
  `←`

- **Déplacement vers la droite**  
  `→`

- **Descente rapide**  
  `↓`

- **Placer le tetromino immédiatement en bas**  
  `↑`

- **Mettre en attente (hold) un tétrimino**
  `h`

- **Quitter la partie en cours**
 `q`
