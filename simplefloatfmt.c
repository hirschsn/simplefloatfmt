
#include <math.h>
#include <stddef.h>

static size_t
simplefloatfmt_itos(char *s, size_t n, int i)
{
    size_t m = 0;
    char *t = s, tmp;
    int d;

    /* Special case: i == 0 */
    if (i == 0) {
        if (m < n && t)
            *t = '0';
        return 1;
    }


    for (; i; i /= 10) {
        d = i % 10;
        if (m < n && t) {
            *t++ = '0' + d;
        }
        m++;
    }

    /* Reverse digits */
    for (; t > s; --t, ++s) {
        tmp = *(t-1);
        *(t-1) = *s;
        *s = tmp;
    }

    return m;
}


size_t
simplefloatfmt_ftoa(char *s, size_t n, float f, size_t nfracdigits)
{
    size_t m = 0;
    size_t ret;
    float intg, frac;
    int iintg, ifrac, sign;

    sign = f < 0;
    f = fabs(f);
    frac = modff(f, &intg);

    iintg = (int) intg;
    ifrac = (int) (frac * pow(10, nfracdigits)); /* Hack */


    if (sign) {
        if (m < n && s)
            *s++ = '-';
        m++;
    }

    ret = simplefloatfmt_itos(s, n - m, iintg);
    if (m < n && s)
        s += ret;
    m += ret;
    

    if (m < n && s)
        *s++ = '.';
    m++;

    ret = simplefloatfmt_itos(s, n - m, ifrac);
    if (m < n && s)
        s += ret;
    m += ret;

    /* Terminator */
    if (m < n && s)
        *s = 0;
    else if (s)
        *(s-1) = 0;
    m++;

    return m;
}

