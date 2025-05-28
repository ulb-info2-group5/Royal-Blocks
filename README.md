# Royal Blocks

## Group members

| First Name | Last Name           | Student ID  |
| ---------- | ------------------- | ----------- |
| Tao        | Chau                |  000567638  |
| Juliette   | Cornu-Besser        |  000581723  |
| Quentin    | Bernard Bouissières |  000572078  |
| Jonas      | Schellekens         |  000590985  |
| Ethan      | Van Ruyskenvelde    |  000589640  |
| Lucas      | Verbeiren           |  000591223  |
| Ernest     | Malysz              |  000514682  |
| Rafaou     | Gajewicz            |  000569354  |

## Build the project

### Dépendances

The project requires the installation of the following programs and libraries (the commands are for Debian-based systems):

- **Make**\
  `sudo apt install make`
- **CMake**\
  `sudo apt install cmake`
- **Git**\
  `sudo apt install git`
- **SQLite3**\
  `sudo apt install libsqlite3-dev`
- **Qt5 (for the GUI)**\
  `sudo apt install qtbase5-dev`

---

#### Installing Dependencies on Windows

To easily install all required dependencies on Windows, we recommend using `vcpkg`.

**Visual Studio** is required to use **vcpkg**.

We also recommend installing **MinGW** to have access to the **g++** compiler.
Don't forget to install **make** and **cmake** with **MinGW** in order to build the project.

##### 1. Install vcpkg

```sh
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
bootstrap-vcpkg.bat
```

add **vcpkg** to your `PATH` to use it easily across all your projects.

##### 2. Install the project dependencies

```bash
vcpkg install boost-system boost-thread sqlite3
```

##### 4. Install Qt5 for Windows

Qt5 is not available via **vcpkg**.
Download it directly from [qt.io](https://www.qt.io/download) and install the following module:

- Qt 5.x (Choose **MinGW** or **MSVC** depending on the compiler you are using).

---

#### Remarque

Other libraries, such as **ftxui** and **nlohmann**, are also required for compilation, but they are automatically included via CMake using the **FetchContent** feature.

**The project also requires:**

- **GCC 13** or higher
- and **C++23** support

### Compilation

The project can be compiled in **Release** or **Debug** :

```sh
make release
```

```sh
make debug
```

## Running the Game

### Launching the Program

To launch **Royal Blocks**, you can choose between two interfaces:

- Graphical interface:

  ```sh
  ./royal-blocks-gui
  ```

- Terminal interface:

  ```sh
  ./royal-blocks-tui
  ```

To start the server, run:

```sh
./royal-blocks-server
```

### Choosing the IP and Port

To establish communication between the client and the server:

#### Server

You can specify a custom port as an argument when launching the server:

```sh
./royal-blocks-server <port>
```

If no argument is provided, the server will read the **SERVER_PORT** environment variable.
If the variable is not set, the default port **1234** will be used.

#### Client

In both the graphical and terminal interfaces, you can modify the server's IP and port directly.
These settings will be saved in the configuration file:

- `~/.config/royal-blocks/config.json` on Linux

- `%APPDATA%\royal-blocks\config.json` on Windows

If no configuration file exists, a default one will be automatically created using:

- the IP address defined by the **SERVER_IP** environment variable (or **127.0.0.1** by default),
- and the port defined by **SERVER_PORT** (or **1234** by default).

### Important Information About Terminal Display

If you can't see all game information on the screen, you may need to **zoom out** in your terminal window.

### Royal Blocks Controls

Here is a list of the different keys used to move and rotate the pieces in the game:

- **Move left**\
  `←`

- **Move right**\
  `→`

- **Soft drop**\
  `↓`

- **Hard drop (instantly place the tetromino at the bottom)**\
  `ESPACE`

- **Rotate clockwise**\
  `g`

- **Rotate counterclockwise**\
  `f`

- **Hold current tetromino**\
  `h`

- **Select previous effect**\
  `e`

- **Select next effect**\
  `r`

- **Clear stored maluses**\
  `t`

- **Buy and immediately send the selected effect**
  - `y`
  - `left-click on the effect`

- **Buy and store the selected effect**\
  `u`

- **Select target for maluses**\
  `left-click on the opponent's name`

- **Quit the current game**\
  `q`

## License

This project is licensed under the [GNU GPL v3](https://www.gnu.org/licenses/gpl-3.0.html).

## License and Third-Party Software

This project uses several open source components.  
Please see [LICENSES_THIRD_PARTY.md](./LICENSES_THIRD_PARTY.md) for details.
