#include <stdio.h>
#include <fcntl.h>

int main(int argc, char** argv) {
    if(argc != 2) {
        printf("Usage: ./keylogger <file-name>");
        return -1;
    }

    int fd = open(argv[1], O_RDONLY, 0);

}
