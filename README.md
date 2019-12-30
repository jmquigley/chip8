# chip8

> My implementation of a chip 8 emulator using c++

The program was devloped under Debian 10 using the following application requirements to build and execute:

- [cmake >= 3.13.4](https://cmake.org/)
- gcc 8.3.x
- [Simple DirectMedia Layer 2](https://www.libsdl.org/)
- [cppcheck](https://sourceforge.net/p/cppcheck/wiki/Home/)
- [valgrind](https://valgrind.org/)

This code is incomplete and a WIP (don't use it).

## Usage

To build the code from scratch use:

```
$ ./build.sh
```

This will generate the Makefile using cmake and execute the build process.  If successful, then an executable named `chip8` will be available in `./build/chip8`.  The program is executed directly using:

```
$ ./build/app {rom file}
```

e.g.

```
$ ./build/app roms/INVADERS
```

The project also contains a BASH wrapper at the root of the script to perform the execution:

```
$ ./chip8 roms/INVADERS
```

The build uses an "out of source" method for building its objects.  To remove all intermediate files use:

```
$ ./clean.sh
```

This will remove the `build` directory and executable files.  One could also just remove the `build` directory directly.

To see debugging messages set the `DEBUG` environment variable to true and rebuild the project.  This will be slower than the release type build becuase the exe will contain debug symbols and log messages will be printed to standard out.


## References

1. https://www.libsdl.org/
2. https://sourceforge.net/p/cppcheck/wiki/Home/
