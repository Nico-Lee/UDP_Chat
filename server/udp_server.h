#pragma once
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>
#include<string>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
#include<map>
#include"udp_data.h"
#include"data_pool.h"

#define SIZE 1024
class udp_server
{
	public:
		bool is_user_exist(std::string &key);
		void add_user(std::string& ip,struct sockaddr_in& sk);
		void del_user(std::string& key);
		int send_data(struct sockaddr_in& client,\
				socklen_t &len,std::string& in);
	public:
		udp_server(const std::string& ip="127.0.0.1",const int& port=8888);
		int init();
		int recv_data(std::string& out);
		int broadcast_data();
		~udp_server();
	private:
		int _sock;
		int _port;
		std::string _ip;
		std::map<std::string,struct sockaddr_in> _online_user;
		data_pool _pool;
};
