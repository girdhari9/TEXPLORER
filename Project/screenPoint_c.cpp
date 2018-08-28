#include "screenPoint.h"

using namespace std;

void screen_point(int x, int y, int flag){
	if(flag)
		cout<<"\033[2J\033[1;1H";
	fflush(stdout);
	gotoxy(38,0);
	for(int i=0;i<=143;i++)
		cout<<"=";
	gotoxy(39,0);
	cout<<"Command Mode:";
	gotoxy(40,0);
	for(int i=0;i<=143;i++)
		cout<<"=";
	gotoxy(x,y);
	return;
}