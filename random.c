#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf(1, "invalid usage. proper usage: random <max value>\n");
        exit();
    }
    printf(1, "%d\n", random(atoi(argv[1])));
    exit();
}