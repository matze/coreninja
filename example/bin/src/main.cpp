#include <cstdio>
#include "adder.h"
#include "sub.h"

int main()
{
    printf("(1 + 2) - 3 = %d\n", bar::sub(foo::add(1, 2), 3));
}
