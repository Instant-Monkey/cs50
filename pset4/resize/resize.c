// Resize a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: resize nFactor infile outfile\n");
        return 1;
    }

    // remember filenames
    int n = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    if (n < 1 || n > 100) {
        fprintf(stderr, "use a number between 1 and 100\n");
        return 1;
    }
    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    BITMAPFILEHEADER bfRes = bf;


    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    BITMAPINFOHEADER biRes = bi;


    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    int newBiWidth = bi.biWidth * n ;
    int newBiHeight = bi.biHeight * n ;

        // determine padding for scanlines
    int oldPadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int newPadding = (4 - (newBiWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    int newBiSizeImage = ((sizeof(RGBTRIPLE) * newBiWidth) + newPadding) * abs(newBiHeight);
    int newBfSize = newBiSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    biRes.biWidth = newBiWidth ;
    biRes.biHeight = newBiHeight ;
    biRes.biSizeImage = newBiSizeImage ;
    bfRes.bfSize = newBfSize;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bfRes, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&biRes, sizeof(BITMAPINFOHEADER), 1, outptr);


    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // we do the line n times to expend vertically
        for (int nv = 0 ; nv < n ; nv++)
        {
              // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile n times
                for (int nh = 0; nh < n; nh++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // add pading
            for (int k = 0; k < newPadding; k++)
            {
                fputc(0x00, outptr);
            }


            // if we still have vertically expand we set the cursor back to the current line
            if (nv != (n - 1))
            {
                int offset = sizeof(RGBTRIPLE) * (bi.biWidth);
                offset = offset * -1 ;
                fseek(inptr, offset , SEEK_CUR);
            } else
            {
                // skip over padding, if any
                fseek(inptr, oldPadding, SEEK_CUR);
            }
        }

    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
