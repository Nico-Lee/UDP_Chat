
#ifndef _MY_JSON_H_
#define _MY_JSON_H_
#include<iostream>
#include<string>
#include"../json_lib/include/json/json.h"
using namespace std;


class my_json
{
	public:
		my_json();
		~my_json();
		int serialize(Json::Value& _val,std::string& _out);
		int deserialize(std::string& _str,Json::Value& _Jval);
};
#endif
