#ifndef _UDP_DATA_H_
#define _UDP_DATA_H
#include<iostream>
#include"my_json.h"

class udp_data
{
	public:
		udp_data();
		~udp_data();
		int val_to_str(std::string& _out);
		int str_to_val(std::string& _in);


		const std::string& get_nick_name();
		const std::string& get_school();
		const std::string& get_msg();
		const std::string& get_type();


		void set_nick_name(const std::string& _nick_name);
		void set_msg(const std::string& _msg);
		void set_type(const std::string& _type);
		void set_school(const std::string& _school);
	private:
		my_json json_bit;
		std::string nick_name;
		std::string school;
		std::string msg;
		std::string type;
};
#endif
