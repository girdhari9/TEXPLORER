#include "normal_mode.h"

using namespace std;
int cmd_mod_screen_start,horizontal,vertical;

void screen_point(int x, int y, int flag){
	struct winsize size;
	ioctl(STDOUT_FILENO,TIOCGWINSZ,&size);

	vertical = size.ws_row;
	horizontal = size.ws_col;
	cmd_mod_screen_start = vertical - 10;
	cmd_mod_screen_start = vertical - 10;

	if(flag) clear_scr(1);
	fflush(stdout);
	gotoxy(cmd_mod_screen_start,0);
	for(int i=0;i<horizontal;i++)
		cout<<"=";
	gotoxy(cmd_mod_screen_start+1,0);
	cout<<"Command Mode:";
	gotoxy(cmd_mod_screen_start+2,0);
	for(int i=0;i<horizontal;i++)
		cout<<"=";
	gotoxy(x,y);
	return;
}

void clear_scr(int start){
	gotoxy(start,1);
	for(int i=start;i<=vertical;i++){
		for(int i=1;i<=horizontal;i++){
			cout<<" ";
		}
	}
	gotoxy(start,1);
}