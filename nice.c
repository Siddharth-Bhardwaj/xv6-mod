#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf(1, "invalid usage. proper usage: nice <pid> <nice value>\n");
        exit();
    }
    char *nicearg = argv[2];
    int nice;
    if (strcmp(strchr(argv[2], '-'), argv[2]) == 0) {
        // parsing if nice is -ve
        nicearg++;
        nice = atoi(nicearg) * -1;
    } else {
        // parsing if nice is +ve
        nice = atoi(argv[2]);
    }
    setnice(atoi(argv[1]), nice);
    exit();
}