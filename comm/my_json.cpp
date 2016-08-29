#include"my_json.h"

my_json::my_json(){}
my_json::~my_json(){}
int my_json::serialize(Json::Value& _val,std::string& _out)
{
#ifdef FAST_JSON_
	Json::FastWriter write;
	_out=write.write(_out);
#else
	Json::StyledWriter write;
	_out=write.write(_out);
#endif
	return 0;
}
int my_json::deserialize(std::string& _str,Json::Value& _Jval)
{
	Json::Reader read;
	if(read.parse(_str,_Jval,false))
	{
		return 0;
	}
	return 1;
}
