#pragma once
#include<iostream>
#include<assert.h>
#include<string>
#include<algorithm>//�㷨
#include"Huffman.h"

typedef unsigned short LongType;//����ͳ���ַ����ֵĸ������ֽ���ռԽС��ѹ��Ч��Խ��
struct CharInfo//ÿ�����ݽṹ(��Ϊ����������Ȩֵ)
{
	unsigned char _ch;//�ַ������ں����������ַ�������ɣ������������ܴ��ڸ�ֵ(��Ϊ�±�ʱ�����)�����Դ˴�ʹ���޷�������
	LongType _count;//�ַ����ֵĴ���
	string _code;//�Ƚ��ַ��������ַ�����ʽ�洢

	//��������Huffman�в�֧�ֵĲ���
	//���ڶѵ�����ΪCharInfo���ͣ����Զ��еıȽϷ���(arr[i] != invidul)����ʹ�ã����Ͳ�ƥ��
	//���رȽϷ���
	bool operator!=(const CharInfo& info)const
	{
		return _count != info._count;
	}
	//ͬ��left->_w + right->_w�������Ҳ��֧�֣�����д
	CharInfo operator+(const CharInfo& info)const
	{
		CharInfo ret;
		ret._count = info._count + _count;
		return ret;
	}
	//ͬ��left->_w > right->_w���Ƚ�Ҳ��֧�֣�Ӧʹ��CharInfo�����е�_count�Ƚ�
	bool operator>(const CharInfo& info)const
	{
		return _count > info._count;
	}
};
//Ϊ��������ļ�ѹ�������ȥ�˽�һ��unicode�ַ�����
class FileCompress
{
	typedef HuffmanNode<CharInfo> Node;
public:
	//ͨ��λ��ӳ��ķ���ͳ�ƴ���
	FileCompress()//��ʼ��
	{
		size_t i = 0;
		for(i = 0;i < 256; i++)//��ʼ���ַ����鼯
		{
			_info[i]._ch = i;//��ʼ���ַ�����(����)
			_info[i]._count = 0;//��ʼ���ַ�����
		}
	}

	//�����ڲ��࣬�������Զ�����д��ѹ���ļ�
	struct _Huffmaninfo
	{
		unsigned char _ch;//���ں����������ַ�������ɣ������������ܴ��ڸ�ֵ(��Ϊ�±�ʱ�����)�����Դ˴�ʹ���޷�������
		LongType _count;
	};

	void Compress(const char* filename)//�ļ�ѹ����ע��filename���������ļ����������ļ���·��(Ĭ�Ϲ����ļ�·��)
	{
		assert(filename);//���ԣ���Ϊ��
		FILE* fout = fopen(filename,"r");//�Զ��ķ�ʽ���ļ�
		//1��ͳ���ַ�����
		char ch = fgetc(fout);//��ȡ�ļ��е�һ���ַ�
		int c = 0;
		while(ch != EOF)
		{
			c++;
			_info[(unsigned char)ch]._count++;//���ַ���Ӧ��������Ϊ��Ӧ���±�
			ch = fgetc(fout);//��ȡ�¸��ַ�
		}
		cout <<"ԭ�ļ��ַ�������" << c << endl;
		//2��������
		CharInfo invilid;
		invilid._count = 0;//_count=0Ϊ�Ƿ�ֵ�������
		Huffman<CharInfo> hftree;//ʹ�ü�ֵ�Թ����������ľ���ʵ����ʹ�ü�ֵ���еĴ���
		hftree.Huffmantree(_info,256,invilid);

		//3�����ɹ��������루ÿ���ַ��ı��룩
		//·�����뷽����1��������---�������ϱ���(���õݹ鷨����)
		//����Ҫ���������ߣ����Ա���ֱ����ǰ�ڵ�ĸ��׽ڵ㣬������ʹ��������������ʹ�ö�����
		//HuffmanCompress_code(hftree.Getroot());//ʹ��������
		//��ʹ�������������������봫��string���ͣ�string������β�ʵ������Ч�ʵ�
		//HuffmanCompress_code2(hftree.Getroot(),_info->_code);//ʹ������
		string code;
		HuffmanCompress_code2(hftree.Getroot(),code);//��ʹ������



		//4��ѹ��
		string conpressFile = filename;//��ȡԭ�ļ���
		conpressFile += ".txt";//����º�׺��
		FILE* fin = fopen(conpressFile.c_str(),"wb");//�����ļ�
		assert(fin);//�ж�

		//д������Ϣ(����ÿ���ַ��ļ�ֵ��д���ļ�)---����ѹ�����ѹ��������
		_Huffmaninfo info;
		for(size_t i = 0;i < 256;i++)//��ÿ���ַ����ֵĴ�����д��
		{
			if(_info[i]._count)//ֻд���ַ�������Ϊ0�ģ���ֻд�ļ��г��ֵ��ַ�
			{
				info._ch = _info[i]._ch;
				info._count = _info[i]._count;
				size_t size = fwrite(&info,sizeof(_Huffmaninfo),1,fin);//���ַ����Ӧ���ֵĴ���(��ֵ��)�Զ�����д��ѹ���ļ�
				assert(size = sizeof(_Huffmaninfo));//����д�������Ƿ���ȷ,������ƥ��
			}
		}
		//���⣺�������ѹ���ļ����������
		//��1���������ַ�������������ѹ���ļ��Ŀ�ͷ�����ݸ�������ѹ���ļ������(�������ڹ���Haffman��)
		//��2����Ƿ�����_Huffmaninfo������ͳ�ƽ�����,��ĳ���ݽ��б�����֡�(_Huffmaninfo����Ϊͳ�ƴ������ͣ�����ѹ���ļ���)
		info._count = 0;//��0���ͳ�ƽ���
		fwrite(&info,sizeof(_Huffmaninfo),1,fin);//�����д��ͳ�ƽ�����

		//����ѹ������
		//�������е��ַ�������������ԭ�ļ����ַ���ÿ���ַ���Ӧ�ı��룬����ÿ���ַ��ı���,����8��λ(һ���ֽ�)д�����ļ��У�ʵ��ѹ����
		char value = 0;
		int count = 0;//λ����
		int c1 = 0;
		fseek(fout,0,SEEK_SET);//���ص��ļ���ͷ
		ch = fgetc(fout);//��ȡ�ַ�
		
		while(ch != EOF)
		{
			c1++;
			//��ʼһ���ֽڵ�λĬ��ȫΪ0��������Ϊ0�����в�������Ϊ0�����л����㣩������ǰ����λ(��1λ)
			//ע������λԭ�򣺺�����һλ���ᵼ�����һ��λ(��8λ)����ʱ���������һ����λ���´�������Ӧ����λ������
			//ע������ָ�������λ�ƣ������Ƿ���
			string& code = _info[(unsigned char)ch]._code;//���ñ�����д����ֱ����code�������
			for(size_t i = 0;i < code.size(); i++)
			{
				value <<= 1;//��������λ
				if(code[i] == '1')
					value |= 1;//������
				else//Ϊ0 ������
					value |= 0;
			
				count++;
				if(count == 8)
				{
					fputc(value,fin);//��һ���ֽ�λд���ļ�
					value = 0;//��ʼ��
					count = 0;//��ʼ��
				}
			}
			ch = fgetc(fout);//��ȡ��һ���ַ�
		}
		cout << "ѹ��" << c1 << endl;
		if(count != 0)//��Ϊ0������count = 8,�������һ���ַ�����8λ�����⣬��00000 100����
		{
			value <<= (8-count);//����8-countλ����Ϊ100 00000
			fputc(value,fin);
		}
		fclose(fin);
		fclose(fout);
	}

	//ʹ��������
	void HuffmanCompress_code(Node* root)//����������
	{
		if(root == NULL)
			return ;
		if(root->_left == NULL && root->_right == NULL)//ԭ�ַ���Ȩֵ����Ҷ�ӽڵ���
		{
			//����code����
			//string code;
			string& code = _info[(unsigned char)root->_w._ch]._code ;//�����븳����Ӧ���ַ����˲����������Ż�,ֱ�ӶԶ�Ӧ���ַ�������
			Node* cur = root;
			Node* parent = cur->_parent;
			while(parent)//ѭ����ֵ�����ڵ�ĸ���Ϊ�գ���������
			{
				if(parent->_left == cur)
					code.push_back('0');//���ӱ�0
				else
					code.push_back('1');//�Һ��ӱ�1
				cur = parent;
				parent = cur->_parent;
			}
			//����ַ������ã���Ϊ����������
			reverse(code.begin(),code.end());//�����㷨
			//_info[root->_w._ch]._code = code;//����Ӧ���ַ���������(δ�Ż�)
			return ;
		}
		 HuffmanCompress_code(root->_left);//�ݹ����������
		 HuffmanCompress_code(root->_right);//����������
	}

	//ʹ����������---�������±������±��� == �ϱ��� + �����ֵ(��--0����--1)
	//����Ҫ��string���͵��βν���ʵ������Ч�ʵ�
	//void HuffmanCompress_code2(Node* root,string& code)//����������
	void HuffmanCompress_code2(Node* root,string code)//����������
	{
		if(root == NULL)
			return ;
		if(root->_left == NULL && root->_right == NULL)//ԭ�ַ���Ȩֵ����Ҷ�ӽڵ���
		{
			_info[(unsigned char)root->_w._ch]._code = code;//��ԭ�е��ַ� ��Ӧ�ı��뱣�� 
			return ;//�˳���ǰ�ݹ�
		}
		 HuffmanCompress_code2(root->_left,code+'0');//�ݹ����������,ͬʱ��ǰcode = code����0
		 HuffmanCompress_code2(root->_right,code+'1');//����������,ͬʱ��ǰcode = code����1
	}

	//��ѹ��������ѹ���ļ��еĶ��������кͶ�Ӧ�ַ��ı��룬ʵ�ֽ�������λ��ԭ���ַ���ͬʱ����ԭ�ļ��ַ��ĸ�������ǰ�˳�����������ӵ�λ
	void UnCompress(const char* filename)//�ļ���ѹ��
	{
		assert(filename);
		int c  =0;
		//1�������ѹ�����ļ���
		string uncomfile = filename;//��ѹ�ļ���
		size_t pos = uncomfile.rfind('.');//����.�ַ���λ��,δ�ҵ�����nops����ֵ��,ע��Ĭ�ϴӺ��ң�ȥ����׺����ԭ�ļ����������ԭ�ļ�����
		assert(pos != string::npos);//�����ҵ���
		uncomfile = uncomfile.substr(0,pos);//����ʼλ�û�ȡ�Ӵ����γɽ�ѹ�ļ���
		uncomfile += "2.png";//�ļ�β��Ӻ�׺��������ԭ�ļ���������ֹ��ԭ�ļ�����
		FILE* fin = fopen(uncomfile.c_str(),"w");//��д�ķ�ʽ�򿪽�ѹ�ļ�
		assert(fin);
		FILE* fout = fopen(filename,"rb");//��ȡѹ���ļ�
		assert(fout);

		//����ѹ���ļ���ÿ���ַ����ֵļ�ֵ��(�ļ�ѹ������֮ǰ)��ԭԭ�ַ����ݼ�(ѹ���ļ��д洢����ÿ����ֵ�ԵĶ����Ʊ���)��
		//����ݻ�ȡ�������ع���Huffman��
		_Huffmaninfo info;//�ַ����ݼ�
		while(1)
		{
			size_t size = fread(&info,sizeof(_Huffmaninfo),1,fout);//�����Ƿ���������ݣ��´δ��¸��ֽڵ�ַ��ʼ��ȡ
			assert(size = sizeof(_Huffmaninfo));//�����Ƿ��������,������ƥ��
			if(info._count > 0)//��Ϊ���
			{
				_info[(unsigned char)info._ch]._ch = info._ch;
				_info[(unsigned char)info._ch]._count = info._count;				
			}
			else//�������˳�
				break;
		}

		//2���ع�����----��Ϊ��ѹ�������Huffman����ȷ���ַ��ı��룬�Ӷ���0/1���н���ת���ɶ�Ӧ���ַ�(�У�11--b)
		CharInfo invilid;
		invilid._count = 0;//_count=0Ϊ�Ƿ�ֵ�������ַ�������ͳ���ַ��������������
		Huffman<CharInfo> hftree;
		hftree.Huffmantree(_info,256,invilid);

		//3����ѹ��
		//1����7λ��1000 0000�����������������㣬��Ϊ���λ���ݣ��������Ƶó�����(8λ)������
		Node* root = hftree.Getroot();//��ȡHuffman��������(������ʼ��ַ)
		LongType charCount = root->_w._count;//��ȡ���ڵ��count��С�����ļ��ַ����������ڵ��count���ӽڵ�count��ӵõ����ӽڵ�countΪ�ַ����ֵĸ���
		//FILE* fout = fopen(filename,"r");
		char value = fgetc(fout);//ʹ��fread��ȡ���´λ��Զ��Ӻ�����ֽڿ�ʼ��ȡ�����Բ�����ǰ���ͳ�ƶ���������ת�����ַ�
		Node* cur = root;
		//while(value != EOF)
		while(1)
		{
			if(feof(fout))//feof()�������ļ���β���ط�0
				break;
			for(int i = 7;i >= 0;i--)//��ȡ8λ�е�ÿλ����
			{
				if(value  & (1 << i))//λΪ1�����ұ���
					cur = cur->_right;
				else//λΪ0���������
					cur = cur->_left;
				if(cur->_left == NULL && cur->_right == NULL)
				{
					c++;
					fputc(cur->_w._ch,fin);//����Ҷ�ڵ㣬��Ϊĳ�ַ��ڵ㣬�����ַ�д���ļ�
					cur = root;//����λ�ã��Ӹ��ڵ���
					if(--charCount == 0)//�ַ���ѹ�ꣿ
						break;//��ѹ���˳������������ӵ�λ
				}
			}
			value = fgetc(fout);//ȡ�¸��ַ��Ƚ�
		}
		cout << "��ѹ" << c << endl;
		fclose(fin);
		fclose(fout);
	}

private:
	CharInfo _info[256];//�ַ������256��,�ļ��е��������ݿ������е�ĳЩ�ַ���ʾ
};

void FileCompress_test()//ѹ���ļ�
{
	FileCompress fc;
	fc.Compress("1.png");
 	//fc.UnCompress("input.txt.txt");

	//����1����ʱ�����ļ�������������⣿������
	//����ԭ��δ��ѹ�꣬���ı��� д���ļ���д�������ƶ�д����Щ�ַ����Ϊ���ɼ������Իᵱ���ļ���������
	//�������1����ʹ��EOF�ж��ļ�������ʹ�ú���(feof)�ж�
	//�������2����ʹ�ö����ƶ�д��

	//����2.�޷���ѹ���ͽ�ѹ���ֿ�(�ֳ���������ʹ��)���������˳�����ʱ�������٣���������Ϊͬһ������
	//���Խ�ѹ���Ķ��������ԭ�ļ���������Ϊͬһ���������Գ������ɽ�ԭ�ļ����ַ����ֵĴ���д��ѹ���ļ��У�
	//��ѹʱʹ��ѹ���ļ��ַ����ֵĴ������Ӷ�����ַ����ֵĴ�����ʵ�ֽ�ѹ��
	//����д��ѹ���ļ�������
	//����1�����������ַ���ʽд�룬���뽫����ת�����ַ����ͣ������鷳
	//����2���������Զ�������ʽ����д��
}

void FileUnCompress_test()//��ѹ��
{
	FileCompress fc;
 	fc.UnCompress("1.png.txt");
}

//�ܽ᣺
/*���⣺
1���ļ��ܷ���ѹ����ԽѹԽС��Ϊʲô��
2��Huffmanѹ������---zip 8M--6M(Huffman) 8(M)--1(M)zip
3���ļ���ѹ����
�⣺�ݹ�ѹ�����ļ��д򿪣����ļ�����ѹ��
4����ͨ�ı�����Ƶ����Ƶ��ͼƬѹ��
5����β���ѹ���ɹ���

*/
