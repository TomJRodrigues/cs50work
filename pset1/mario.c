#include <stdio.h>
#include <cs50.h>

int main(int argc, char* argv[])
{
    int num = 0;
    
    do
    {
        printf("height: ");
        num = GetInt();
    }
    while (num <= 0 || num >= 23);
  
    // iterates the number of times that the user inputs
    for (int i = num; i > 0; i--)
    {
        //prints the blank spaces
        for (int j = i-1; j > 0; j--)
        {
            printf(" ");
        }
        //prints the sharps
        for (int k = i - 2; k < num; k++)
        {
            printf("#");
        }
        //goes to a new line after the # have been printed on each line
        printf("\n");
    }
    
    return 0;   
}
