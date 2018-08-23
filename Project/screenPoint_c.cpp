#include "screenPoint.h"


#define gotoxy(x,y) cout<<"\033["<<x<<";"<<y<<"H"

using namespace std;

void screen_point(int x, int y, int flag){
	if(flag)
	cout<<"\033[2J\033[1;1H";
	fflush(stdout);
	gotoxy(40,0);
	cout<<"---------------------------------";
	cout<<"---------------------------------";
	cout<<"---------------------------------";
	cout<<"---------------------------------";
	cout<<"------------";
	gotoxy(41,0);
	cout<<"Command Mode:";
	gotoxy(x,y);
	return;
}