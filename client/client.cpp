#include<signal.h>
#include<pthread.h>
#include"udp_client.h"
#include"cwindow.h"


typedef struct client_info
{
	udp_client* cli;
	cwindow* win;
	std::string nick_name;
	std::string school;
}cinfo;

cinfo c_info;
static void quit(int sig)
{
	udp_client* clip=c_info.cli;
	udp_data data;
	data.set_school(c_info.school);
	data.set_msg("None");
	data.set_type("QUIT");

	std::string str;
	data.val_to_str(str);

	clip->send_data(str);
	exit(0);
}

void usage(const char* proc)
{
	std::cout<<"Usage : "<<proc<<"[remote_ip][remote_port]"<<std::endl;

}

void *run_header(void* arg)
{
	cinfo* wcli=(cinfo*)arg;
	cwindow* winp=wcli->win;
	winp->draw_header();

	int max_y=0;
	int max_x=0;
	std::string msg="Welcom To Chat";
	int i=0;
	while(1)
	{
		getmaxyx(winp->get_header(),max_y,max_x);
		winp->put_str_to_win(winp->get_header(),max_y/2,i++,msg);
		winp->win_refresh(winp->get_header());
		winp->clear_win_line(winp->get_header(),max_y/2,2);
		i%=max_x;
		usleep(100000);
	}
}

void* run_output_flist(void* arg)
{
	cinfo * wcli=(cinfo*)arg;
	cwindow* winp=wcli->win;
	udp_client* clip=wcli->cli;

	winp->draw_output();
	winp->draw_flist();

	std::string in_str;
	udp_data data;

	std::string user;
	std::string friends;
	int max_y,max_x;

	int line=1;
	while(1)
	{
		getmaxyx(winp->get_output(),max_y,max_x);
		clip->recv_data(in_str);
		data.str_to_val(in_str);
		user=data.get_nick_name();
		user+="-";
		user+=data.get_school();

		friends=user;
		if(data.get_type()=="QUIT")
		{
			clip->del_friend(friends);
		}else
		{
			clip->add_friend(friends);
		}
		user+="# ";
		user+=data.get_msg();

		if(data.get_type()!="QUIT")
		{
			winp->put_str_to_win(winp->get_output(),line++,3,user);
		}
		if(line>max_y)
		{
			line=1;
			winp->clear_win_line(winp->get_output(),1,max_y-1);
		}

		int size=clip->flist.size();
		for(int i=0;i<size;i++)
		{
			winp->put_str_to_win(winp->get_flist(),i+1,2,clip->flist[i]);
		}
		usleep(100000);
		winp->win_refresh(winp->get_output());
		winp->win_refresh(winp->get_flist());
	}
}

void* run_input(void* arg)
{
	cinfo* wcli=(cinfo*)arg;
	wcli->win->draw_input();
	cwindow* winp=wcli->win;
	udp_client* clip=wcli->cli;
	std::string tips="Please Enter# ";

	int max_x=0;
	int max_y=0;

	udp_data data;
	std::string smsg;
	while(1)
	{
		data.set_nick_name(wcli->nick_name);
		data.set_school(wcli->school);
		data.set_type("None");

		getmaxyx(winp->get_input(),max_y,max_x);
		winp->put_str_to_win(winp->get_input(),1,2,tips);
		winp->win_refresh(winp->get_input());

		std::string tmp=data.get_msg();
		winp->get_str_to_win(winp->get_input(),tmp);

		data.val_to_str(smsg);
		clip->send_data(smsg);

		winp->clear_win_line(winp->get_input(),1,max_y-1);
		usleep(100000);
	}
}
int main(int argc,char* argv[])
{
	if(argc!=3)
	{
		usage(argv[0]);
		return 1;
	}
	signal(2,quit);
	std::cout<<"Please Enter nick_name: ";
	fflush(stdout);
	std::cin>>c_info.nick_name;
	std::cout<<"Please Enter school: ";
	fflush(stdout);
	std::cin>>c_info.school;

	udp_client net(argv[1],atoi(argv[2]));
	cwindow win;
	c_info.cli=&net;
	c_info.win=&win;

	pthread_t header,output_flist,input;
	pthread_create(&header,NULL,run_header,(void*)&c_info);
	pthread_create(&output_flist,NULL,run_output_flist,(void*)&c_info);
	pthread_create(&input,NULL,run_input,(void*)&c_info);
	pthread_join(header,NULL);
	pthread_join(output_flist,NULL);
	pthread_join(input,NULL);
	return 0;
}
