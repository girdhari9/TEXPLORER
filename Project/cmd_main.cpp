#include "cmd_mode.h"
#include "screenPoint.h"

using namespace std;

vector<string> v;
vector<string>::iterator it;
extern string home_path;

void cmd_main(){
        screen_point(33,0,0); 
        string s, clear_screen = "clear";
        getline(cin, s);
        // if(s == clear_screen){
        //     cout<<"\033[2J\033[33;1H";
        // }
        for(unsigned int i = 0;i < s.size(); i++){
            int x = i;
            while(s[i] != ' ' && i < s.size()) i++;
            v.push_back(s.substr(x,i-x));
        }
        for(int i = 1; i < v.size()-1; i++){   
            if(v[0] == "copy") copy_file(home_path + "/" + v[i],home_path + "/" + v[v.size()-1] + "/" + v[i]);
            else break;
        }
        cout<<"File Copied Successfully!";

}