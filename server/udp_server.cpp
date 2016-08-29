#include"udp_server.h"
int udp_server::init()
{
	int _sock=socket(AF_INET,SOCK_DGRAM,0);
	if(_sock<0)
	{
		perror("socket error!");
		exit(1);
	}
	struct sockaddr_in local;
	local.sin_family=AF_INET;
	local.sin_addr.s_addr=inet_addr(_ip.c_str());
	local.sin_port=htons(_port);
	if(bind(_sock,(struct sockaddr*)&local,sizeof(local))<0)
	{
		perror("bind error!");
		exit(2);
	}
	return 0;
}

int udp_server::recv_data(std::string& out)
{
	char buf[SIZE];
	struct sockaddr_in peer;
	socklen_t len=sizeof(peer);
	ssize_t _s=recvfrom(_sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&peer,&len);
	if(_s>0)
	{
		buf[_s]='\0';
		out=buf;
		std::string ip=inet_ntoa(peer.sin_addr);
		udp_data data;
		data.str_to_val(out);
		if(data.get_type()=="QUIT")
		{
			del_user(ip);
		}else
		{
			add_user(ip,peer);
		}
		std::cout<<"recv: "<<buf<<std::endl;
		_pool.put_msg(buf);
	}
	else
	{
		perror("bind sock error");

	}
	return _s;
}

int udp_server::broadcast_data()
{
	std::string msg;
	_pool.get_msg(msg);

	std::cout<<"broadcast: "<<msg<<std::endl;
	std::map<std::string,struct sockaddr_in>::iterator iter=_online_user.begin();
	socklen_t len=0;
	for(;iter!=_online_user.end();iter++)
	{
		len=sizeof(iter->second);
		send_data(iter->second,len,msg);
	}
}

void udp_server::add_user(std::string& ip,struct sockaddr_in& sk)
{
	if(!(is_user_exist(ip)))
	{
		_online_user.insert(std::pair<std::string,struct sockaddr_in>(ip,sk));
	}
}

void udp_server::del_user(std::string& key)
{
	if(is_user_exist(_ip))
	{
		_online_user.erase(key);
	}
}

udp_server::udp_server(const std::string& ip,const int& port)
	:_ip(ip)
	 ,_port(port)
{
	init();	
}

int udp_server::send_data(struct sockaddr_in& client,socklen_t &len,\
		std::string& in)
{
	ssize_t _s=sendto(_sock,in.c_str(),in.size(),0,(struct sockaddr*)&client,len);
	if(_s<0)
	{
		perror("sendto error ");

	}
	return _s;
}

bool udp_server::is_user_exist(std::string &key)
{
	std::map<std::string,struct sockaddr_in>::iterator iter=_online_user.find(key);
	return iter==_online_user.end()?false:true;
}



udp_server::~udp_server()
{
	if(_sock<0)
		close(_sock);
}
