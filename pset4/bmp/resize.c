/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Resizes a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember filenames
    int factor = atoi(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf, bf_r;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    bf_r = bf;

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi, bi_r;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    bi_r = bi;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // declare heightmultiplier
    int heightmultiplier = 0;
    
    // declare widthmultiplier
    int widthmultiplier= 0;

    // store header changes
    bi_r.biWidth = bi.biWidth * factor;
    bi_r.biHeight = bi.biHeight * factor;
    
    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding_r = (4 - (bi_r.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // store other header changes
    bi_r.biSizeImage = (bi_r.biWidth * sizeof(RGBTRIPLE) + padding_r) * abs(bi_r.biHeight);
    bf_r.bfSize = bf.bfSize - bi.biSizeImage + bi_r.biSizeImage;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf_r, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi_r, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    // duplicate each line according to height multiplier
    while(heightmultiplier < factor)
    {
        heightmultiplier++;
        
        // iterate over infile's scanlines
        for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
        {
            while(widthmultiplier < factor)
            
                widthmultiplier++;
                // iterate over pixels in scanline
                for (int j = 0; j < bi.biWidth; j++)
                {
                    // temporary storage
                    RGBTRIPLE triple;

                    // read RGB triple from infile
                    fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }

            // skip over padding, if any
            fseek(inptr, padding, SEEK_CUR);

            // then add it back (to demonstrate how)
            for (int k = 0; k < padding; k++)
            {
                fputc(0x00, outptr);
            }
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
