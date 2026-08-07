# DownloadOrganizer

> A small C++ prototype for organizing files into category folders using configurable keyword rules.

**Status:** 🚧 Early prototype / long-term learning project

## Overview

DownloadOrganizer started from a practical problem: a cluttered Downloads folder. The broader goal is to build a tool that can reduce the manual work of sorting files and, over time, become more flexible and context-aware than a simple rule-based sorter.

This project is intentionally long-term. It is meant to grow with the author’s skills rather than be treated as a quick one-off project. At the same time, the current codebase is still a prototype: it works as a basic organizer, but it is not a polished end-user application.

## What the project does now

The current implementation is a keyword-driven organizer. It does the following:

- reads category rules from `config/rules.txt`
- scans a source directory with `std::filesystem::directory_iterator`
- matches each filename against configured keywords in a case-insensitive way
- creates destination folders if they do not already exist
- copies or moves files into a category folder depending on the `TransferMethod`
- records processed counts and filesystem errors in an `OrganizingReport`

The bundled demo in `src/main.cpp` is hardcoded to read the project root, open `config/rules.txt`, and process files from `PROJECT_ROOT_DIR/test_data/source` into `PROJECT_ROOT_DIR/test_data/target`. The current demo passes `CollisionPolicy::RENAME`, but collision handling is still under development and should not be treated as fully implemented.

## Implementation details

The code is deliberately small and split into a few main parts:

- `ConfigParser` loads category/keyword rules from a text file
- `FileOrganizer` iterates through files, finds the matching category, and transfers the file
- `StringUtils` handles trimming, lowercase conversion, and basic line/file reading utilities used by the config and organizer code
- `main.cpp` wires the parser and organizer together for the local demo workflow

The transfer layer supports `MOVE`, `COPY`, `HARDLINK`, and `SOFTLINK`, although the current demo uses `COPY`.

This is still a straightforward rule-based system. It does not yet include a graphical interface, user preferences, or deeper semantic understanding of file content.

## Configuration format

Rules are stored in `config/rules.txt` with a simple category-to-keyword mapping:

```text
Documents: pdf, doc, docx, txt
Images: jpg, jpeg, png, gif
Audio: mp3, wav, flac
SourceCode: cpp, h, hpp, py, java
```

The parser accepts this format:

```text
CategoryName: keyword1, keyword2, keyword3
```

Lines without a category header are treated as additional keywords for the most recent category.

## Build

The project uses CMake and requires a C++20-compatible compiler.

```bash
cmake -S . -B build
cmake --build build
```

Then run the executable from the build directory:

```bash
./build/DownloadOrganizer
```

The demo reads from a project-local `test_data/source` directory. If that source folder does not exist, the directory scan will fail. The target directory is created as needed for each category during organization.

## Project structure

```text
DownloadOrganizer/
├── CMakeLists.txt
├── LICENSE
├── README.md
├── config/
│   └── rules.txt
├── include/
│   ├── Core/
│   │   ├── ConfigParser.hpp
│   │   └── FileOrganizer.hpp
│   └── Utils/
│       └── StringUtils.hpp
├── src/
│   ├── Core/
│   │   ├── ConfigParser.cpp
│   │   └── FileOrganizer.cpp
│   ├── Utils/
│   │   └── StringUtils.cpp
│   └── main.cpp
└── (example local folders used by the demo)
```

## Current limitations

This project is still intentionally limited in scope:

- it relies on manually maintained keyword rules
- it is not yet a general-purpose user-facing application
- it does not include a polished UI or installer flow
- its organization logic is based on filename matching rather than deeper file understanding
- it is still focused on learning and iteration rather than production-level release work

The long-term direction is to make the organizer more flexible and more intelligent over time, but the current codebase is best understood as a prototype stepping stone toward that goal.

## License

This project is licensed under the MIT License.
