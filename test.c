
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

size_t
simplefloatfmt_ftoa(char *s, size_t n, float f, size_t nfracdigits);


void test(float v, size_t bufsiz, const char *expect)
{
    if (!bufsiz)
        bufsiz = simplefloatfmt_ftoa(NULL, 0, v, 5);

    char s[bufsiz];
    simplefloatfmt_ftoa(s, bufsiz, v, 5);

    printf("Test %10f %10zu failed: Got %20s, expected %20s", v, bufsiz, s, expect);
    if (strcmp(s, expect))
        printf(" FAILED.\n");
    else
        printf(" passed.\n");
}

int main(void)
{
    test(5.2, 0, "5.19999");
    test(2., 0, "2.0");
    test(-0.71, 0, "-0.70999");
    test(0, 0, "0.0");
    test(31.9, 3, "31"); /* truncation test */
}
