#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include"HuffmanTree.h"

using namespace std;

typedef long long LongType;
struct CharInfo
{
	char _ch;//�ַ�
	LongType _count;//�ַ����ֵĴ���
	string _code;// h

	CharInfo(LongType count = 0)
		:_count(count)
		, _ch(0)
	{}

	bool operator!=(const CharInfo& info)const
	{
		return _count != info._count;
	}

	CharInfo operator+ (const CharInfo& info)
	{
		return _count + info._count;
	}

	bool operator<(const CharInfo& info)const
	{
		return _count < info._count;
	}
};

struct CountInfo
{
	char _ch;
	LongType _count;
};
class FileCompress
{
public:
	FileCompress()
	{
		for (size_t i = 0; i < 256; ++i)
		{
			_infos[i]._ch = i;
		}
	}
	void Compress(const char* filename)
	{
		assert(filename);

		//ͳ���ַ����ֵĴ���
		FILE* fout = fopen(filename, "r");
		assert(fout);

		char ch = fgetc(fout);
		while (ch != EOF)
		{
			_infos[ch]._count++;
			ch = fgetc(fout);
		}
		//����HuffmanTree
		CharInfo invalid;
		invalid._count = 0;
		HuffmanTree<CharInfo> tree (_infos, 256, invalid);

		//����Huffman code
		_GetHuffmanCode(tree.GetRoot());

		//ѹ��
		string CompressFile = filename;
		CompressFile += ".huffman";
		FILE* fin = fopen(CompressFile.c_str(), "w");//c_str() ��string ת����const char * 
		assert(fin);

		//������Ϣ(�ӷ����ֵĴ���->�ؽ�HuffmanTree
	

		fseek(fout, 0, SEEK_SET);// ��λ���ļ�ͷ
		ch = getc(fout);
		char value = 0; 
		int pos = 0;
		while (ch != EOF)
		{
			string& code = _infos[ch]._code;
			for (size_t i = 0; i < code.size(); ++i)
			{
				value <<= 1;
				++pos;
				if (code[i] == '1')
					value |= 1;
				if (pos == 8)
				{
					fputc(value, fin);
					value = 0;
					pos = 0;
				}
			}
			ch = fgetc(fout);
		}
		if (pos)
		{
			value <<= (8 - pos);
			fputc(value, fin);
		}
		fclose(fin);
		fclose(fout);
	}

	//��ѹ
	void Uncompress(const char* filename)
	{
		//Input.txt.huffman->Input.txt
		assert(filename);
		string UncompressFile = filename;
		size_t index = UncompressFile.rfind('.');
		assert(index != string::npos);
		UncompressFile = UncompressFile.substr(0, index);
		//��ԭ�ļ�
		FILE* fin = fopen(UncompressFile.c_str(), "w");
		assert(fin);

		FILE* fout = fopen(filename, "r");
		assert(fout);
		//�ؽ�HuffmanTree
		CharInfo invalid;
		invalid._count = 0;
		HuffmanTree<CharInfo> tree(_infos, 256, invalid);
		HuffmanTreeNode<CharInfo>* root = tree.GetRoot();
		HuffmanTreeNode<CharInfo>* cur = root;
		char value = fgetc(fout);
		LongType count = root->_w._count;

		int pos = 7;
		int test = 1;

		while (value != EOF)
		{
			while (pos >= 0)
			{
				if (value && (test << pos))
					cur->_right;
				else
					cur->_left;
				--pos;
				if (cur->_left == NULL && cur->_right == NULL)
				{
					fputc(cur->_w._ch, fin);
				}
				--pos;
			}
			value = fgetc(fout);
		}
		fclose(fout);
		fclose(fin);
	}
protected:
	void _GetHuffmanCode(HuffmanTreeNode < CharInfo>* root)
	{
		if (root == NULL)
			return;

		if (root->_left == NULL && root->_right == NULL)// �ҵ�Ҷ�ӽ��
		{
			HuffmanTreeNode<CharInfo>* cur;
			HuffmanTreeNode<CharInfo>* parent;
			string& code = _infos[root->_w._ch]._code;
			cur = root;
			parent = cur->_parent;
			
			//��Ҷ�ӽ�㵽���ڵ�
			while (parent)
			{
				if (cur == parent->_left)
					code += '0';
				else
					code += '1';
				cur = parent;
				parent = cur->_parent;
			}
			reverse(code.begin(), code.end());// �ѱ���ת�ã�
		}
		_GetHuffmanCode(root->_left);
		_GetHuffmanCode(root->_right);
	}
protected:
	CharInfo _infos[256]; //�����ַ�����Ϣ��
};