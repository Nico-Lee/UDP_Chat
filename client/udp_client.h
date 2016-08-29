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
#include<string.h>
#include<pthread.h>
#include<unistd.h>
#include<map>
#include<vector>
#include"udp_data.h"


#define SIZE 1024
class udp_client
{

	public:
		udp_client(const std::string& ip="127.0.0.1",const int& port=8888);
		int init();
		int recv_data(std::string& out);
		int send_data(const std::string& in);
		void add_friend(std::string &);
		void del_friend(std::string &);
		~udp_client();
	public:
		std::vector<std::string> flist;
	private:
		bool is_friend_exist(const std::string &);
	private:
		int _sock;
		int _remote_port;
		std::string _remote_ip;
};
