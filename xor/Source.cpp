#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
    char *fname = argv[2], *param = argv [1];
    char cryptname[100] = { 0 };
    char key = argv[3][0];
    unsigned char buf[100] = { 0 };
    FILE *fin, *fout;

    strcpy(cryptname, fname);
    strcat(cryptname, ".xored");

    if (param[1] == 'c')
    {

        fin = fopen(cryptname, "rb");
        fout = fopen(fname, "wb");

        int bytes = 0;
        while (bytes = fread(buf, sizeof(unsigned char), 100, fin))
        {
            for (size_t i = 0; i < bytes; i++)
                buf[i] ^= key;
            fwrite(buf, sizeof(unsigned char), bytes, fout);
            memset(buf, 0, sizeof(buf));
        }
    }
    else
    {
        fin = fopen(fname, "rb");
        fout = fopen(cryptname, "wb");

        int bytes = 0;
        while (bytes = fread(buf, sizeof(unsigned char), 100, fin))
        {
            for (size_t i = 0; i < bytes; i++)
                buf[i] ^= key;
            fwrite(buf, sizeof(unsigned char), bytes, fout);
            memset(buf, 0, sizeof(buf));
        }
    }

    fclose(fin);
    fclose(fout);
        return 0;
}