#ifndef LOADER_H_
#define LOADER_H_

#include <string>

using namespace std;

class Loader {

public:
    static const int MaxProgramSize = 3584;

    Loader(string const &filename);
    ~Loader();

    unsigned char *buffer(void);
    int size(void);

private:

    // character buffer that holds the contents of the ROM file
    unsigned char *_buffer = NULL;

    // the size, in bytes, of the input ROM file
    int _size;
};

#endif
