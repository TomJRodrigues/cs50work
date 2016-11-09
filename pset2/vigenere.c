/* 
  Tom Rodrigues
  tomjrodrigues@gmail.com
  
  vigenere.c
  A program to encrypt text with the vigenere cypher.
*/

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char * argv[])
{
    string key = argv[1];
    int keylen = strlen(argv[1]);
   
    // Ensures user provides 2 arguments
    if (argc != 2)
    {
       printf("Please give me a valid key\n");
       return 1;
    }
    else
    {
        // User enters plaintext to be encrypted
        string plntxt = GetString();
        if (plntxt != NULL)
        {
            // Encrypts and prints
            for (int i = 0, k = 0; i < strlen(plntxt); i++)
            {
                int c = 0;
               
               // Check if text is upper case or lower case
               // If so, switch to alpha number and encrypt
               if (isupper(plntxt[i]) && isupper(key[k]))
               {
                   c = (((int)plntxt[i] - 65 + (int)key[k] - 65) % 26) + 65;
                   printf("%c", (char) c);
                   k++;
                   k = k % keylen;
               }
               else if (isupper(plntxt[i]) && islower(key[k]))
               {
                   c = (((int)plntxt[i] - 65 + ((int)key[k] - 32) - 65) % 26) + 65;
                   printf("%c", (char) c);
                   k++;
                   k = k % keylen;
               }
               else if (islower(plntxt[i]) && islower(key[k]))
               {
                   c = (((int)plntxt[i] - 97 + (int)key[k] - 97) % 26) + 97;
                   printf("%c", (char) c);
                   k++;
                   k = k % keylen;
               }
               else if (islower(plntxt[i]) && isupper(key[k]))
               {
                   c = (((int)plntxt[i] - 97 + ((int)key[k] + 32) - 97) % 26) + 97;
                   printf("%c", (char) c);
                   k++;
                   k = k % keylen;
               }
               else
               {
                   printf("%c", plntxt[i]);
               }
            }
        }
        printf("\n");
    }
    return 0;
}
