#include<pthread.h>
#include"cwindow.h"
#include"udp_data.cpp"
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
cwindow::cwindow()
{
	header=NULL;
	output=NULL;
	input=NULL;
	flist=NULL;
}
cwindow::~cwindow()
{
	delwin(header);
	delwin(output);
	delwin(flist);
	delwin(input);
	endwin();
}
void cwindow::init()
{
	initscr();
}
WINDOW* cwindow::create_win(int hig,int wth,int y,int x)
{
	pthread_mutex_lock(&mutex);
	WINDOW* _win=newwin(hig,wth,y,x);
	pthread_mutex_unlock(&mutex);
	return _win;
}
void cwindow::draw_header()
{
	int hig=LINES/5;
	int wth=COLS;
	int y=0;
	int x=0;
	header=create_win(hig,wth,y,x);
}
void cwindow::draw_output()
{
	int hig=LINES*3/5;
	int wth=COLS*3/4;
	int y=LINES/5;
	int x=0;
	output=create_win(hig,wth,y,x);
}
void cwindow::draw_flist()
{
	int hig=LINES*3/5;
	int wth=COLS/4;

	int y=LINES/5;
	int x=COLS*3/4;
	flist=create_win(hig,wth,y,x);
}
void cwindow::draw_input()
{
	int hig=LINES/5;
	int wth=COLS;
	int y=LINES*4/5;
	int x=0;
	input=create_win(hig,wth,y,x);
}

void cwindow::win_refresh(WINDOW* _win)
{
	pthread_mutex_lock(&mutex);
	box(_win,0,0);
	wrefresh(_win);
	pthread_mutex_unlock(&mutex);
}
void cwindow::put_str_to_win(WINDOW* _win,int _y,int _x,\
		const std::string& _str)
{
	pthread_mutex_lock(&mutex);
	mvwaddstr(_win,_y,_x,_str.c_str());
	pthread_mutex_unlock(&mutex);
}
void cwindow::get_str_to_win(WINDOW* _win,std::string& _msg)
{
	char buf[BUF_SIZE];
	memset(buf,'\0',sizeof(buf));
	wgetnstr(_win,buf,sizeof(buf));
	_msg=buf;
}
void cwindow::clear_win_line(WINDOW* _win,int _begin,int _num)
{
	pthread_mutex_lock(&mutex);
	while(_num-->0)
	{
		wmove(_win,_begin++,0);
		wclrtoeol(_win);
	}
	pthread_mutex_unlock(&mutex);
}

WINDOW* cwindow::get_header()
{
	return header;
}
WINDOW* cwindow::get_flist()
{
	return flist;
}
WINDOW* cwindow::get_output()
{
	return output;
}
WINDOW* cwindow::get_input()
{
	return input;
}



//int main()
//{
//	cwindow c;
//	c.draw_header();
//	sleep(1);
//	c.draw_flist();
//	sleep(1);
//	c.draw_input();
//	sleep(1);
//	c.draw_output();
//	return 0;
//}
