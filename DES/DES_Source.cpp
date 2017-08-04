#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
    char *fname = argv[2], *param = argv[1];
    char cryptname[100] = { 0 };

    unsigned int key = 0xCA6B5EA4;
    //‭11001010011010110101111010100100‬

    unsigned char buf[8] = { 0 }, lpart[4] = { 0 }, rpart[4] = { 0 }, tpart[4] = { 0 };
    FILE *fin, *fout;

    strcpy(cryptname, fname);
    strcat(cryptname, ".DES");

    if (param[1] == 'c')
    {

        fin = fopen(fname, "rb");
        fout = fopen(cryptname, "wb");

        int bytes = 0;
        while (bytes = fread(buf, sizeof(unsigned char), 8, fin))
        {
            memcpy(lpart, buf, 4);
            memcpy(tpart, buf, 4);
            memcpy(rpart, buf + 4, 4);

            for (size_t i = 0; i < 16; i++) //16 step des
            {
                *((unsigned int*)lpart) ^= key;
                *((unsigned int*)lpart) ^= *((unsigned int*)rpart);
                memcpy(rpart, tpart, 4);
                memcpy(tpart, lpart, 4);
                key += 1;
            }
            
            memcpy(buf, lpart, 4);
            memcpy(buf + 4, rpart, 4);
            fwrite(buf, sizeof(unsigned char), 4, fout);
            memset(buf, 0, sizeof(buf));
        }
    }
    else
    {
        fin = fopen(cryptname, "rb");
        fout = fopen(fname, "wb");

        int bytes = 0;
        while (bytes = fread(buf, sizeof(unsigned char), 8, fin))
        {
            memcpy(lpart, buf, 4);
            memcpy(tpart, buf, 4);
            memcpy(rpart, buf + 4, 4);

            for (size_t i = 0; i < 16; i++) //16 step des
            {
                *((unsigned int*)lpart) ^= key;
                *((unsigned int*)lpart) ^= *((unsigned int*)rpart);
                memcpy(rpart, tpart, 4);
                memcpy(tpart, lpart, 4);
                key += 1;
            }

            memcpy(buf, lpart, 4);
            memcpy(buf + 4, rpart, 4);
            fwrite(buf, sizeof(unsigned char), 4, fout);
            memset(buf, 0, sizeof(buf));
        }
    }

    fclose(fin);
    fclose(fout);
    return 0;
}