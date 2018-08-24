#include "screenPoint.h"
#include <termios.h>
using namespace std;

#define gotoxy(x,y) cout<<"\033["<<x<<";"<<y<<"H"


int pointer_move(string pre_path,string path, int cur_pos){
	struct termios initialrsettings, newrsettings;
    tcgetattr(0, &initialrsettings);
    
    newrsettings = initialrsettings;
    newrsettings.c_lflag &= ~ECHO;
    newrsettings.c_lflag &= ~ICANON;
    // newrsettings.c_lflag &= ~ISIG;
    tcsetattr(0, TCSANOW, &newrsettings);

    int c = 0, x = cur_pos, y = 0;
    while(c != 101){
    		switch(c = getchar()){
    		    case 'A': if(x) screen_point(--x,y,0); break;
    		    case 'B': if(x < cur_pos) screen_point(++x,y,0); break;
    		    case 'C': list_print(pre_path,path,x); break;
    		    case 'D': list_print(pre_path,path,x); break;
                case 10: list_print(pre_path,path,x);
    		    default: break;
    	    }
    }
    tcsetattr(0, TCSANOW, &initialrsettings);
    exit(0);
}