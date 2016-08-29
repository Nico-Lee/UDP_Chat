#pragma once
#include<iostream>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>


void print_log(std::string _log,std::string func,int line)
{
#ifdef _DEBUG_
	std::cerr<<"function"<<func<<":"<<"line"<<":"<<line<<_log<<std::endl;
#endif
}
