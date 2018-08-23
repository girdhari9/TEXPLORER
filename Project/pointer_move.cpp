#include "screenPoint.h"
#include <termios.h>
using namespace std;

#define gotoxy(x,y) cout<<"\033["<<x<<";"<<y<<"H"


int pointer_move(int cur_pos){
	struct termios initialrsettings, newrsettings;
    tcgetattr(0, &initialrsettings);
    
    newrsettings = initialrsettings;
    newrsettings.c_lflag &= ~ECHO;
    newrsettings.c_lflag &= ~ICANON;
    // newrsettings.c_lflag &= ~ISIG;
    tcsetattr(0, TCSANOW, &newrsettings);

    int c = 0, x = 1, y = 0;
    while(c != 101){
    		switch(c = getchar()){
    		    case 'A': if(x > 1) screen_point(--x,y,0); break;
    		    case 'B': if(x <= cur_pos) screen_point(++x,y,0); break;
    		    // case 'C': if(y < 144) screen_point(x,++y,0); break;
    		    // case 'D': if(y) screen_point(x,--y,0); break;
                case 10: list_print(x);
    		    default: break;
    	    }
    }
    tcsetattr(0, TCSANOW, &initialrsettings);
    exit(0);
}