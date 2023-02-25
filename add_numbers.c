#include <limits.h>
#include <errno.h>
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
