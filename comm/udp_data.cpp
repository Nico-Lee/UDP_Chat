#include"udp_data.h"

udp_data::udp_data(){}
udp_data::~udp_data(){}
int udp_data::val_to_str(std::string& _out)
{
	Json::Value _val;
	_val["nick_name"]=nick_name;
	_val["school"]=school;
	_val["msg"]=msg;
	_val["type"]=type;
	json_bit.serialize(_val,_out);
}
int udp_data::str_to_val(std::string& _in)
{
	Json::Value _val;
	json_bit.deserialize(_in,_val);
	nick_name=_val["nick_name"].asString();
	school=_val["school"].asString();
	msg=_val["msg"].asString();
	type=_val["type"].asString();
}

const std::string& udp_data::get_nick_name(){return nick_name;}
const std::string& udp_data::get_school(){return school;}
const std::string& udp_data::get_msg(){return msg;};
const std::string& udp_data::get_type(){return type;};

void udp_data::set_nick_name(const std::string& _nick_name)
{nick_name=_nick_name;}
void udp_data::set_msg(const std::string& _msg)
{msg=_msg;}
void udp_data::set_type(const std::string& _type)
{type=_type;}
void udp_data::set_school(const std::string& _school)
{school=_school;}

