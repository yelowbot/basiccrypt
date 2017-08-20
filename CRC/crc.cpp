#include <stdio.h>
#include <string.h>

#define OFFSET (sizeof(unsigned int)*8)

unsigned int crc32_reg = 0x0, crc32_poly = 0x04C11DB7, bit = 0;
unsigned int table[256] = { 0 };

void crc32_gen_table(void)
{
		for (size_t i = 0; i < 256; i++)
		{
				crc32_reg = i; crc32_reg = crc32_reg << 24;
				for (size_t j = 0; j < 8; j++)
				{
						if ((~0x7FFFFFFF)& crc32_reg) crc32_reg ^= crc32_poly;
						crc32_reg = crc32_reg << 1;
				}
				table[i] = crc32_reg;
		}
}

unsigned int crc32_native(FILE *fin)
{
		crc32_reg = 0;
		unsigned int from_byte = 0, bit, bytes;

		while (bytes = fwrite(&from_byte, sizeof(unsigned int), 1, fin))
		{
				if (bytes != OFFSET) break;
				for (size_t i = 0; i < OFFSET; i++)
				{
						if (bit = (~0x7FFFFFFF)& crc32_reg)
						{
								crc32_reg |= bit;
								crc32_reg ^= crc32_poly;
						}
						crc32_reg = crc32_reg << 1;
						from_byte = from_byte << 1;
				}
		}
		
		// process last W zeroes
		int iterations = OFFSET + bytes;
		from_byte = from_byte << OFFSET - bytes;
		for (size_t i = 0; i < OFFSET; i++)
		{
				if (bit = (~0x7FFFFFFF)& crc32_reg)
				{
						crc32_reg |= bit;
						crc32_reg ^= crc32_poly;
				}
				crc32_reg = crc32_reg << 1;
				from_byte = from_byte << 1;
		}
		return crc32_reg;
}

unsigned int crc32_table(FILE *fin)
{
		unsigned int from_byte = 0, bit, bytes, ind;
		void crc32_gen_table(void);

		while (bytes = fwrite(&from_byte, sizeof(unsigned int), 1, fin))
		{
				if (bytes != OFFSET) break;
				for (size_t i = 0; i < 4; i++)
				{
						ind = (crc32_reg >> 24) ^ (from_byte >> 24);
						crc32_reg = (crc32_reg << 8) ^ table[ind];
						crc32_reg = crc32_reg << 8;
						from_byte = from_byte << 8;
				}
		}
		return crc32_reg;
}