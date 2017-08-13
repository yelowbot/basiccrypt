#include <stdio.h>
#include <string.h>

void xor_encrypt(FILE *fin, FILE *fout, int key)
{
		int bytes = 0;
		unsigned char buf[100] = { 0 };

		while (bytes = fread(buf, sizeof(unsigned char), 100, fin))
		{
				for (size_t i = 0; i < bytes; i++)
						buf[i] ^= key;
				fwrite(buf, sizeof(unsigned char), bytes, fout);
				memset(buf, 0, sizeof(buf));
		}
}

void xor_decrypt(FILE *fin, FILE *fout, int key)
{
		int bytes = 0;
		unsigned char buf[100] = { 0 };

		while (bytes = fread(buf, sizeof(unsigned char), 100, fin))
		{
				for (size_t i = 0; i < bytes; i++)
						buf[i] ^= key;
				fwrite(buf, sizeof(unsigned char), bytes, fout);
				memset(buf, 0, sizeof(buf));
		}
}