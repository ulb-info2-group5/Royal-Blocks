# Third-Party Licenses

This file lists licenses of third-party libraries used in this project.

---

## 1. Boost.Asio

**License**: Boost Software License 1.0  
**Source**: [asio](https://github.com/boostorg/asio)\
**Usage**: Included directly in `lib/asio/` folder.  
**Notes**: Only the standalone headers are used. No Boost dependency required.

---

## 2. SQLite3

**License**: Public Domain  
**Source**: [SQLite3](https://www.sqlite.org/index.html)\
**Usage**: Included directly in the `lib/sqlite/` folder of this project.  
**Notes**: SQLite is released into the public domain. You may modify, use, and redistribute it freely, without any attribution or license restriction.

---

## 3. Qt5

**License**: GNU Lesser General Public License v3.0 or commercial license  
**Source**: [Qt5](https://www.qt.io)\
**Notes**: Dynamically linked in this project.

---

## 4. FTXUI

**License**: MIT License  
**Source**: [ftxui](https://github.com/ArthurSonzogni/FTXUI)\
**Usage**: Integrated using CMake FetchContent.

---

## 5. nlohmann_json

**License**: MIT License  
**Source**: [nlohmann](https://github.com/nlohmann/json)\
**Usage**: Integrated using CMake FetchContent.

---

## 6. bcrypt (by Christoph Hilchenbach, based on Niels Provos)

**License**: BSD 4-Clause License  
**Source**: [bcrypt](https://github.com/hilch/Bcrypt.cpp)\
**Usage**: Included directly in the `lib/` folder of this project.  
**Notes**: Attribution clause #3 applies:  
This product includes software developed by Niels Provos.

## 6. cpp-make-cmake-template (by [@Evr5](https://github.com/Evr5)

**License**: MIT License  
**Source**: [cpp-make-cmake-template](https://github.com/Evr5/cpp-make-cmake-template)\
**Usage**: Provides a cross-platform CMake + Make integration, a support for static and dynamic linking and a modular structure.
