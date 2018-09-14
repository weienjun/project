#pragma once 
#include<iostream>
#include<vector>
#include<assert.h>
using namespace std;
//���---���и��ڵ�����ӽڵ�
//С��---���и��ڵ�С���ӽڵ�
//��Ӧ��---���ȼ�����---PreQueue
//С��---����---�º���(ͨ����������������ʵ��)
template<class T>
struct Less//С�ѱȽ��෽��
{
	bool operator()(const T& left,const T& right)const //���أ���
	{
		return left > right;
	}
};
template<class T>
struct Greater//��ѱȽ��෽��
{
	bool operator()(const T& left,const T& right)const //���أ���
	{
		return left < right;
	}
};
//CompareΪLess��ΪС��,����С����ȽϷ�����ΪGreater��Ϊ��ѣ����ô����ȽϷ���
template<class T,class Compare = Greater<T>>//��һ�����������ȽϷ�����ȱʡ����Ĭ�ϴ�ѣ�
class Heap
{
public :
	Heap()//�޲ι���
	{}
	//����ת������
	Heap(T* arr,size_t size)//���ι���
	{
		size_t i = 0;
		_heap.reserve(size);//����
		for(i = 0;i < size; i++)
		{
			_heap.push_back(arr[i]);
		}
		//����
		for(int j = _heap.size()/2;j >= 0 ;j--)//��ѭ���Ƚϵ�ǰ��-1�Σ������ϵĲ��ٱȽϣ�
		//AdjustDown(j);//���µ���
		AdjustDown2(j);//���µ���

	}
	//��ѵ���
	//1.�ҵ����һ����Ҷ�ӽڵ㣨�����ڵ㣩a���������ϵ���(a--����һ�����׽ڵ�)
	//���ѣ������K������Ϊ���
	void AdjustDown(size_t K)//���µ���
	{
		size_t parent = K;
		size_t chiled = K*2+1;//����,K*2+2�Һ���
		while(chiled < _heap.size())
		{
			Max_change(parent,chiled);//��������
			parent++;
			chiled = parent*2+1;
		}
	}
	//����һ�����ݣ�β�壩�����ϵ�����ֻ���������ڵ������·��
	void Puch(T data)
	{
		size_t chiled ;
		size_t parent ;
		_heap.push_back(data);
		//���ϵ���
		chiled = _heap.size()-1;
		while(chiled)//��Ϊ���ڵ��±꣨0��
		{
			parent = (chiled-1)/2;
			Max_change(parent,chiled);//��������
			chiled = parent;//������Ϊ���ӽڵ�
		}
	}
	void AdjustDown2(size_t K)//���µ���
	{
		Compare com;//�ȽϷ�������
		size_t parent = K;
		size_t chiled = K*2+1;//����,K*2+2�Һ���
		while(chiled < _heap.size())//��Ϊ���ڵ��±꣨0��
		{
			if(chiled < _heap.size()-1 && com(_heap[chiled] , _heap[chiled+1]))//com���ö�Ӧ�ıȽϷ������е����غ���
			{
				chiled++;//��Ϊ�Һ���
			}
			//��������
			//if(chiled < _heap.size() && _heap[parent] < _heap[chiled])//�жϣ��Ƿ񽻻�
			if(chiled < _heap.size() && com(_heap[parent] , _heap[chiled]))//�жϣ��Ƿ񽻻�
			{
				swap(_heap[parent],_heap[chiled]);//����
				parent++;
			    chiled = parent*2+1;
			}
			else
				break;
		}
	}
	void Max_change(size_t parent,size_t chiled)//��������
	{
		Compare com;//�ȽϷ�������
		//if(chiled < _heap.size()-1 && _heap[chiled] < _heap[chiled+1])//ѡ����ĺ���,-1��Ϊ�˷�ֹ����Խ��
		if(chiled < _heap.size()-1 && com(_heap[chiled] , _heap[chiled+1]))//com���ö�Ӧ�ıȽϷ������е����غ���
		{
			chiled++;//��Ϊ�Һ���
		}
		//��������
		//if(chiled < _heap.size() && _heap[parent] < _heap[chiled])//�жϣ��Ƿ񽻻�
		if(chiled < _heap.size() && com(_heap[parent] , _heap[chiled]))//�жϣ��Ƿ񽻻�
		{
			swap(_heap[parent],_heap[chiled]);//����

		}
	}
	//ɾ��һ�����ڵ�(���ڵ�)
	//�Ƚ����ڵ������һ���ڵ㽻����ɾ�����һ���ڵ㣬�ڽ������µ���
	void Pop()
	{
		swap(_heap[0],_heap[_heap.size()-1]);//���ڵ������һ���ڵ㽻��
		_heap.pop_back();//βɾ
		AdjustDown(0);//���µ���
	}

	T& Top()
	{
		return _heap.front();
	}
	//�ж��Ƿ�Ϊ���,�������±��������һ���ڵ�ĸ��׽ڵ㣬���бȽ�
	bool Isheap()
	{
		Compare com;
		size_t i = 0;
		assert(!_heap.empty());
		for(i = 0;i <= _heap.size()-2/2;i++)
		{
			size_t left = i*2+1;
			size_t right = i*2+2;
			//if((right < _heap.size()&&_heap[i] < _heap[left])||//����ж�
			   //(right < _heap.size() && _heap[i] < _heap[right]))//������
			if((left < _heap.size()-1 && com(_heap[i] , _heap[left])) || //����ж�
			   (right < _heap.size()-1 && com(_heap[i] , _heap[right])))//�Ҳ��ж�
				return false;//�����в�����
			//�����������
		}//���������������
		return true;
	}
	size_t Size()
	{
		return _heap.size();
	}
	bool Empty()
	{
		return _heap.empty();
	}


	//�Լ�ʵ�ֵĴ���
	void Init_heap(T* arr,const size_t size)
	{
		size_t i = 0;
		for(i = 0; i < size; i++)
		{
			_heap.push_back(arr[i]);
		}
	}
	void Max_heap()
	{
		size_t i = 0;
		size_t j = 0;
		while(j++ < _heap.size())
		{
			i = 0;
			while(i < _heap.size())
			{
				if(i*2+1 < _heap.size() && _heap[i] < _heap[i*2+1])
				{
					T tmp = _heap[i];
					_heap[i] = _heap[i*2+1];
					_heap[i*2+1] = tmp;
				}
				if(i*2+2 < _heap.size() && _heap[i] < _heap[i*2+2])
				{
					T tmp = _heap[i];
					_heap[i] = _heap[i*2+2];
					_heap[i*2+2] = tmp;
				}
				i++;
			}
		}
	}

	void Min_heap()
	{
		size_t i = 0;
		size_t j = 0;
		while(j++ < _heap.size())
		{
			i = 0;
			while(i < _heap.size())
			{
				if(i*2+1 < _heap.size() && _heap[i] > _heap[i*2+1])
				{
					T tmp = _heap[i];
					_heap[i] = _heap[i*2+1];
					_heap[i*2+1] = tmp;
				}
				if(i*2+2 < _heap.size() && _heap[i] > _heap[i*2+2])
				{
					T tmp = _heap[i];
					_heap[i] = _heap[i*2+2];
					_heap[i*2+2] = tmp;
				}
				i++;
			}
		}
	}
	void heap_print()
	{
		size_t i = 0;
		while(i < _heap.size())
		{
			cout << _heap[i++] << ' ';
		}
		cout << endl;
	}
private :
	vector<T> _heap;
};

void Heap_test()
{
	int arr[] = {1,2,3,4,5,9,8,6,7};
	size_t sz = sizeof(arr)/sizeof(arr[0]);

	Heap<int> h1(arr,sz);//���
	cout << h1.Isheap() << endl;
	h1.heap_print();
	
	h1.Puch(10);
	h1.heap_print();

	h1.Pop();
	h1.heap_print();

	cout << endl;
	Heap<int,Less<int>> h2(arr,sz);//С��
	h2.heap_print();
	
	h2.Puch(10);
	h2.heap_print();

	h2.Pop();
	h2.heap_print();
	cout << h1.Isheap() << endl;

	/*
	Heap<int> h1;
	h1.Init_heap(arr,sz);
	h1.heap_print();

	h1.Max_heap();
	h1.heap_print();

	h1.Min_heap();
	h1.heap_print();
	*/
}


//���кܶ�����ݣ�������ǰK����---������⣨��K�����ݵĶѣ�
//����ⷨ:ʱ�临�Ӷ���СO(N*lgN)�����ҿռ�����޷�����
//�ѽ⣺��һ������K���ڵ�� С�ѣ�����ͷ�ڵ�Pop��(���е���)����ȡ��һ���������ͷ���бȽϣ����ڶ�ͷ���������(���е���)��
//����ѭ����������������һ�ζѣ����նѼ�Ϊ����ǰK�����ݣ�ʱ�临�Ӷȣ�O(N*lgK)
//ʵ��д������ʵ�ֶѣ�ֻʵ�ֽ��ѣ������µ���������дPop,��������ֻ��ʹ�ý�������swap�����Ѷ�(arr2[0])����
void Big_test()
{
	const size_t N = 10000;
	const size_t K = 10;
	int arr[N];//ԭ����
	int arr2[K];//��Ҫ������е�����
	int i = 0;
	for(i= 0;i < N;i++)//��������
	{
		arr[i] = rand()%N;
	}
	//����10������� > 10000,����� > 10000����ȷ
	arr[10] = N+100;
	arr[100] = N+200;
	arr[101] = N+150;
	arr[150] = N+160;
	arr[16] = N+170;
	arr[50] = N+160;
	arr[90] = N+600;
	arr[900] = N+650;
	arr[1000] = N+100;
	arr[500] = N+690;

	for(i = 0;i < K; i++)//ȡǰK������
	{
		arr2[i] = arr[i];
	}
	Heap<int,Less<int>> h1(arr2,K);//��С��(����е���)

	for(i = K - 1; i < N ;i++)//ѭ����ѱȽ�
	{
		if(h1.Top() < arr[i])
		{
			h1.Pop();//ɾ����ͷ
			h1.Puch(arr[i]);//�ȵ�ǰ��ͷ�����(��Ѻ����е���)
		}
	}
	h1.heap_print();//��ӡ���ն��е�Ԫ��
}

//������---ѡ������
//1������---��С�� 
//2��ѭ������С�����ݷ�����ǰ��ÿ�ν����ڵ��뵱ǰ���һ���ڵ㽻��������е�����ÿ�ֺ��ڿ������һ���ڵ�
//3��ʱ�临�Ӷ�---O(N*lgN)