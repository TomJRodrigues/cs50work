#include <stdio.h>
#include <cs50.h>

int main(void)
{
    printf("%c\n", ('z' - 'a' + 1) % 26 + 'a');
    return 0;
}
