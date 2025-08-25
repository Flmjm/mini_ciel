#include "../src/lib_parse.h"

int main(int argc, char **argv) {
    if (argc != 2)
        return 0;
    char *mdr;
    char *input = argv[1];
    mdr = getenv(input);
    if (!mdr)
        return 1;
    printf("%s\n", mdr);
    return 0;
}