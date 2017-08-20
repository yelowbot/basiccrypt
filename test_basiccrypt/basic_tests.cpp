#include <stdio.h>
#include <string.h>
#include <vector>
#include <iostream>
#include "xor.h"

#define F_SIZE 1024

using namespace std;

struct TestAlgs
{
		virtual void crypt(void) = 0;
		virtual void decrypt(void) = 0;

		void check(void)
		{
				fin = fopen(fname, "wb");
				int buf = 0;
				for (size_t i = 0; i < F_SIZE; i++)
				{
						buf = rand() << 2;
						fwrite(&buf, sizeof(int), 1, fin);
				}

				fclose(fin);
		}
		bool result(void)
		{
				return true;
		}
		bool test()
		{
				crypt();
				decrypt();
				return result();
		}

		char fname[100], cryptname[100], key;
		FILE *fin, *fout;
};

//COMPRESS
struct TestHuffman : TestAlgs
{
		TestHuffman()
		{
				strcpy(fname, "Huffman.txt");
				strcpy(cryptname, "Xor.txt.HUFFMAN");
				key = rand();
				check();
		}
		void crypt(void)
		{
				fin = fopen(fname, "rb");
				fout = fopen(cryptname, "wb");

				cout << fname << " encrypt\n";
				xor_encrypt(fin, fout, key);

				fclose(fin);
				fclose(fout);
		}
		void decrypt(void)
		{
				fin = fopen(cryptname, "rb");
				fout = fopen(fname, "wb");

				cout << cryptname << " decrypt\n";
				xor_decrypt(fin, fout, key);

				fclose(fin);
				fclose(fout);
		}
};
struct TestShannonFano : TestAlgs
{
		TestShannonFano()
		{
				strcpy(fname, "ShannonFano.txt");
				strcpy(cryptname, "Xor.txt.SHANNONFANO");
				key = rand();
				check();
		}
		void crypt(void)
		{
				fin = fopen(fname, "rb");
				fout = fopen(cryptname, "wb");

				cout << fname << " encrypt\n";
				xor_encrypt(fin, fout, key);

				fclose(fin);
				fclose(fout);
		}
		void decrypt(void)
		{
				fin = fopen(cryptname, "rb");
				fout = fopen(fname, "wb");

				cout << cryptname << " decrypt\n";
				xor_decrypt(fin, fout, key);

				fclose(fin);
				fclose(fout);
		}
};
struct TestLZ77 : TestAlgs
{
		TestLZ77()
		{
				strcpy(fname, "LZ77.txt");
				strcpy(cryptname, "LZ77.txt.LZ77");
				key = rand();
				check();
		}
		void crypt(void)
		{
				fin = fopen(fname, "rb");
				fout = fopen(cryptname, "wb");

				cout << fname << " encrypt\n";
				xor_encrypt(fin, fout, key);

				fclose(fin);
				fclose(fout);
		}
		void decrypt(void)
		{
				fin = fopen(cryptname, "rb");
				fout = fopen(fname, "wb");

				cout << cryptname << " decrypt\n";
				xor_decrypt(fin, fout, key);

				fclose(fin);
				fclose(fout);
		}
};
struct TestLZ78 : TestAlgs
{
		TestLZ78()
		{
				strcpy(fname, "LZ78.txt");
				strcpy(cryptname, "LZ78.txt.LZ78");
				key = rand();
				check();
		}
		void crypt(void)
		{
				fin = fopen(fname, "rb");
				fout = fopen(cryptname, "wb");

				cout << fname << " encrypt\n";
				xor_encrypt(fin, fout, key);

				fclose(fin);
				fclose(fout);
		}
		void decrypt(void)
		{
				fin = fopen(cryptname, "rb");
				fout = fopen(fname, "wb");

				cout << cryptname << " decrypt\n";
				xor_decrypt(fin, fout, key);

				fclose(fin);
				fclose(fout);
		}
};
struct TestLZMA : TestAlgs
{
		TestLZMA()
		{
				strcpy(fname, "LZMA.txt");
				strcpy(cryptname, "LZMA.txt.LZMA");
				key = rand();
				check();
		}
		void crypt(void)
		{
				fin = fopen(fname, "rb");
				fout = fopen(cryptname, "wb");

				cout << fname << " encrypt\n";
				xor_encrypt(fin, fout, key);

				fclose(fin);
				fclose(fout);
		}
		void decrypt(void)
		{
				fin = fopen(cryptname, "rb");
				fout = fopen(fname, "wb");

				cout << cryptname << " decrypt\n";
				xor_decrypt(fin, fout, key);

				fclose(fin);
				fclose(fout);
		}
};

////CRYPTO
//void test_rsa()
//{
//
//}
//
//void test_des()
//{
//
//}
//
struct TestXor : TestAlgs
{
		TestXor()
		{
				strcpy(fname, "Xor.txt");
				strcpy(cryptname, "Xor.txt.XOR");
				key = rand();
				check();
		}
		void crypt(void)
		{
				fin = fopen(fname, "rb");
				fout = fopen(cryptname, "wb");

				cout << fname << " encrypt\n";
				xor_encrypt(fin, fout, key);

				fclose(fin);
				fclose(fout);
		}
		void decrypt(void)
		{
				fin = fopen(cryptname, "rb");
				fout = fopen(fname, "wb");

				cout << cryptname << " decrypt\n";
				xor_decrypt(fin, fout, key);

				fclose(fin);
				fclose(fout);
		}
};

struct TestCrc : TestAlgs
{
		TestCrc()
		{
				strcpy(fname, "Crc.txt");
				strcpy(cryptname, "Crc.txt.CRC");
				key = rand();
				check();
		}
		void crypt(void)
		{
				fin = fopen(fname, "rb");
				fout = fopen(cryptname, "wb");

				cout << fname << " encrypt\n";
				xor_encrypt(fin, fout, key);

				fclose(fin);
				fclose(fout);
		}
		bool test()
		{
				crypt();
				return result();
		}
};

//void test_md5()
//{
//
//}
//
//void test_sha()
//{
//
//}

int main(void)
{
		vector<TestAlgs*>vect;
		
		//compress
		vect.push_back(new TestHuffman());
		vect.push_back(new TestShannonFano());
		
		//cryptors
		vect.push_back(new TestXor());

		for (auto i : vect) i->test();
		return 0;
}