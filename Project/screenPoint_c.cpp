#include "screenPoint.h"

using namespace std;

int cmd_mod_screen_start = 30;

void screen_point(int x, int y, int flag){
	if(flag)
		cout<<"\033[2J\033[1;1H";
	fflush(stdout);
	gotoxy(cmd_mod_screen_start,0);
	for(int i=0;i<=143;i++)
		cout<<"=";
	gotoxy(cmd_mod_screen_start+1,0);
	cout<<"Command Mode:";
	gotoxy(cmd_mod_screen_start+2,0);
	for(int i=0;i<=143;i++)
		cout<<"=";
	gotoxy(x,y);
	return;
}