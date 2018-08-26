#include "screenPoint.h"
#include "cmd_mode.h"
#include <termios.h>
using namespace std;

#define gotoxy(x,y) cout<<"\033["<<x<<";"<<y<<"H"

// stack<string> st;

int pointer_move(stack<string> &forword_st,stack<string> &back_st,string path, int cur_pos){
    // cout<<st.top()<<" ";
	struct termios initialrsettings, newrsettings;
    tcgetattr(0, &initialrsettings);
    
    newrsettings = initialrsettings;
    newrsettings.c_lflag &= ~ECHO;
    newrsettings.c_lflag &= ~ICANON;
    // newrsettings.c_lflag &= ~ISIG;
    tcsetattr(0, TCSANOW, &newrsettings);

    int c = 0, x = cur_pos, y = 0;
    string path1;

    while(c != 58){
    		switch(c = getchar()){
                cout<<"$";
    		    case 'A': if(x) screen_point(--x,y,0);
                          else{ x = cur_pos; screen_point(x,y,0); } break;
    		    case 'B': if(x < cur_pos && x < 38) screen_point(++x,y,0); 
                          else{ x = 1; screen_point(x,y,0); } break;
    		    case 'C':
                        if(!forword_st.empty()){
                            path1 = forword_st.top();
                            back_st.push(path1);
                            forword_st.pop(); list_print(path1,1); break;
                        }
    		    case 'D':{ 
                        if(!back_st.empty()){
                            path1 = back_st.top(); forword_st.push(path1);
                            back_st.pop(); list_print(path1,1); break;
                        }
                    }
                case 10:{
                    back_st.push(path);
                    list_print(path,x); break;  
                } 
                case 8:
                        if(!back_st.empty()){
                            path1 = back_st.top();
                            forword_st.push(path1);
                            back_st.pop(); list_print(path1,1); break;
                        }
    		    default: break;
    	    }
    }
    string cmd_arg[3];
    while(c != 101){
        screen_point(41,y,0); 
        tcsetattr(0, TCSANOW, &initialrsettings);
        switch(c = getchar()){
            case 10:cin>>cmd_arg[0]>>cmd_arg[1]>>cmd_arg[0]; 
                    if(cmd_arg[0] == "copy") copy_file(path + cmd_arg[1],cmd_arg[2]);
                    else break;
            default: break;
        }
    }
    tcsetattr(0, TCSANOW, &initialrsettings);
    exit(0);
}