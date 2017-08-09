#include <stdio.h>
#include <string.h>
#include <vector>
#include <iostream>

using namespace std;

struct TestAlgs
{
		virtual void crypt(void) = 0;
		virtual void decrypt(void) = 0;
		virtual bool result(void) = 0;

		bool test()
		{
				cout << "test alg\n";
				crypt();
				decrypt();
				return result();
		}
};

//COMPRESS

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
		
		bool result(void)
		{
				cout << "	huffmann ok\n";
				return true;
		}
};

struct TestShannonFano : TestAlgs
{
		void crypt(void)
		{
				cout << "	crypt shannon-fano\n";
		}

		void decrypt(void)
		{
				cout << "	decrypt shannon-fano\n";
		}

		bool result(void)
		{
				cout << "	shannon-fano ok\n";
				return true;
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
		vect.push_back(new TestHuffman());
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