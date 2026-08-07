# DownloadOrganizer

> A lightweight C++ application that automatically categorizes files in a specified directory using config rules.

**Status:** 🚧 Early Development

## About

DownloadOrganizer is a project I started to explore a different approach to organizing files on a computer.

The long-term idea is to build a system that can understand the files entering a computer and organize them with less manual work. Instead of relying only on file extensions or manually written rules, the project may eventually use information such as file content, context, and where the file came from.

Another important part of the idea is personalization: the system should gradually learn how the user prefers their files to be organized.

The project is still **very early**. What exists now is only the first small step toward that idea.

## Current State

For now, the project is focused on building the basic file-organization core.

Currently, it has:

* C++20 / CMake project structure
* Configuration-based file categorization
* Basic file organization
* Filesystem operations
* Basic reporting
* A simple separation between the main components

Many parts of the original idea are not implemented yet.

## Project Structure

```text
DownloadOrganizer/
│
├── CMakeLists.txt
│
├── config/
│   └── rules.txt
│
├── include/
│   ├── Core/
│   │   ├── ConfigParser.hpp
│   │   └── FileOrganizer.hpp
│   │
│   └── Utils/
│       └── StringUtils.hpp
│
└── src/
    ├── main.cpp
    │
    ├── Core/
    │   ├── ConfigParser.cpp
    │   └── FileOrganizer.cpp
    │
    └── Utils/
        └── StringUtils.cpp
```

## Build

The project uses CMake and requires a C++20-compatible compiler.

```bash
cmake -S . -B build
cmake --build build
```

## What's Next?

The project will be developed gradually as I learn and experiment with new ideas.

Some of the areas I would like to explore include:

* A graphical interface
* Less dependence on manually written rules
* Understanding files beyond their extensions
* Using file context and source information
* More flexible organization
* Learning from the user's decisions and corrections

This list is not a fixed roadmap. The direction of the project may change as development continues.

## License

This project is licensed under the MIT License.
