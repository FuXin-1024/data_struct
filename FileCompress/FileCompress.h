#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include"HuffmanTree.h"

using namespace std;

typedef long long LongType;
struct CharInfo
{
	unsigned char _ch;//字符
	LongType _count;//字符出现的次数
	string _code;// h

	CharInfo(LongType count = 0)
		:_count(count)
		, _ch(0)
		, _code("")
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
	unsigned char _ch;
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

		//统计字符出现的次数
		FILE* fout = fopen(filename, "rb");
		assert(fout);

		int ch = fgetc(fout);
		while (ch != EOF)
		{
			_infos[(unsigned char)ch]._count++;
			ch = fgetc(fout);
		}
		//构建HuffmanTree
		CharInfo invalid;
		invalid._count = 0;
		HuffmanTree<CharInfo> tree (_infos, 256, invalid);

		//生成Huffman code
		_GetHuffmanCode(tree.GetRoot());

		//压缩
		string CompressFile = filename;
		CompressFile += ".huffman";
		FILE* fin = fopen(CompressFile.c_str(), "wb");//c_str() 将string 转化成const char * 
		assert(fin);

		//配置信息(子符出现的次数->重建HuffmanTree
		CountInfo info;
		for (size_t i = 0; i < 256; i++)
		{
			if (_infos[i]._count)  //存储出现过的字符信息；
			{
				info._ch = _infos[i]._ch;
				info._count = _infos[i]._count;

				fwrite(&info, sizeof(info), 1, fin);
			}
		}
		//结尾的标记
		info._count = -1;
		fwrite(&info, sizeof(info), 1, fin);
		fseek(fout, 0, SEEK_SET);// 定位到文件头
		ch = fgetc(fout);
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

	//解压
	void Uncompress(const char* filename)
	{
		//Input.txt.huffman->Input.txt
		assert(filename);
		string UncompressFile = filename;
		size_t index = UncompressFile.rfind('.');
		assert(index != string::npos);

		UncompressFile = UncompressFile.substr(0, index);
		//还原文件
		FILE* fin = fopen(UncompressFile.c_str(), "wb");
		assert(fin);

		FILE* fout = fopen(filename, "rb");
		assert(fout);
		CharInfo invalue;
		invalue._count = 0;
		CountInfo info;
		while (1)
		{
			fread(&info, sizeof(CountInfo), 1, fout);
			if (info._count == -1)
				break;
			_infos[info._ch]._ch = info._ch;
			_infos[info._ch]._count = info._count;
		}
		HuffmanTree<CharInfo> tree(_infos, 256, invalue);

		//处理只有一个字符或者文本只有一个字符并且重复多次出现
		if (tree.GetSize() == 1)
		{
			char ch;
			int count = 0;
			for (int i = 0; i < 256; i++)
			{
				if (_infos[i] != invalue)
				{
					ch = _infos[i]._ch;
					count = _infos[i]._count;
				}
			}
			while (count > 0)
			{
				fputc(ch, fin);
				count--;
			}
			return;
		}

		HuffmanTreeNode<CharInfo>* root = tree.GetRoot();
		int pos = 7;
		int test = 1;
		char value = fgetc(fout);
		LongType  count = root->_w._count;
		HuffmanTreeNode<CharInfo>*  cur = root;
		while (value != EOF || count != 0)
		{
			while (pos >= 0)
			{
				if (value& (test << pos))

					cur = cur->_right;
				else
					cur = cur->_left;
				--pos;
				if (cur->_left == NULL&& cur->_right == NULL)
				{
					fputc(cur->_w._ch, fin);
					cur = root;
					count--;
					if (count == 0)
					{
						break;
					}
				}
			}
			pos = 7;
			value = fgetc(fout);
		}
		fclose(fin);
		fclose(fout);
	}
protected:
	void _GetHuffmanCode(HuffmanTreeNode < CharInfo>* root)
	{
		if (root == NULL)
			return;

		if (root->_left == NULL && root->_right == NULL)// 找到叶子结点
		{
			HuffmanTreeNode<CharInfo>* cur;
			HuffmanTreeNode<CharInfo>* parent;
			string& code = _infos[(unsigned)root->_w._ch]._code;
			cur = root;
			parent = cur->_parent;
			
			//从叶子结点到根节点
			while (parent)
			{
				if (cur == parent->_left)
					code += '0';
				else
					code += '1';
				cur = parent;
				parent = cur->_parent;
			}
			reverse(code.begin(), code.end());// 把编码转置；
		}
		_GetHuffmanCode(root->_left);
		_GetHuffmanCode(root->_right);
	}
protected:
	CharInfo _infos[256]; //所有字符的信息；
};
