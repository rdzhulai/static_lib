#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "mmath.h"

long add(const long a, const long b)
// The function returns the sum of the two parameters.
// It handles overflow(underflow) by returning macro LONG_MIN(LONG_MAX) and setting errno to ERANGE.
{
    if (a < 0 && b < 0 && b < LONG_MIN - a)
    {
        errno = ERANGE;
        return LONG_MAX;
    }
    if (a > 0 && b > 0 && b > LONG_MAX - a)
    {
        errno = ERANGE;
        return LONG_MIN;
    }
    return a + b;
}

long sub(const long a, const long b)
// The function returns the substraction of the two parameters.
// It handles overflow(underflow) by returning macro LONG_MIN(LONG_MAX) and setting errno to ERANGE.
{
    if (a < 0 && b > 0 && a < LONG_MIN + b)
    {
        errno = ERANGE;
        return LONG_MAX;
    }
    if (a > 0 && b < 0 && a > LONG_MAX - b)
    {
        errno = ERANGE;
        return LONG_MIN;
    }
    return a - b;
}

typedef struct operation
{
    long (*func)(const long, const long);
    char sign;
    char name[20];
} operation;

int main(int argc, char *argv[])
{
    char *endptr;
    long val1, val2, result;

    int operation_index = -1;
    const int OPERATIONS_SIZE = 2;
    operation *operations = calloc(OPERATIONS_SIZE, sizeof(operation));
    operations[0].func = add;
    operations[0].sign = '+';
    strcpy(operations[0].name, "add");
    operations[1].func = sub;
    operations[1].sign = '-';
    strcpy(operations[1].name, "sub");

    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s operation(add/sub) str\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < OPERATIONS_SIZE; i++)
    {
        if (!strcmp(argv[1], operations[i].name))
        {
            operation_index = i;
            break;
        }
    }
    if (operation_index == -1)
    {
        fprintf(stderr, "Usage: %s operation(add/sub) str\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    errno = 0; /* To distinguish success/failure after call */
    val1 = strtol(argv[2], &endptr, 10);

    /* Check for various possible errors */

    if (errno != 0)
    {
        perror("strtol");
        exit(EXIT_FAILURE);
    }

    if (endptr == argv[2])
    {
        fprintf(stderr, "No digits were found\n");
        exit(EXIT_FAILURE);
    }

    /* If we got here, strtol() successfully parsed a number */
    if (argc == 3)
    {
        printf("Result: %ld\n", val1);
        exit(EXIT_SUCCESS);
    }

    for (int i = 3; i < argc; i++)
    {
        errno = 0; /* To distinguish success/failure after call */
        val2 = strtol(argv[i], &endptr, 10);

        /* Check for various possible errors */

        if (errno != 0)
        {
            perror("strtol");
            exit(EXIT_FAILURE);
        }

        if (endptr == argv[i])
        {
            fprintf(stderr, "No digits were found\n");
            exit(EXIT_FAILURE);
        }

        /* If we got here, strtol() successfully parsed a number */
        result = (*operations[operation_index].func)(val1, val2);
        if (errno != 0)
        {
            perror(operations[operation_index].name);
            exit(EXIT_FAILURE);
        }
        getchar();
        printf("Result: %ld %c %ld = %ld\n", val1, operations[operation_index].sign, val2, result);
        val1 = result;
    }
    free(operations);
    exit(EXIT_SUCCESS);
}
