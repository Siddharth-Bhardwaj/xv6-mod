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
        setnice(getpid(), -12);
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
                printf(1, "LEAST NICE (HIGHEST PRIORITY) ran 10000 times with nice = -12\n");
            }
        }
    }

    pid = fork();
    if (pid == 0)
    {
        int count = 0;

        setnice(getpid(), -6);
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
                printf(1, "MODERATELY LESS NICE (HIGH PRIORITY) ran 10000 times with nice = -6\n");
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
        int count = 0;

        setnice(getpid(), 4);
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
                printf(1, "MODERATELY NICE (LOW PRIORITY) ran 10000 times with nice = 4\n");
            }
        }
    }

    pid = fork();
    if (pid == 0)
    {
        int count = 0;

        setnice(getpid(), 10);
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
                printf(1, "MOST NICE (LOWEST PRIORITY) ran 10000 times with nice = 10\n");
            }
        }
    }
    exit();
}