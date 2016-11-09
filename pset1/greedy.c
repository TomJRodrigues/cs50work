#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main()
{
    // declares change to be zero
    float change = 0;
    
    // prompts user for float that is positive
    do
    {
        printf("How much change is owed?:\n");
        change = GetFloat();
        
    }
    while (change < 0);
    
    // convert float dollars to int cents
    int cents = 0;
    cents = change * 100 + 0.5;
    
    // prints the amount of change we are working with
    printf("Number cents: %d\n", cents);
    
    // stores and prints number of quarters given
    int quarters = 0;
    quarters = cents / 25;
    printf("Number of quarters given: %d\n", quarters);
    
    // stores and prints amount of change after giving quarters
    int after_quarters = 0;
    after_quarters = cents % 25;
    printf("Cents remaining after giving quarters: %d\n", after_quarters);
    
    // dimes
    int dimes = 0;
    dimes = after_quarters / 10;
    printf("Number of dimes given: %d\n", dimes);
    
    // after dimes
    int after_dimes = 0;
    after_dimes = after_quarters % 10;
    printf("Cents remaning after giving dimes: %d\n", after_dimes);
    
    // nickels
    int nickels = 0;
    nickels = after_dimes / 5;
    printf("Number of nickels given: %d\n", nickels);
    
    // after nickels
    int after_nickels = 0;
    after_nickels = after_dimes % 5;
    printf("Cents remaining after giving nickels: %d\n", after_nickels);
    
    // pennies
    int pennies = 0;
    pennies = after_nickels / 1;
    printf("Number of pennies given: %d\n", pennies);
    
    // after pennies
    int after_pennies = 0;
    after_pennies = after_nickels % 1;
    printf("Cents remaining after giving pennies: %d\n", after_pennies);
    
    // add number of coins and prints
    int total_coins = 0;
    total_coins = quarters + dimes + nickels + pennies;
    printf("Total number of coins: %d\n", total_coins);
    
    return 0;
}
