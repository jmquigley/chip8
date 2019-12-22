# chip8

> My implementation of a chip 8 emulator using c++

The program was devloped under Debian 10 using the following application requirements to build and execute:

- [cmake >= 3.13.4](https://cmake.org/)
- gcc 8.3.x
- [Simple DirectMedia Layer 2](https://www.libsdl.org/)
- [cppcheck](https://sourceforge.net/p/cppcheck/wiki/Home/)

This code is incomplete and a WIP (don't use it).

## Usage

To build the code from scratch use:

```
$ ./build.sh
```

This will generate the Makefile using cmake and execute the build process.  If successful, then an executable named `chip8` will be available in `./build/chip8`.  The program is executed directly using:

```
$ ./build/chip8 {rom file}
```

e.g.

```
$ ./build/chip8 roms/INVADERS
```

To remove all intermediate files use:

```
$ ./clean.sh
```

This will remove the `build` directory and executable files.


## References

1. https://www.libsdl.org/
2. https://sourceforge.net/p/cppcheck/wiki/Home/
