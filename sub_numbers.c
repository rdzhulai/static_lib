#include <limits.h>
#include <errno.h>
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
