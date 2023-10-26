#include "types.h"
#include "stat.h"
#include "user.h"

#define X 10000

int main(int argc, char *argv[])
{
    int pid = fork();
    if (pid == 0)
    {
        int count = 0;
        setnice(getpid(), -20);
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
                printf(1, "LEAST NICE (HIGHEST PRIORITY) ran 10000 times with nice = -20\n");
            }
        }
    }

    pid = fork();
    if (pid == 0)
    {
        int count = 0;
        while (1)
        {
            int j, primes = 0;
            // finding primes under 9999 to use up CPU time
            for (j = 1; j < 9999; j++)
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
                printf(1, "DEFAULT NICE (MEDIUM PRIORITY) ran 10000 times with nice = 0\n");
            }
        }
    }

    pid = fork();
    if (pid == 0)
    {
        int count = 0, extCount = 0, nice = 19;

        setnice(getpid(), 19);
        while (1)
        {
            int j, primes = 0;
            // finding primes under 9999 to use up CPU time
            for (j = 1; j < 9999; j++)
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
                count = 1;
                extCount++;
                if (extCount == 5)
                {
                    setnice(getpid(), -30);
                    nice += -30;
                    printf(1, "Decreasing nice value of process with pid: %d by 30\n");
                }
                printf(1, "TEST PROCESS (DYNAMIC PRIORITY) ran 10000 times with nice = %d\n", nice);
            }
        }
    }
    exit();
}
