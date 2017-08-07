#include <stdio.h>
#include <string.h>

unsigned int crc16_reg = 0xFFFF, crc16_poly = 0x8d95, bit = 0;

void crc16_gen_table(void)
{
}

void crc16(unsigned int user_data)
{
    //CRC   cycle
    for (size_t i = 0; i < 16; i++)
    {
        bit = ((user_data & 0xFFFF) >> 15);
        crc16_reg = ((crc16_reg << 1) & 0xFFFF) | bit;
        user_data << 1;

        if (bit)
            crc16_reg ^= crc16_poly;
    }
}

int main(int argc, char** argv)
{
    char *fname = argv[2], *param = argv[1];
    char cryptname[100] = { 0 };

    unsigned char buf[8] = { 0 }, lpart[4] = { 0 }, rpart[4] = { 0 }, tpart[4] = { 0 };
    FILE *fin, *fout;

    strcpy(cryptname, fname);
    strcat(cryptname, ".crc");

    fin = fopen(fname, "rb");
    fout = fopen(cryptname, "wb");

    int bytes = 0;
    while (bytes = fread(buf, sizeof(unsigned char), 16, fin))
        crc16(*((unsigned int*)buf));

    fclose(fin);
    fclose(fout);
    return 0;
}