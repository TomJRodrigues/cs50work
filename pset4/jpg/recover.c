/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Tom Rodrigues tomjrodrigues@gmail.com
 *
 * 22-6-2015
 *
 * Recovers JPEGs from a forensic image.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int main(int argc, char* argv[])
{
    // open card.raw in read mode
    FILE* card = fopen("card.raw", "r");
    if (card == NULL)
    {
        fprintf(stderr, "Could not open file");
        fclose(card);
        return 2;
    }
    
    // declarations
    uint8_t buffer[512];       // 512 bytes alloc'd for buffer
    char filename[8];           // 8 bytes alloc'd for filename
    uint8_t checkjpg1[4] = {0xff, 0xd8, 0xff, 0xe0};
	uint8_t checkjpg2[4] = {0xff, 0xd8, 0xff, 0xe1};
	uint8_t check[4];
    FILE* outfile = NULL;       // initialize outfile
    int num_jpgs = 0;           // initialize num_jpgs
    int open = 0;               // set outfile open counter
    
    fread(buffer, 512, 1, card);
    
    while (fread(buffer, 512, 1, card) != 0)
    {
        // Add first four bytes into the check buffer
		for(int i = 0; i < 4; i++)
		{
			check[i] = buffer[i];
		}
		
        if ((memcmp(checkjpg1, check, 4) == 0) || (memcmp(checkjpg2, check, sizeof(check)) == 0))
        {
            sprintf(filename, "%03d.jpg", num_jpgs);
           
            if (open == 0)
            {
                outfile = fopen(filename, "w");
                fwrite(buffer, sizeof(buffer), 1, outfile);
                open = 1;
            }
            if (open == 1)
            {
                fclose(outfile);
                outfile = fopen(filename, "w");
                fwrite(buffer, sizeof(buffer), 1, outfile);
                num_jpgs++;
            } 
        }
        else 
        {
            if (open == 1)
            {
                //write to the current jpg
                fwrite(buffer, sizeof(buffer), 1, outfile);
            }
        }
    }
    //close and tidy TODO free memory?
    if (outfile)
        fclose(outfile);
        
    fclose(card);
 return 0;   
}
