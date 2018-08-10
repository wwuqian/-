#pragma once
#ifndef __HUFFMAN_CODE_H__
#define __HUFFMAN_CODE_H__

#include<algorithm> //std::reverse
#include<string>

#include "HuffmanTree.h"

typedef unsigned long long LongType;
struct CharInfo
{
	unsigned char _ch;  //字符
	LongType _count;    //字符出现的次数
	string _code;       //huffman编码

	CharInfo(LongType count = 0)
		:_ch(0)
		,_count(count)
	{}

	CharInfo operator+(const CharInfo& info) const
	{
		CharInfo tmp;
		tmp._count = _count + info._count;
		return tmp;
	}

	bool operator!=(const CharInfo& info) const
	{
		return _count != info._count;
	}

	bool operator<(const CharInfo& info) const
	{
		return _count < info._count;
	}
};

//ostream& operator<<(ostream& os, CharInfo& info)
//{
//	os << info._ch << ":" <<info._count;
//	return os;
//}

class FileCompress
{
	typedef HuffmanTreeNode<CharInfo> Node;
public:
	FileCompress();
	//文件压缩
	void fileCompress(const char* filename);
	//解压缩
	void unfileCompress(const char* filename);

protected:
	//以递归的方式生成Huffman树
	void _GenerateHuffmanCode(Node* root,string code);
protected:
	CharInfo _info[256];
};

#endif  /*__HUFFMAN_CODE_H__*/
