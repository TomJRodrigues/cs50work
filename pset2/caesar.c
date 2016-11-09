/* 
  Tom Rodrigues
  tomjrodrigues@gmail.com
  
  caesar.c
  A program to encrypt text with a simple Caesar cypher
*/

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char * argv[])
{
     string key = argv[1];
     /* Ensures user provides 2 arguments */
     if (argc != 2)
     {
        printf("Please give me a valid key\n");
        return 1;
     }
     else
     {      
        /* Converts user string into integer key */    
        int ROT = atoi(key) % 26;
        
        // Check that it is a valid key
        if (ROT == 0)
        {
            printf("Invalid key. Try again.\n");
            return 1;
        }
       
        printf("Rotation amount:%d\n", ROT);
       
        // User enters plaintext to be encrypted
        string plaintext = GetString();
        if (plaintext != NULL)
        {
           // Encrypt and print
           for (int i = 0, n = strlen(plaintext); i < n; i++)
           {
               int c = 0;
               
               // Check if text is upper case or lower case
               // If so, switch to alpha number and encrypt
               if (isupper(plaintext[i]))
               {
                   c = (((int)plaintext[i] - 65 + ROT) % 26) + 65;
                   printf("%c", (char) c);
               }
               else if (islower(plaintext[i]))
               {
                   c = (((int)plaintext[i] - 97 + ROT) % 26) + 97;
                   printf("%c", (char) c);
               }
               else
               {
                   printf("%c", plaintext[i]);
               }
           }
        }
        printf("\n");
    }
    return 0;
}
