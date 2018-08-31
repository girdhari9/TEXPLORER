#include "normal_mode.h"
#include <termios.h>
using namespace std;

#define gotoxy(x,y) cout<<"\033["<<x<<";"<<y<<"H"

#include<dirent.h>

using namespace std;

// struct dirent ** namelist;


int item_select(int x,int cur_pos, string path){
    int itemCounter = 0;
    // string p1 = (string)path[2];
    // string p2 = (string)namelist[x]->d_name;
    // string p3 = p1 + p2 + '/';
    // cout<<p3<<" ";
    // path[2] = &p3;
    int n = scandir(path.c_str(),&namelist,NULL, alphasort);
    while(n--){
        cout<<namelist[n]->d_name<<"\n";
        itemCounter++;
        // free(namelist[n]);
    }
    // free(namelist);
    return itemCounter;
}