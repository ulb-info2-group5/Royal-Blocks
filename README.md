<div align="center">

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

</div>

### Dépendances

Le projet nécessite l'installation des programmes et bibliothèques suivants
(les commandes fonctionnent pour Debian) :

- **Make**  
  `sudo apt install make`
- **CMake**  
  `sudo apt install cmake`
- **CppUnit**  
  `sudo apt install libcppunit-dev`

### Compilation

Le projet peut être compilé en mode **Release** ou **Debug** :

```sh
make release
```

```sh
make debug
```

<div align="center">

## Exécution du jeu

</div>

**Pour afficher correctement le jeu Tetris avec la bibliothèque Ncurses dans
votre terminal, il faut que la variable d'environnement `TERM` soit bien mise
à `xterm-256color`**.

### Lancer le programme

Pour lancer Tetris, exécutez :

```sh
./tetris_royal_client
```

Pour lancer le serveur, exécutez :

```sh
./tetris_royal_server
```

### Les différentes commandes de déplacement

Voici une liste des différentes touches pour déplacer et tourner les pièces du
Tetris :

- **Rotation sens horlogique**  
  `g`

- **Rotation sens anti-horlogique**  
  `f`

- **Déplacement vers la gauche**  
  `←`

- **Déplacement vers la droite**  
  `→`

- **Descendre plus rapidement**  
  `↓`

- **Placer le tetromino en bas**  
  `↑`
