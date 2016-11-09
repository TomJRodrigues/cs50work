#include <stdio.h>
#include <cs50.h>

int main(int argc, char* argv[])
{
    int n = 0;
    
    do
    {
        printf("Type a positive number: ");
        n = GetInt();
    }
    while (n < 0);
    
    printf("Thanks for the positive number!\n");
    
    return 0;
}
