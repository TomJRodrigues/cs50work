#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    printf("Enter your name: \n");
    string name = GetString();
    
    // loop through the string
    for (int i = 0, n = strlen(name); i < n; i++)
    {
        /* if it finds a space and the next character isn't a
        space then it capitalizes and prints that character */
        if (name[i] == ' ' && name[i + 1] != ' ')
        {
            printf("%c", toupper(name[i + 1]));
        }
    }
    
    // prints new line after initials
    printf("\n");
    
    return 0;
}
