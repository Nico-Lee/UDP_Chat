#include"udp_client.h"


udp_client::udp_client(const std::string& ip,const int& port)
	:_remote_ip(ip)
	 ,_remote_port(port)
{
	init();
}
int udp_client::init()
{
	_sock=socket(AF_INET,SOCK_DGRAM,0);
	if(_sock<0)
	{
		perror("create sock error");
		exit(1);
	}
	return 0;
}
int udp_client::recv_data(std::string& out)
{
	char  buf[SIZE];
	struct sockaddr_in server;
	socklen_t len=sizeof(server);
	ssize_t _s=recvfrom(_sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&server,&len);
	if(_s>0)
	{
		buf[_s]='\0';
		out=buf;
	}else
	{
		perror("recv error");
		return _s;
	}
}
int udp_client::send_data(const std::string& in)
{
	struct sockaddr_in server;
	server.sin_family=AF_INET;
	server.sin_port=htons(_remote_port);
	server.sin_addr.s_addr=inet_addr(_remote_ip.c_str());
	ssize_t _s=sendto(_sock,in.c_str(),in.size(),0,(struct sockaddr*)&server,sizeof(server));
	if(_s<0)
	{
		perror("sendto error ");

	}
	return _s;
}
udp_client::~udp_client()
{
	if(_sock>0)
		close(_sock);
}

void udp_client::add_friend(std::string &f)
{
	if(!is_friend_exist(f))
	{
		flist.push_back(f);
	}
}
void udp_client::del_friend(std::string &f)
{
	if(is_friend_exist(f))
	{
		std::vector<std::string>::iterator iter=flist.begin();
		for(;iter!=flist.end();)
		{
			if(*iter==f)
			{
				iter=flist.erase(iter);
				break;
			}else
			{
				++iter;
			}
		}
	}
}
bool udp_client::is_friend_exist(const std::string &_key)
{
	std::vector<std::string>::iterator iter=flist.begin();
	for(;iter!=flist.end();++iter)
	{
		if(*iter==_key)
			return true;
	}
	return false;
}
