#ifndef _CWINDOW_H_
#define _CWINDOW_H_
#include<iostream>
#include<string>
#include<string.h>
#include<ncurses.h>
#include<pthread.h>

#define BUF_SIZE 1024
class cwindow
{
	public:
		cwindow();
		~cwindow();
		void init();
		void draw_header();
		void draw_output();
		void draw_flist();
		void draw_input();

		void win_refresh(WINDOW* _win);
		 void put_str_to_win(WINDOW* _win,int _y,int _x,\
				const std::string& _str);
		void get_str_to_win(WINDOW* _win,std::string& _msg);
		void clear_win_line(WINDOW* _win,int _begin,int _num);

		WINDOW* get_header();
		WINDOW* get_flist();
		WINDOW* get_output();
		WINDOW* get_input();
	private:
		WINDOW* create_win(int hei,int wth,int y,int x);
	private:
		WINDOW* header;
		WINDOW* output;
		WINDOW* input;
		WINDOW* flist;
};

#endif
