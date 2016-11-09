#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int main(void)
{
    //declares the card_number
    long long card_number = 0;

    //asks user for card number and verifies it's <19 digits and positive TODO make this work
    do
    {
        printf("Number: ");
        card_number = GetLongLong();
    }
    while (9999999999999999 < card_number || card_number < 1000000000000);  //make it less than 19 digits long or else there's long long overflow
    
    /* count number of digits */
    int c = 0; /* digit position */
    long long n = card_number;
    
    while ( n != 0)
    {
        n /= 10;
        c++;
    }
    
    int number_array[c];
    
    c = 0;
    n = card_number;
    
    /* extract each digit  and put it in array*/
    while (n != 0)
    {
        number_array[c] = n % 10;
        n /= 10;
        c++;
    }
    
   // Now we should take every other digit, double it, and enter it into another array
   
   int d = (c / 2); // New array length
   
   int every_other_array[d];
   
   for (int i = 1, j = 0; i < c; i = i + 2, j++)
   {
        every_other_array[j] = number_array[i] * 2;
   }
   
   // Then we should add all of the digits in the doubled array
   int double_sum = 0;
   
   for (int i = 0; i < d; i++)
   {
       while (every_other_array[i] != 0)
       {
           double_sum += every_other_array[i] % 10;
           every_other_array[i] /= 10;
       }
   }
   
   /* Then we should add all of the digits NOT multiplied by 2 */
   // New array length
   int e = 0;
   if (c % 2 == 0)
       e = c / 2;
   else
       e = (c / 2) + 1;
   
   // declare new array
   int single_array[e];
   
   for (int i = 0, j = 0; i < c; i = i + 2, j++)
   {
        single_array[j] = number_array[i];
   }
    
   // Add the single digits in the array
   int single_sum = 0;
   
   for (int i = 0; i < e; i++)
   {
       while (single_array[i] != 0)
       {
           single_sum += single_array[i] % 10;
           single_array[i] /= 10;
       }
   }
   
   // Add total sum
   int total_sum = 0;
   total_sum = double_sum + single_sum;
   
   // Check if divisible by 10 and what kind of card it is:
   if (number_array[c - 1] == 3 && (number_array[c - 2] == 4 || number_array[c - 2] == 7) && total_sum % 10 == 0)
       printf("AMEX\n");
   else if (number_array[c - 1] == 5 && number_array[c - 2] > 0 && number_array[c - 2] < 6 && total_sum % 10 == 0)
       printf("MASTERCARD\n");
   else if (number_array[c - 1] == 4 && total_sum % 10 == 0)
       printf("VISA\n");
   else
       printf("INVALID\n");
       
return 0;
}
