# Wheel CTN

Single-thread with the given `dictionary.txt` and `wheel.txt`:

```sh
time ./dist/bin/wheel-ctn default

> ...
> Found 1739 words
> ./dist/bin/wheel-ctn default  0.10s user 0.01s system 99% cpu 0.114 total
```

```
Of the 0.114s in total:

0.105 is spent making a cache for the dictionary
0.009 is spent looking for the words
```

The above is achieved with:
```
LLVM 12.0.1, clang++
C++ 17

Built in release mode
Important compile flags: -O3 -std=c++17

CPU: Intel i7-10875H
```

## Executable and VS solution

A compiled executable for Windows x86_64 is located in `vs/dist/bin/Release/wheel-ctn.exe`.

This project is built with CMake, to build your own Visual Studio solution please follow:
```sh
cd <project_dir>
mkdir bld
cd bld/
cmake -DCMAKE_RELEASE_TYPE=Release ..
```
There should now be a `bld/` directory with a valid (for your system) Visual Studio solution.

If it is not possible to install CMake, you can make use of the provided solution under `vs/`, the
only caveat is that all paths must be corrected to your own system.
