#define _CRT_SECURE_NO_WARNING 1
#include<stdio.h>  //feof
#include<cstddef>  //std::size_t
#include "FileCompress.h"

typedef HuffmanTreeNode<CharInfo> Node;
FileCompress::FileCompress()
{
	for(size_t i = 0;i < 256;++i)
	{
		_info[i]._ch = i;
		_info[i]._count = 0;
	}
}

//压缩
void FileCompress::fileCompress(const char* filename)
{
	assert(filename);
	FILE* fout = fopen(filename,"rb");
	assert(fout);
	//1.统计字符出现的次数
	char ch = fgetc(fout);
	while(!feof(fout))
	{
		++_info[(unsigned char)ch]._count;
		ch = fgetc(fout);
	}

	//2.构建huffman树
	CharInfo invalid;  //一层抽象，当遇见非法字符时，不构建huffman tree
	invalid._count = 0;
	HuffmanTree<CharInfo> tree(this->_info,sizeof(_info)/sizeof(_info[0]),invalid);

	//3.生成Huffman编码
	string code;
	_GenerateHuffmanCode(tree.GetRoot(),code);


	size_t _last; //用于记录文件名和后缀

	//4.打开要压缩的文件，删除原有后缀名,加入压缩后缀.huff
	string compressfile = filename;
	_last = compressfile.find_last_of('.');

	if(_last < compressfile.size())
		compressfile.erase(_last);

	compressfile += ".huff";
	FILE* fin = fopen(compressfile.c_str(),"wb");
	assert(fin);

	//5.写配置信息：将字符和出现次数按照（字符，次数）的形式，按行保存到配置文件中
	string configfile = filename;
	_last = configfile.find_last_of('.');

	if(_last < configfile.size())
		configfile.erase(_last);

	configfile += ".config";
	FILE* config = fopen(configfile.c_str(),"wb"); //二进制写的方式
	assert(config);

	string info;
	char count[20]; //以字符串的形式表示次数
	for(int i = 0;i < 256;i++)
	{
		info.clear();
		if(_info[i] != invalid)
		{
			info = _info[i]._ch;
			info += ':';
			//将10进制整型转换为字符串
			(string)itoa(_info[i]._count,count,10);

			info += count;
			info += '\n';
			fputs(info.c_str(),config);

		}
	}

	//6.将编码进行压缩，存入压缩文件中
	long long cnt = 0; //统计读取的字符个数，方便调试
	unsigned char value = 0;
	int pos = 0;
	fseek(fout,0,SEEK_SET); //把fout置到文件的开始
	ch = fgetc(fout);
	while(!feof(fout))
	{
		++cnt;
		string& code = _info[(unsigned char)ch]._code;
		for(size_t i = 0;i < code.size();++i)
		{
			value <<= 1;
			//简洁的写法：
			//value |= (code[i]-'0');

			//方便理解：
			if(code[i] == '0') //左子树
			{
				//value默认为0，当该位为0时，不需要操作。和0进行按位或
				value |= 0;
			}
			else if(code[i] == '1')
			{
				//当该位为1时，将value置为1。所以和1进行按位或
				value |= 1;
			}
			else
				assert(false);

			++pos;

			//value满8个位，就写入到压缩文件中，未满8个位就保存在value中
			//byte：8个位
			if(pos == 8)
			{
				fputc(value,fin);
				value = 0;
				pos = 0;
			}
		}
		ch = fgetc(fout); //读取下一个字符
	}
	if(pos != 0)  //说明最终未满8个位，没有写入压缩文件中
	{
		value <<= (8-pos); //将value写满8个位，左移，后面补0
		fputc(value,fin);  //将满8个位的value写入压缩文件中
	}

	cout << "压缩字符的个数为：" << cnt <<endl;
	fclose(fout);
	fclose(fin);
	fclose(config);

}


//解压缩:input.huff->input.unhuff(解压后的文件)
void FileCompress::unfileCompress(const char* filename)
{
	//读取配置文件中的内容
	string configfile = filename;
	//去后缀".huff"
	size_t _last = configfile.find_last_of('.');
	if(_last < configfile.size())
		configfile.erase(_last);

	//加后缀：".config"
	configfile += ".config";
	FILE* file = fopen(configfile.c_str(),"rb");
	assert(file);

	unsigned char ch = fgetc(file);
	char buff[20] = {0};
	while (!feof(file))
	{
		fgetc(file);//读取冒号
		fgets(buff, 20, file);
		this->_info[ch]._count = (LongType)atoi((buff));
		ch = fgetc(file);
	}

	

	//根据配置文件构建Huffman树
	CharInfo invalid(0);
	HuffmanTree<CharInfo> tree(_info,256,invalid);
	Node* root = tree.GetRoot();

	//根据压缩文件和重建的Huffman树进行解压缩
	string uncompress = filename;
	_last = uncompress.find_last_of('.');
	if(_last < uncompress.size())
		uncompress.erase(_last);

	uncompress += ".unhuff"; //解压后的文件后缀，区分input.txt
	FILE* fin = fopen(uncompress.c_str(),"wb");
	assert(fin);
	
	//读取压缩文件
	string compress = filename;
	_last = compress.find_last_of('.');
	if(_last < compress.size())
		compress.erase(_last);
	compress += ".huff";
	FILE* fout = fopen(compress.c_str(),"rb");
	assert(fout);

	//根据压缩文件的二进制编码解压文件
	Node* cur = root;
	int pos = 8;
	long long cnt = 0; //用来统计解压的字符数，方便调试
	ch = fgetc(fout);
	assert(ch);
	LongType count = cur->_weight._count; //用来统计原文件的字符数
	cout << "原文件字符个数为：" << count << endl;

	while(!feof(fout))
	{
		if(pos == 0)
		{
			pos = 8;
			ch = fgetc(fout);
		}
		--pos;
		if(ch & 1 << pos) //ch=1
			cur = cur->_right;
		else
			cur = cur->_left;
		if(cur->_left == NULL && cur->_right == NULL)
		{
			++cnt;
			fputc(cur->_weight._ch,fin);
			cur = root;

			//当所有的字符都解压完就，就break
			if(--count == 0)
				break;

		}
	}
	cout << "解压缩字符的个数为：" << cnt << endl;

	fclose(file);
	fclose(fin);
	fclose(fout);
}


//以递归的方式生成Huffman树
void FileCompress::_GenerateHuffmanCode(Node* root,string code)
{
	if(root == NULL)
		return;
	if(root->_left == NULL && root->_right == NULL)
	{
		_info[(unsigned char)root->_weight._ch]._code = code;
		return;
	}
	_GenerateHuffmanCode(root->_left,code+'0');
	_GenerateHuffmanCode(root->_right,code+'1');

}

///////////////////////////////////////
//////测试函数：测试readLine
///////////////////////////////////////
//void TestreadLine()
//{
//	string code = "";
//	FileCompress file;
//	//string path = "D:\\input.txt";
//	//
//	//FILE* str = fopen(path.c_str(),"rb");
//	//bool res = file.readLine(str,code);
//	//cout << res;
//	
//}

//////////////////////////////////////
///测试压缩
//////////////////////////////////////
void TestCompress()
{
	string filename = "./11.jpg";
	//cout << "压缩时间：";
	FileCompress fc;
	fc.fileCompress(filename.c_str());
}

////////////////////////////////////
///测试解压缩文件
////////////////////////////////////
void TestUnCompress()
{
	string filename = "./11.huff";
	FileCompress fc;
	cout << "解压缩开始！" <<endl;
	fc.unfileCompress(filename.c_str());
	cout << "解压缩完成！" << endl;
}


