/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 * 
 * Edited by Tom Rodrigues tomjrodrigues@gmail.com 30-5-2015
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
            /* Linear search, no check if input is negative.
            for (int i = 0; i < n; i++)
            {    
                if (value == values[i])
                {
                    return true;
                }
            }
            */
            
    /* Binary search */
    
    // Set values for top and bottom of search
    int lower = 0;
    int upper = n -1;
    
    while (lower <= upper)
    {
        // find the middle
        int middle = (upper + lower) / 2;
        
        // evaluate three options
        if (values[middle] == value)
        {
            return true;
        }
        else if (values[middle] < value)
        {
            lower = middle + 1;
        }
        else if (values[middle] > value)
        {
            upper = middle - 1;
        }
    }
            
    return false;
}

/**
 * Sorts array of n values via Bubblesort.
 */
void sort(int values[], int n)
{
    // cycle through array
    for (int k = 0; k < n - 1; k++)
    {
        // optimize; check if there are no swaps
        int swaps = 0;

        //iterate through the array, leaving out the previously sorted section
        for (int i = 0; i < n - 1 - k; i++)
        {
            // check if values[n] and values[n + 1] are in order
            if (values[i] > values[i+1])
            {
                //swap
                int temp = values[i+1];
                values[i+1] = values[n];
                values[i] = temp;
                swaps++;
            }
        }
        if (!swaps)
            break;
    }
    return;
}
