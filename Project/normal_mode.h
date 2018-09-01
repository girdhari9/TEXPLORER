#include<bits/stdc++.h>
#include<dirent.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include<pwd.h>
#include<grp.h>
#include <sys/ioctl.h>

using namespace std;

#define gotoxy(x,y) cout<<"\033["<<x<<";"<<y<<"H"

void screen_point(int x, int y, int flag);
void list_print(string path,int cur_pos,int update_value);
int pointer_move();
int item_select(int x,int cur_pos, string path);
void print_file_permission(string path);
void clear_scr(int start);
string trim_name(string name,int size,int flag);
void init_setting();
void re_init_setting();
