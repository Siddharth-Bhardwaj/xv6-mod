#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf(1, "invalid usage. proper usage: randtest <max value>\n");
        exit();
    }
    int min = __INT32_MAX__, max = 0, sum = 0, i, maxValue = atoi(argv[1]);
    for (i = 0; i < 1000; i++) {
        int randomNum = random(maxValue);
        if (randomNum < min) {
            min = randomNum;
        }
        if (randomNum > max) {
            max = randomNum;
        }
        sum += randomNum;
    }
    printf(1, "min: %d\t max: %d\t mean: %d\n", min, max, sum/1000);
    exit();
}