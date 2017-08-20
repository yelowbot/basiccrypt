#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;

int byte = 0;
#define OFFSET sizeof(unsigned int) * 8

struct node
{
		pair<char, int > val;
		struct node *left, *right;
};
vector<node> dictionary;

struct tabl_inst
{
		tabl_inst() : code(-1), code_len(-1), ch(-1){}
		tabl_inst(int co, int col, char c) : code(co), code_len(col), ch(c){}
		int code, code_len;
		char ch;
};
vector<tabl_inst> table;

bool isEqual(struct node & element)
{
		return element.val.first == byte;
}

bool compair(struct node nodeA, struct node nodeB)
{
		return nodeA.val.second < nodeB.val.second;
}

void make_table(node root, int position, int upper_bit)
{
		static int code;
		int ind = 0;
		if (root.left == NULL)
		{
				ind = root.val.first;
				table[ind].code = code || (upper_bit << position);
				table[ind].code_len = position;
				table[ind].ch = root.val.first;
		}
		make_table(*root.left, position + 1, 0);
		make_table(*root.right, position + 1, 1);
}

void huffman_encrypt(FILE *fin, FILE *fout, int key)
{
		unsigned char buf[100] = { 0 };
		char *ptr = 0;
		table.resize(300);
		node *newnode;
		node *lnode, *rnode;
		while (byte = fgetc(fin))
		{
				auto it = find_if(dictionary.begin(), dictionary.end(), isEqual);
				if (it != dictionary.end())
						it->val.second++;
				else
				{
						newnode = new(node);
						newnode->val = make_pair(byte, 1);
						newnode->left = newnode->right = NULL;
						dictionary.push_back(*newnode);
				}
		}
		sort(dictionary.begin(), dictionary.end(), compair);

		//make tree leafs

		while (dictionary.size() != 1)
		{
				lnode = &dictionary.back(); dictionary.pop_back();
				rnode = &dictionary.back(); dictionary.pop_back();

				newnode = new(node);
				newnode->left = lnode;
				newnode->right = rnode;
				dictionary.push_back(*newnode);

				sort(dictionary.begin(), dictionary.end(), compair);
		}

		make_table(dictionary[0], 0, 0);

		//write table into file
		unsigned int to_encr = 0, filled = 0;

		to_encr = table.size();
		fwrite(&to_encr, sizeof(unsigned int), 1, fout);
		for (auto i : table)
		{
				to_encr = 0; to_encr |= i.code;
				fwrite(&to_encr, sizeof(unsigned int), 1, fout);
				to_encr = 0; to_encr |= i.ch;
				to_encr = to_encr << sizeof(char) * 8;
				to_encr |= i.code_len;
				fwrite(&to_encr, sizeof(unsigned int), 1, fout);
		}

		///////
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

void huffman_decrypt(FILE *fin, FILE *fout, int key)
{
		unsigned int tab_size, from_byte, new_ch, mask;
		fread(&tab_size, sizeof(unsigned int), 1, fin);
		
		vector<tabl_inst> tabl2;
		char chrtr;
		int ch_code, ch_codelen, max_ind=0;
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