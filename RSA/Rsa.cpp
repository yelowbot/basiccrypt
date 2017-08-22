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
int p, q, N, fN, e, d;

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

bool ÑoPrime_euclid(int a, int b)
{
		for (;;)
		{
				if (!(a %= b)) return b == 1;
				if (!(b %= a)) return a == 1;
		}
}

// C function for extended Euclidean Algorithm
int Extended_euclid(int a, int b, int *x, int *y)
{
		if (a == 0)
		{
				*x = 0, *y = 1;
				return b;
		}
		int x1, y1; // To store results of recursive call
		int gcd = Extended_euclid(b%a, a, &x1, &y1);

		*x = y1 - (b / a) * x1;
		*y = x1;
		return gcd;
}

// Function to find modulo inverse of a
int modInverse(int a, int m)
{
		int x, y;
		int g = Extended_euclid(a, m, &x, &y);
		if (g != 1)
				return -1;
		else
		{
				// m is added to handle negative x
				int res = (x%m + m) % m;
				return res;
		}
}

// Iterative Function to calculate (x^y)%p in O(log y)
int modulo_power(int x, unsigned int y, int p)
{
		int res = 1;
		x = x % p;
		while (y > 0)
		{
				// If y is odd, multiply x with result
				if (y & 1) res = (res*x) % p;
				// y must be even now
				y = y >> 1;
				x = (x*x) % p;
		}
		return res;
}

void RSA_init(void)
{
		while ((p = primes[rand() % primes_cnt]) == (q = primes[rand() % primes_cnt]));
		N = p*q;
		fN = (p - 1)*(q - 1);
		e = rand() % fN;
		while (!ÑoPrime_euclid(e, fN))
				e = rand() % fN;
		d = modInverse(e, N);
}
void RSA_encrypt(FILE *fin, FILE *fout)
{
		int from_byte = 0, crypt_byte;
		while (fread(&from_byte, sizeof(int), 1, fin))
		{
				crypt_byte = modulo_power(from_byte, e, N);
				fwrite(&crypt_byte, sizeof(char), 1, fout);
		}
}
void RSA_decrypt(FILE *fin, FILE *fout, int key)
{
		int from_byte = 0, decrypt_byte;
		while (fread(&from_byte, sizeof(int), 1, fin))
		{
				decrypt_byte = modulo_power(from_byte, d, N);
				fwrite(&decrypt_byte, sizeof(char), 1, fout);
		}
}