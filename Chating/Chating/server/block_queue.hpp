#pragma once
#include<iostream>
#include<vector>
#include<semaphore.h> //信号
#include<string.h>
using namespace  std;

namespace server{
template <typename T>
class BlockQueue{
public:
	BlockQueue(size_t s = 1024)
		:data_(s)
		,head_(0)
		,tail_(0)
		,size_(0)
	{
		sem_init(&sem_data_,0,0);
		sem_init(&sem_blank_,0,s);
	}

	~BlockQueue(){
		sem_destroy(&sem_data_);
		sem_destroy(&sem_blank_);
	}

	//插入元素
	void PushBack(const T& value){
		sem_wait(&sem_blank_); //先对空白资源wait操作,阻塞等待直到右空白资源
		data_[tail_++] = value; //插入数据
		if(tail_ > data_.size()){
			tail_ = 0;
		}
		++size_; //
		sem_post(&sem_data_);
	}

	void PopFront(T* value){
		sem_wait(&sem_data_); //无数据阻塞等待
		*value = data_[head_++];
		if(head_ >= data_.size()){
			head_ = 0;
		}
		--size_;
		sem_post(&sem_blank_); //v操作
	}

private:
	vector<T> data_;
	sem_t sem_data_; //资源
	sem_t sem_blank_; //空白资源
	//由于此处实现的是一个单生产者消费者的BlockQueue,可以不加互斥锁
	//sem_t sem_lock;
	size_t head_; 
	size_t tail_;
	size_t size_; //资源数
};
};
