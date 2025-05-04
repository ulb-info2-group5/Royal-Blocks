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

- **Make**\
  `sudo apt install make`
- **CMake**\
  `sudo apt install cmake`
- **Git**\
  `sudo apt install git`
- **CppUnit**\
  `sudo apt install libcppunit-dev`
- **SQLite3**\
  `sudo apt install libsqlite3-dev`
- **Qt5**\
  `sudo apt install qtbase5-dev`
- **Boost (uniquement la partie réseau est nécessaire)**\
  `sudo apt install libboost-system-dev libboost-thread-dev`

D'autres bibliothèques, comme ftxui et nlohmann, sont également nécessaires pour la compilation, mais elles sont ajoutées automatiquement grâce à CMake via la fonctionnalité FetchContent.

#### Remarque

**Le projet nécessite également :**

- **GCC 13** ou supérieur
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

### Choix de l'IP et du port

Pour établir la communication entre le client et le serveur :

#### Serveur

Vous pouvez passer un port de votre choix en argument lors du lancement :

```sh
./tetris_royal_server <port>
```

Sinon, le serveur lira la variable d'environnement **SERVER_PORT**.
Si aucune variable n'est définie, le port **1234** sera utilisé par défaut.

#### Client

Dans les interfaces graphique et terminal, il est possible de modifier l'IP et le port du serveur directement.
Ces informations seront sauvegardées dans le fichier `data/config.json`.

Si aucun fichier de configuration n'existe, un fichier par défaut sera automatiquement créé, en utilisant :

- l'IP définie par la variable d'environnement **SERVER_IP** (ou **127.0.0.1** par défaut),
- et le port défini par **SERVER_PORT** (ou **1234** par défaut).

### Information importante concernant l'affichage du jeu dans le terminal

Si vous ne voyez pas toutes les informations du jeu à l'écran, vous devez dézoomer l'écran de votre terminal.

### Les différentes commandes de Tetris Royale

Voici une liste des différentes touches pour déplacer et tourner les pièces du
Tetris :

- **Déplacement vers la gauche**\
  `←`

- **Déplacement vers la droite**\
  `→`

- **Descente rapide**\
  `↓`

- **Placer le tetromino immédiatement en bas**\
  `ESPACE`

- **Rotation dans le sens horaire**\
  `g`

- **Rotation dans le sens antihoraire**\
  `f`

- **Mettre en attente (hold) un tétrimino**\
  `h`

- **Sélectionner l'effet précédent**\
  `e`

- **Sélectionner l'effet suivant**\
  `r`

- **Vider les malus mis de côté**\
  `t`

- **Acheter l'effet sélectionné et l'envoyer directemment**
  - `y`
  - `clic gauche sur l'effet`

- **Acheter et mettre de côté l'effet sélectionné**\
  `u`

- **Sélectionner la cible des malus**\
  `clic gauche sur le nom de l'adversaire`

- **Quitter la partie en cours**\
  `q`
