#pragma once
#include<iostream>
#include"heap.h"
using namespace std;

template<class T>
struct HuffmanNode
{
	HuffmanNode<T> *_left;
	HuffmanNode<T> *_right;
	//文件操作添加成三叉链
	HuffmanNode<T> *_parent;

	T _w;//权值

	HuffmanNode(const T& w)
		:_w(w)
		,_left(NULL)
		,_right(NULL)
		,_parent(NULL)
	{}
};
//构建树----Huffman树的根节点为所有叶子节点权值之和
//前提：一组有序数据(从小到大)
//选取最小的两个数据作为左右孩子(左--小)，两个数据之和作为父节点，
//并将计算结果放回数组，以此循环直至将所有数组中的数据取至仅只有一个。(由于会放回，所以数组不会为空)
//由于将数据放回数组中，会导致数据无序，所以此处可将数据放在小堆中，小堆的上面即为最小的数据

//详解：1、将数据入小堆(每个数据开辟一个空间，作为一个节点，节点的地址入小堆)
//注：堆不可直接放入权值原因：生成的父节点与放回堆中的数据应为同一个数据(地址)，才能将节点链接起来，构成树，否则不能将节点进行链接，无法构树
//注意：堆中的调整是根据类型进行调整的，所以此处需重写一个内部类，重写一个比较的方法(取地址中的权值比较)，否则会直接默认使用地址进行比较(错误)
//2、取堆顶的数据作为左孩子，将堆顶删除，再取堆顶数据作为右孩子，将堆顶删除(总结：取两个节点作为左，右孩子，取出后删除堆顶)
//3、将取出的两个孩子的权值进行相加，作为父节点(生成父节点，开辟空间)
//4、链树：父节点的左指针指向左孩子，右指针指向右孩子
//5、将父节点入堆
//6、依次循环2~5，循环至堆中只有一个数据,(由于每次都会将父节点入堆，所以堆不会为空)
//7、返回堆顶，即树的根地址
template<class W>
class Huffman
{
	typedef HuffmanNode<W> Node;
public:
	Huffman()
		:_root(NULL)
	{}

	//Node* Huffmantree(W* arr,size_t n)//传入数组的权值a
	Node* Huffmantree(W* arr,size_t n,W& invidul)//传入数组的权值a,非法值invidul
	{
		Node* left = NULL;//左孩子
		Node* right = NULL;//右孩子
		Node* parent = NULL;//父节点
		//注：权值不是数据，所以不可直接将权值放在堆中
		//注意：堆中的调整是根据类型进行调整的，所以此处需重写一个内部类，重写一个比较的方法，否则会直接默认使用地址进行比较
		struct NodeCompare//内部类，比较方法
		{
			bool operator()(const Node* left,const Node* right)//重写比较方法
			{
				return left->_w > right->_w;//权值比较
			}
		};

		Heap<Node*,NodeCompare> min_heap;//定义一个小堆,比较方法为NodeCompare
		size_t i = 0;
		for(i = 0;i < n; i++)//循环将所有数据的节点地址入堆
		{
			if(arr[i] != invidul)//不为非法值(次数非0)---入堆
			min_heap.Puch(new Node(arr[i]));//为每个数据开辟一个空间，并初始化入堆（即每个数据为一个节点）
		}
		while(min_heap.Size() > 1)
		{
			left = min_heap.Top();//取堆顶作为左孩子
			min_heap.Pop();//删除堆顶(已取)
			right = min_heap.Top();//取当前堆顶,作右孩子
			min_heap.Pop();
			parent = new Node(left->_w + right->_w);//两个孩子产生一个父节点
			//链接左右孩子
			parent->_left = left;
			parent->_right = right;
			//文件操作添加
			left->_parent = parent;//左孩子保存他的父亲
			right->_parent = parent;//右孩子保存他的父亲

			min_heap.Puch(parent);//将结果放回堆中，作为一个权值
		}
		return _root = min_heap.Top();//返回堆顶，即树的起始地址
	}
	Node*print()
	{
		return print(_root);
	}
	Node* print(Node* root)
	{
		if(! root)
		{
			return NULL;
		}
		cout << root->_w << ' ';
	    print(root->_left);
		print(root->_right);
	}
	Node* Getroot()//提供私有数据接口，只可访问，不可修改
	{
		return _root;
	}
private:
	Node* _root;
};

void Huffman_test()
{
	int arr[] = {0,1,2,3,4,5,6,7,8,9};
	int invilid = -1;//非法值
	size_t sz = sizeof(arr)/sizeof(arr[0]);
	Huffman<int> h1;
	h1.Huffmantree(arr,sz,invilid);
	h1.print();
}

//文件压缩，
//1、统计字符出现的次数
//2、次数作为权值，构造哈夫曼树(Huffman)
//3、生成Huffman code(标记0/1（孩子:小(左)--0，大(右)--1）)
//4、压缩---生成哈夫曼编码
//5、解压缩---根据哈夫曼编码还原
//列：aaaabbbccd
//统计个数：a---4,b---3,c---2,d---1
//构造哈夫曼树，和标树数
//       10
//     /0   \1              编码：
//  a--4     6              a---0
//         /0  \1           b---11
//        3     b--3        c---101
//      /0 \1               d---100
//    d--1  c--2
//压缩编码方法：a---0;个数为4 所以4个0（0000）,其它依次类推
//压缩编码：00001111 11101101 10000000(位数不够补0)
//解码：以每个字符对应的编码特点进行解码，如a编码为0，所以每个比特位为0的为a,(注意将添加的比特位去除)
//0 0 0 0---aaaa 11 11 11---bbb 101 101---cc 100---c  0 0 0 0 0---aaaaa（添加位删除,或根据原文件字符个数读取，不读取添加的位）
//结果：压缩前占10个字节，压缩后占3个字节
//文件压缩的 哈夫曼树的 权值为CharInfo类型---次数
//路径：Huffman_code > 8 不能压小，哈夫曼编码短(出现次数多)的压缩效果好，> 8是出现次数少的(树低)
//文件压缩一定能压小吗？
//答：不一定 编码长度code.size() < 8 可以压缩，code.size() > 8 不能压缩(因为一个字符本身就占8个位)
//字符出现次数差值小的，编码效率低，差值大的效率好