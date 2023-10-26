#include "types.h"
#include "stat.h"
#include "user.h"

#define X 10000

int main(int argc, char *argv[])
{
    int i;
    // creating 10 processes with same nice values
    for (i = 0; i < 10; i++)
    {
        int pid = fork();
        if (pid == 0)
        {
            int count = 0;
            printf(1, "process created with pid: %d\n", getpid());
            while (1)
            {
                int j, primes = 0;
                // finding primes under 9999 to use up CPU time
                for (j = 1; j < 999; j++)
                {
                    int k = 2;
                    while (k <= j)
                    {
                        if (j % k == 0)
                        {
                            break;
                        }
                        k++;
                    }
                    if (j == k)
                    {
                        primes++;
                    }
                }
                count++;
                if (count > X)
                {
                    count = 0;
                    printf(1, "Process with pid: %d ran 10000 times\n", getpid());
                }
            }
        }
    }

    exit();
}