#include "screenPoint.h"
#include "cmd_mode.h"
#include <termios.h>
using namespace std;

#define gotoxy(x,y) cout<<"\033["<<x<<";"<<y<<"H"
string home_path = "/home/gunno/Documents/os";
extern int up,n,x,y,screen_limit;

int c = 0;

int pointer_move(stack<string> &forword_st,stack<string> &back_st,string path, int cur_pos){
	struct termios initialrsettings, newrsettings;
    tcgetattr(0, &initialrsettings);
    
    newrsettings = initialrsettings;
    newrsettings.c_lflag &= ~ECHO;
    newrsettings.c_lflag &= ~ICANON;
    // newrsettings.c_lflag &= ~ISIG;
    tcsetattr(0, TCSANOW, &newrsettings);

    string path1;

    while(c != 101){
    		switch(c = getchar()){
    		    case 'A': if(x > 1) screen_point(--x,y,0);
                        else if(up != 0){ 
                            up--; list_print(path,1,1);
                        } break;
    		    case 'B': if(x < cur_pos && x < screen_limit) screen_point(++x,y,0); 
                          else if(up + screen_limit < n){
                                up++; list_print(path,1,2);
                          } break;
    		    case 'C':{ up = 0, x = 1;
                        if(!forword_st.empty()){
                            path1 = forword_st.top();
                            back_st.push(path1);
                            forword_st.pop(); list_print(path1,1,0); break;
                        }
                    } 
    		    case 'D':{ up = 0, x = 1;
                        if(!back_st.empty()){
                            path1 = back_st.top(); forword_st.push(path1);
                            back_st.pop(); list_print(path1,1,0); break;
                        }
                    }
                case 10:{ 
                    back_st.push(path);
                    list_print(path,x,0); break;  
                } 
                case 127: up = 0, x = 1;
                        if(!back_st.empty()){
                            path1 = back_st.top();
                            forword_st.push(path1);
                            back_st.pop(); list_print(path1,1,0); break;
                        }
                case 104: up = 0, x = 1;
                        list_print(home_path,1,0); break;
                case 58: tcsetattr(0, TCSANOW, &initialrsettings); cmd_main();
    		    default: break;
    	    }
    }
    tcsetattr(0, TCSANOW, &initialrsettings);
    exit(0);
}