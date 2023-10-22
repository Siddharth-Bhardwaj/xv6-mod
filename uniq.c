#include "types.h"
#include "stat.h"
#include "user.h"

char buf[3072];
char currentLine[3072];
char prevLine[3072];
char *output[3072];
int count[3072];

int toLower(int chr)
{
    if (chr >= 'A' && chr <= 'Z')
    {
        return chr + 32;
    }
    return chr;
}

char *strToLower(char *str)
{
    char *newPtr1 = str;
    char *newPtr2 = str;
    while (*newPtr1)
    {
        *newPtr2 = toLower(*newPtr1);
        newPtr2++;
        newPtr1++;
    }
    *newPtr2 = '\0';
    return str;
}

int compareStrings(char *str1, char *str2, int iFlag)
{
    if (iFlag == 1)
    {
        char *str1Lowered = malloc(strlen(str1) + 1);
        strcpy(str1Lowered, str1);
        strToLower(str1Lowered);
        char *str2Lowered = malloc(strlen(str2) + 1);
        strcpy(str2Lowered, str2);
        strToLower(str2Lowered);
        return strcmp(str1Lowered, str2Lowered);
    }
    else
    {
        return strcmp(str1, str2);
    }
}

void uniq(int fd, char *name, int iFlag, int cFlag, int dFlag)
{
    if (cFlag == 1 && dFlag == 1)
    {
        printf(1, "uniq: -c and -d cannot be used together\n");
        exit();
    }
    int i = 0, n, duplicatePrinted = 0, repeatLineCount = 0, outputCounter = 0, k;

    while ((n = read(fd, buf, sizeof(buf))) > 0)
    {
        i = 0;
        while (i < n)
        {
            int j = i;
            int lineCounter = 0;
            memset(currentLine, 0, sizeof(currentLine));
            while (j < n && buf[j] != '\n')
            {
                currentLine[lineCounter] = buf[j];
                j++;
                lineCounter++;
            }
            if (compareStrings(prevLine, currentLine, iFlag) != 0)
            {
                if (dFlag == 0 && strcmp(prevLine, "") != 0)
                {
                    if (cFlag == 1)
                    {
                        count[outputCounter] = repeatLineCount;
                    }
                    output[outputCounter] = (char *)malloc(sizeof(char *) * (strlen(prevLine) + 2));
                    for (k = 0; k < strlen(prevLine); k++)
                    {
                        output[outputCounter][k] = prevLine[k];
                    }
                    output[outputCounter][k] = '\0';
                    outputCounter++;
                }
                strcpy(prevLine, currentLine);
                duplicatePrinted = 0;
                repeatLineCount = 1;
            }
            else
            {
                if (dFlag == 1 && duplicatePrinted == 0)
                {
                    output[outputCounter] = (char *)malloc(sizeof(char *) * (strlen(prevLine) + 2));
                    for (k = 0; k < strlen(prevLine); k++)
                    {
                        output[outputCounter][k] = prevLine[k];
                    }
                    output[outputCounter][k] = '\0';
                    outputCounter++;
                }
                duplicatePrinted = 1;
                repeatLineCount++;
            }
            i = j + 1;
        }
    }
    if (dFlag == 0)
    {
        if (cFlag == 1)
        {
            count[outputCounter] = repeatLineCount;
        }
        output[outputCounter] = (char *)malloc(sizeof(char *) * (strlen(prevLine) + 2));
        for (k = 0; k < strlen(prevLine); k++)
        {
            output[outputCounter][k] = prevLine[k];
        }
        output[outputCounter][k] = '\0';
        outputCounter++;
    }

    if (n < 0)
    {
        printf(1, "uniq: read error\n");
        exit();
    }

    if (cFlag == 1)
    {
        for (i = 0; i < outputCounter; i++)
        {
            printf(1, "%d %s\n", count[i], output[i]);
        }
    }
    else
    {
        for (i = 0; i < outputCounter; i++)
        {
            printf(1, "%s\n", output[i]);
        }
    }
    
    free(output);
    exit();
}

int main(int argc, char *argv[])
{
    int fd, i, iFlag = 0, cFlag = 0, dFlag = 0;

    // in case there is no file and just flags
    int filePresent = 0;
    if (argc >= 1)
    {
        for (i = 1; i < argc; i++)
        {
            if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "-D") == 0 || strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "-C") == 0 || strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "-i") == 0)
            {
                continue;
            }
            else
            {
                filePresent = 1;
            }
        }
    }
    if (filePresent == 0)
    {
        for (i = 0; i < argc; i++)
        {
            if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "-D") == 0)
            {
                dFlag = 1;
            }
            else if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "-C") == 0)
            {
                cFlag = 1;
            }
            else if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "-I") == 0)
            {
                iFlag = 1;
            }
        }
        uniq(0, "", iFlag, cFlag, dFlag);
        exit();
    }

    if (argc <= 1)
    {
        uniq(0, "", 0, 0, 0);
        exit();
    }
    else if (argc == 2)
    {
        for (i = 1; i < argc; i++)
        {
            if ((fd = open(argv[i], 0)) < 0)
            {
                printf(1, "uniq: cannot open %s\n", argv[i]);
                exit();
            }
            uniq(fd, argv[i], 0, 0, 0);
            close(fd);
        }
        exit();
    }
    else
    {
        for (i = 0; i < argc; i++)
        {
            if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "-D") == 0)
            {
                dFlag = 1;
            }
            else if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "-C") == 0)
            {
                cFlag = 1;
            }
            else if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "-I") == 0)
            {
                iFlag = 1;
            }
        }

        for (i = 1; i < argc; i++)
        {
            if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "-D") == 0 || strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "-C") == 0 || strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "-i") == 0)
            {
                continue;
            }
            if ((fd = open(argv[i], 0)) < 0)
            {
                printf(1, "uniq: cannot open %s\n", argv[i]);
                exit();
            }
            uniq(fd, argv[i], iFlag, cFlag, dFlag);
            close(fd);
        }
        exit();
    }

    exit();
}