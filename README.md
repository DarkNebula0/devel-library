# Devel C++ Library

Welcome to the new and improved Devel C++ Library! This repository is a rewrite of the original library, now with
enhanced features and Linux compatibility.

This library was initially written to provide utility functions for developing private servers and other projects. After
spending some time in a private repository on Bitbucket, we decided to make it public on GitHub. We hope that you will
find some interesting functions that you can use in your projects.

For a detailed list of all the files and their brief descriptions, please refer to
the [documentation](https://darknebula0.github.io/devel-library/).

# Features

The library is organized into several modules, each providing a set of related functionalities:

- Core: Contains fundamental utilities such as CharArray, ObjectData, Singleton, Timer, and various utility functions.
- IO: Handles input/output operations, including Buffer, Dir, JsonArray, JsonDocument, JsonObject, Path, ReadStream,
  WriteStream.
- Logging: Contains logging functions and macros.
- Serializing: Provides functionalities for serializing data, including core types and JSON serializable types.
- Threading: Contains utilities for multithreading, including LockGuard, Mutex, MutexVector, SafeQueue, and ThreadPool.

# Dependencies

To build this library, you will need to install vcpkg and use it in manifest mode
(see [here](https://learn.microsoft.com/de-de/vcpkg/users/manifests) for more information).

The current dependencies are:

- boost-asio
- catch2
- rang

Please note that the submodule is only needed to build the documentation, not the library itself.

# Repository Status

This repository is actively maintained and we welcome contributions. If you encounter any issues, please refer to this
README or open an issue in the repository.
