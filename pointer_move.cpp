#include "normal_mode.h"
#include "cmd_mode.h"

using namespace std;

#define gotoxy(x,y) cout<<"\033["<<x<<";"<<y<<"H"

extern string home_path;
extern int up,n,x,y,screen_limit,mode;
extern map<string,string> trace_map;
struct termios initialrsettings, newrsettings;
int c = 0;
extern stack<string> back_st;   
extern stack<string> forword_st;
extern int itemCounter;
extern string new_path;
int pointer_move(){
    mode = 1;
    string path;
    int cur_pos;
    init_setting();
    string path1;

    //To handle ctlr+c signal
    struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = my_handler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, NULL);

    while(c != 101){
        fflush(stdin);
        fflush(stdout);
        path = new_path;
        cur_pos = itemCounter;
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
                        fflush(stdout); fflush(stdin);
                        if(!forword_st.empty()){
                            path1 = forword_st.top();
                            back_st.push(path1);
                            forword_st.pop(); list_print(path1,1,0); 
                        }
                        break;
                    } 
    		    case 'D':{ up = 0, x = 1;
                        if(!back_st.empty()){
                            path1 = back_st.top(); forword_st.push(path1);
                            back_st.pop(); list_print(path1,1,0); 
                        }
                        break;
                    }
                case 10:{
                    // if(!forword_st.empty() && x < 3){
                        back_st.push(path);
                        list_print(path,x,0);  
                    // } 
                    break;
                } 
                case 127: up = 0, x = 1;
                        if(!back_st.empty()){
                            path1 = back_st.top();
                            forword_st.push(path1);
                            back_st.pop(); list_print(path1,1,0); break;
                        }
                case 104: up = 0, x = 1;
                        list_print(home_path,1,0); break;
                case 58:  cmd_main(path); break;
    		    default: break;
    	    }
    }
    re_init_setting();
    exit(0);
}

void init_setting(){
    tcgetattr(0, &initialrsettings);
    newrsettings = initialrsettings;
    newrsettings.c_lflag &= ~ECHO;
    newrsettings.c_lflag &= ~ICANON;
    // newrsettings.c_lflag &= ~ISIG;
    tcsetattr(0, TCSANOW, &newrsettings);
}

void re_init_setting(){
    tcsetattr(0, TCSANOW, &initialrsettings);
}

void my_handler(int s){
    map<string,string>::iterator it;
    clear_scr(1);
    re_init_setting();
    for(it = trace_map.begin();it != trace_map.end(); it++){
        string file_path = home_path + "/Trash/" + it->first;
        unlink(file_path.c_str());
    }
    trace_map.erase(trace_map.begin(),trace_map.end());
    exit(1); 
}