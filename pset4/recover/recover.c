// recover jpeg files

#include <stdio.h>
#include <stdlib.h>



int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: recover raw file \n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 2;
    }
    unsigned char buffer[512];

    int jpegCount = -1;
    FILE *img;
    while(fread(buffer,512,1,file)== 1)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (jpegCount >= 0 )
            {
                fclose(img);
            }
            jpegCount++;
            char fileName[8];
            sprintf(fileName, "%03d.jpg", jpegCount);
            img = fopen(fileName, "w");
        }
        if (jpegCount >= 0 )
        {
            fwrite(buffer,512,1,img);
        }

    }



    return 0;
}