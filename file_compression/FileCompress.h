#pragma once
#include<iostream>
#include<assert.h>
#include<string>
#include<algorithm>//算法
#include"Huffman.h"

typedef unsigned short LongType;//用于统计字符出现的个数，字节所占越小，压缩效率越高
struct CharInfo//每个数据结构(作为哈夫曼树的权值)
{
	unsigned char _ch;//字符，由于汉字由两个字符编码组成，所以其结果可能存在负值(做为下标时会出错)，所以此处使用无符号类型
	LongType _count;//字符出现的次数
	string _code;//先将字符编码以字符串形式存储

	//以下重载Huffman中不支持的操作
	//由于堆的类型为CharInfo类型，所以堆中的比较方法(arr[i] != invidul)不可使用，类型不匹配
	//重载比较方法
	bool operator!=(const CharInfo& info)const
	{
		return _count != info._count;
	}
	//同理（left->_w + right->_w），相加也不支持，需重写
	CharInfo operator+(const CharInfo& info)const
	{
		CharInfo ret;
		ret._count = info._count + _count;
		return ret;
	}
	//同理（left->_w > right->_w）比较也不支持，应使用CharInfo类型中的_count比较
	bool operator>(const CharInfo& info)const
	{
		return _count > info._count;
	}
};
//为更好理解文件压缩，最好去了解一下unicode字符编码
class FileCompress
{
	typedef HuffmanNode<CharInfo> Node;
public:
	//通过位置映射的方法统计次数
	FileCompress()//初始化
	{
		size_t i = 0;
		for(i = 0;i < 256; i++)//初始化字符数组集
		{
			_info[i]._ch = i;//初始化字符内容(数字)
			_info[i]._count = 0;//初始化字符个数
		}
	}

	//设置内部类，将次数以二进制写入压缩文件
	struct _Huffmaninfo
	{
		unsigned char _ch;//由于汉字由两个字符编码组成，所以其结果可能存在负值(做为下标时会出错)，所以此处使用无符号类型
		LongType _count;
	};

	void Compress(const char* filename)//文件压缩，注：filename不仅仅是文件名，还有文件的路径(默认工程文件路径)
	{
		assert(filename);//断言，不为空
		FILE* fout = fopen(filename,"r");//以读的方式打开文件
		//1、统计字符个数
		char ch = fgetc(fout);//获取文件中的一个字符
		int c = 0;
		while(ch != EOF)
		{
			c++;
			_info[(unsigned char)ch]._count++;//以字符对应的数字作为对应的下标
			ch = fgetc(fout);//获取下个字符
		}
		cout <<"原文件字符个数：" << c << endl;
		//2、构建树
		CharInfo invilid;
		invilid._count = 0;//_count=0为非法值，不入堆
		Huffman<CharInfo> hftree;//使用键值对构建树，树的具体实现是使用键值对中的次数
		hftree.Huffmantree(_info,256,invilid);

		//3、生成哈夫曼编码（每种字符的编码）
		//路径编码方法：1、遍历树---从下向上遍历(可用递归法遍历)
		//由于要倒者向上走，所以必须直到当前节点的父亲节点，所以需使用三叉链，不可使用二叉树
		//HuffmanCompress_code(hftree.Getroot());//使用三叉链
		//不使用三叉链，哈夫曼编码传入string类型，string会进行形参实例化，效率低
		//HuffmanCompress_code2(hftree.Getroot(),_info->_code);//使用引用
		string code;
		HuffmanCompress_code2(hftree.Getroot(),code);//不使用引用



		//4、压缩
		string conpressFile = filename;//获取原文件名
		conpressFile += ".txt";//添加新后缀名
		FILE* fin = fopen(conpressFile.c_str(),"wb");//打开新文件
		assert(fin);//判断

		//写配置信息(出现每种字符的键值对写入文件)---处理压缩与解压分离问题
		_Huffmaninfo info;
		for(size_t i = 0;i < 256;i++)//将每种字符出现的次数都写入
		{
			if(_info[i]._count)//只写入字符个数不为0的，即只写文件中出现的字符
			{
				info._ch = _info[i]._ch;
				info._count = _info[i]._count;
				size_t size = fwrite(&info,sizeof(_Huffmaninfo),1,fin);//将字符与对应出现的次数(键值对)以二进制写入压缩文件
				assert(size = sizeof(_Huffmaninfo));//断言写的数据是否正确,且类型匹配
			}
		}
		//问题：如何区分压缩文件，与次数？
		//解1：次数区分法：将次数放在压缩文件的开头，根据个数区别压缩文件与次数(次数用于构建Haffman树)
		//解2：标记法：用_Huffmaninfo类型在统计结束后,用某数据进行标记区分。(_Huffmaninfo类型为统计次数类型，放在压缩文件中)
		info._count = 0;//用0标记统计结束
		fwrite(&info,sizeof(_Huffmaninfo),1,fin);//将标记写在统计结束后

		//内容压缩处理
		//生成所有的字符编码链：根据原文件的字符和每个字符对应的编码，生成每个字符的编码,并以8个位(一个字节)写入新文件中（实现压缩）
		char value = 0;
		int count = 0;//位计数
		int c1 = 0;
		fseek(fout,0,SEEK_SET);//返回到文件开头
		ch = fgetc(fout);//读取字符
		
		while(ch != EOF)
		{
			c1++;
			//起始一个字节的位默认全为0，所以若为0不进行操作（不为0，进行或运算），运算前先移位(移1位)
			//注：先移位原因：后左移一位，会导致最后一个位(第8位)进入时，多进行了一次移位导致错误，所以应先移位后运算
			//注：左移指的是向高位移，而不是方向
			string& code = _info[(unsigned char)ch]._code;//引用便于书写，可直接用code代替后者
			for(size_t i = 0;i < code.size(); i++)
			{
				value <<= 1;//先左移移位
				if(code[i] == '1')
					value |= 1;//或运算
				else//为0 不操作
					value |= 0;
			
				count++;
				if(count == 8)
				{
					fputc(value,fin);//将一个字节位写入文件
					value = 0;//初始化
					count = 0;//初始化
				}
			}
			ch = fgetc(fout);//读取下一个字符
		}
		cout << "压缩" << c1 << endl;
		if(count != 0)//不为0，则不满count = 8,处理最后一个字符不满8位的问题，如00000 100问题
		{
			value <<= (8-count);//左移8-count位，变为100 00000
			fputc(value,fin);
		}
		fclose(fin);
		fclose(fout);
	}

	//使用三叉链
	void HuffmanCompress_code(Node* root)//哈夫曼编码
	{
		if(root == NULL)
			return ;
		if(root->_left == NULL && root->_right == NULL)//原字符的权值都在叶子节点上
		{
			//生成code编码
			//string code;
			string& code = _info[(unsigned char)root->_w._ch]._code ;//将编码赋给对应的字符（此操作进行了优化,直接对对应的字符操作）
			Node* cur = root;
			Node* parent = cur->_parent;
			while(parent)//循环编值，根节点的父亲为空，即遍历完
			{
				if(parent->_left == cur)
					code.push_back('0');//左孩子标0
				else
					code.push_back('1');//右孩子标1
				cur = parent;
				parent = cur->_parent;
			}
			//最后将字符串逆置，就为哈夫曼编码
			reverse(code.begin(),code.end());//逆置算法
			//_info[root->_w._ch]._code = code;//将对应的字符赋给编码(未优化)
			return ;
		}
		 HuffmanCompress_code(root->_left);//递归遍历左子树
		 HuffmanCompress_code(root->_right);//遍历右子树
	}

	//使不用三叉链---从上向下遍历，下编码 == 上编码 + 自身编值(左--0，右--1)
	//但需要对string类型的形参进行实例化，效率低
	//void HuffmanCompress_code2(Node* root,string& code)//哈夫曼编码
	void HuffmanCompress_code2(Node* root,string code)//哈夫曼编码
	{
		if(root == NULL)
			return ;
		if(root->_left == NULL && root->_right == NULL)//原字符的权值都在叶子节点上
		{
			_info[(unsigned char)root->_w._ch]._code = code;//将原有的字符 对应的编码保存 
			return ;//退出当前递归
		}
		 HuffmanCompress_code2(root->_left,code+'0');//递归遍历左子树,同时当前code = code连上0
		 HuffmanCompress_code2(root->_right,code+'1');//遍历右子树,同时当前code = code连上1
	}

	//解压缩：根据压缩文件中的二进制序列和对应字符的编码，实现将二进制位还原成字符，同时根据原文件字符的个数，提前退出，不处理添加的位
	void UnCompress(const char* filename)//文件解压缩
	{
		assert(filename);
		int c  =0;
		//1、处理解压缩的文件名
		string uncomfile = filename;//解压文件名
		size_t pos = uncomfile.rfind('.');//查找.字符的位置,未找到返回nops（数值）,注：默认从后找，去除后缀后与原文件重名，会对原文件操作
		assert(pos != string::npos);//断言找到？
		uncomfile = uncomfile.substr(0,pos);//从起始位置获取子串，形成解压文件名
		uncomfile += "2.png";//文件尾添加后缀，避免与原文件重名，防止对原文件操作
		FILE* fin = fopen(uncomfile.c_str(),"w");//以写的方式打开解压文件
		assert(fin);
		FILE* fout = fopen(filename,"rb");//读取压缩文件
		assert(fout);

		//根据压缩文件中每中字符出现的键值对(文件压缩内容之前)还原原字符数据集(压缩文件中存储的是每个键值对的二进制编码)，
		//后根据获取的数据重构建Huffman树
		_Huffmaninfo info;//字符数据集
		while(1)
		{
			size_t size = fread(&info,sizeof(_Huffmaninfo),1,fout);//返回是否读到的数据，下次从下个字节地址开始读取
			assert(size = sizeof(_Huffmaninfo));//断言是否读到数据,且类型匹配
			if(info._count > 0)//不为标记
			{
				_info[(unsigned char)info._ch]._ch = info._ch;
				_info[(unsigned char)info._ch]._count = info._count;				
			}
			else//到达标记退出
				break;
		}

		//2、重构建树----因为解压还需根据Huffman树来确定字符的编码，从而将0/1序列进行转化成对应的字符(列：11--b)
		CharInfo invilid;
		invilid._count = 0;//_count=0为非法值（不是字符，而是统计字符个数），不入堆
		Huffman<CharInfo> hftree;
		hftree.Huffmantree(_info,256,invilid);

		//3、解压缩
		//1左移7位得1000 0000，再与编码进行与运算，即为最高位数据，依次类推得出所有(8位)的数据
		Node* root = hftree.Getroot();//获取Huffman树得数据(树得起始地址)
		LongType charCount = root->_w._count;//获取根节点的count大小，即文件字符个数，父节点的count由子节点count相加得到，子节点count为字符出现的个数
		//FILE* fout = fopen(filename,"r");
		char value = fgetc(fout);//使用fread读取后，下次会自动从后面的字节开始读取，所以不担心前面的统计二进制数被转化成字符
		Node* cur = root;
		//while(value != EOF)
		while(1)
		{
			if(feof(fout))//feof()函数，文件结尾返回非0
				break;
			for(int i = 7;i >= 0;i--)//获取8位中的每位数据
			{
				if(value  & (1 << i))//位为1，向右遍历
					cur = cur->_right;
				else//位为0，向左遍历
					cur = cur->_left;
				if(cur->_left == NULL && cur->_right == NULL)
				{
					c++;
					fputc(cur->_w._ch,fin);//到达叶节点，即为某字符节点，将该字符写入文件
					cur = root;//重置位置，从根节点走
					if(--charCount == 0)//字符解压完？
						break;//解压完退出，不处理后添加的位
				}
			}
			value = fgetc(fout);//取下个字符比较
		}
		cout << "解压" << c << endl;
		fclose(fin);
		fclose(fout);
	}

private:
	CharInfo _info[256];//字符最多有256种,文件中的所有内容可用其中的某些字符表示
};

void FileCompress_test()//压缩文件
{
	FileCompress fc;
	fc.Compress("1.png");
 	//fc.UnCompress("input.txt.txt");

	//问题1，有时出现文件结果不完整问题？？？？
	//问题原因：未解压完，查文本读 写，文件读写，二进制读写，有些字符组合为不可见，所以会当成文件结束处理
	//解决方法1：不使用EOF判断文件结束，使用函数(feof)判断
	//解决方法2：需使用二进制读写，

	//问题2.无法将压缩和解压缩分开(分成两个函数使用)，由于在退出函数时对象被销毁，两个对象不为同一个对象，
	//所以解压缩的对象的树与原文件建的树不为同一个树，所以出错，但可将原文件的字符出现的次数写入压缩文件中，
	//解压时使用压缩文件字符出现的次数，从而获得字符出现的次数，实现解压缩
	//次数写入压缩文件方法：
	//方法1：将次数以字符形式写入，但须将类型转化成字符类型，操作麻烦
	//方法2：将次数以二进制形式读，写入
}

void FileUnCompress_test()//解压缩
{
	FileCompress fc;
 	fc.UnCompress("1.png.txt");
}

//总结：
/*问题：
1、文件能否多次压缩，越压越小？为什么？
2、Huffman压缩意义---zip 8M--6M(Huffman) 8(M)--1(M)zip
3、文件夹压缩？
解：递归压缩，文件夹打开，对文件进行压缩
4、普通文本、音频、视频、图片压缩
5、如何测试压缩成功？

*/
