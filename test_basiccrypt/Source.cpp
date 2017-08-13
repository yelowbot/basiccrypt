#include <stdio.h>
#include <string.h>
#include <vector>
#include <iostream>

#define F_SIZE 1024

#include "xor.h"

using namespace std;

struct TestAlgs
{
		virtual void crypt(void) = 0;
		virtual void decrypt(void) = 0;

		void generate(void)
		{
				fin = fopen(fname, "wb");
				int buf = 0;
				for (size_t i = 0; i < F_SIZE; i++)
				{
						buf = rand();
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

struct TestXor : TestAlgs
{
		TestXor()
		{
				strcpy(fname, "Xor.txt");
				strcpy(cryptname, "Xor.txt.XOR");
				key = rand();
				generate();
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

struct TestHuffman : TestAlgs
{
		void crypt(void)
		{
				cout << "	crypt huffmann\n";
		}
		void decrypt(void)
		{
				cout << "	decrypt huffmann\n";
		}
};

struct TestShannonFano : TestAlgs
{
		TestShannonFano()
		{
				strcpy(fname, "ShannonFano.txt");
				strcpy(cryptname, "Xor.txt.SHANNONFANO");
				key = rand();
				generate();
		}
		void crypt(void)
		{
				cout << "	crypt shannon-fano\n";
		}
		void decrypt(void)
		{
				cout << "	decrypt shannon-fano\n";
		}
};

//void test_lz77()
//{
//
//}
//
//void test_lz78()
//{
//
//}
//
//void test_lzma()
//{
//
//}
//
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
//void test_xor()
//{
//
//}
//
////HASH
//void test_crc()
//{
//
//}
//
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
		vect.push_back(new TestXor());
		vect.push_back(new TestShannonFano());

		for (auto i : vect) i->test();
		////COMPRESS
		//test_huffman();
		//test_shannon_fano();
		//test_lz77();
		//test_lz78();
		//test_lzma();
		////CRYPTO
		//test_rsa();
		//test_des();
		//test_xor();
		////HASH
		//test_crc();
		//test_md5();
		//test_sha();

		return 0;
}