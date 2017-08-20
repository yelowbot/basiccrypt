#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;

int byte = 0;
#define OFFSET sizeof(unsigned int) * 8
#define SEIVE_SZ 1000
unsigned int primes[SEIVE_SZ] = { 1 };
unsigned int primes_cnt = 0;

void seive(void)
{
		unsigned int seive[SEIVE_SZ] = { 1 };
		seive[0] = seive[1] = 0;
		for (size_t i = 2; i*i < SEIVE_SZ; i++)
			if (seive[i] == 1)
				for (size_t j = i*i; j < SEIVE_SZ; j+=i)
					seive[j] = 0;
		
		int ind = 0;
		for (size_t i = 0; i < SEIVE_SZ; i++)
				if (seive[i] == 1)
						primes[ind++] = i;
		primes_cnt = ind;
}

void RSA_encrypt(FILE *fin, FILE *fout, int key)
{
		
		while (byte = fgetc(fin))
		{
				filled += table[byte].code_len;
				if (filled <= sizeof(unsigned int))
				{
						to_encr <<= table[byte].code_len;
						to_encr = to_encr | table[byte].code;
				}
				else
				{
						fwrite(&to_encr, sizeof(unsigned int), 1, fout);
						filled = to_encr = 0;
				}
		}
}

void RSA_decrypt(FILE *fin, FILE *fout, int key)
{
		unsigned int tab_size, from_byte, new_ch, mask;
		fread(&tab_size, sizeof(unsigned int), 1, fin);

		vector<tabl_inst> tabl2;
		char chrtr;
		int ch_code, ch_codelen, max_ind = 0;
		for (size_t i = 0; i < tab_size; i++)
		{
				fread(&from_byte, sizeof(unsigned int), 1, fin);
				ch_code = from_byte;
				fread(&from_byte, sizeof(unsigned int), 1, fin);
				ch_codelen = from_byte & (~0xFF);
				chrtr = from_byte >> sizeof(char) * 8;
				tabl_inst newtabins(ch_code, ch_codelen, chrtr);
				tabl2.push_back(newtabins);

				if (ch_code > max_ind)
						max_ind = ch_code;
		}
		tabl_inst ins;
		vector<tabl_inst> tabl3; tabl3.resize(max_ind);

		for (auto i : tabl3) i = ins;
		for (auto i : tabl2) tabl3[i.code] = i;
		//

		int bytes = 0;
		unsigned char buf[100] = { 0 };


		while (fread(&from_byte, sizeof(unsigned int), 1, fin))
		{
				new_ch = 0;
				mask = 1 << OFFSET;
				for (int i = 0; i < sizeof(unsigned int) * 8; i++)
				{
						new_ch |= (from_byte & mask) >> OFFSET;
						if (tabl3[new_ch].code != -1)
						{
								fwrite(&tabl3[new_ch].ch, sizeof(char), 1, fout);
								break;
						}
				}
				fwrite(buf, sizeof(unsigned char), bytes, fout);
				memset(buf, 0, sizeof(buf));
		}
}