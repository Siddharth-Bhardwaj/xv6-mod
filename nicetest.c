#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char*argv[]) {
    int pid = fork();
    if (pid < 0) {
        printf(1, "fork failed\n");
    } else if (pid == 0) {
        printf(1, "Child created with pid: %d\n", getpid());
        int j, primes = 0;
        // finding primes under 9999 to use up CPU time
        for (j = 1; j < 99999; j++) {
            int k = 2;
            while (k <= j) {
                if (j % k == 0) {
                    break;
                }
                k++;
            }
            if (j == k) {
                primes++;
            }
        }
        printf(1, "%d\n", primes);
    } else {
        wait();
        printf(1, "Parent with pid %d created child with pid %d\n", getpid(), pid);
    }
    
    exit();
}