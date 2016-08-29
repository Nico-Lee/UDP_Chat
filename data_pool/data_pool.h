#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<semaphore.h>

#define POOL_SIZE 512

class data_pool
{
	public:
		data_pool(int _size =POOL_SIZE);
		~data_pool();
		bool get_msg(std::string& msg);
		bool put_msg(const std::string& msg);
	private:
		const int pool_size;
		std::vector<std::string> pool;
		sem_t product_sem;
		sem_t consumer_sem;
		int start;
		int end;
};

