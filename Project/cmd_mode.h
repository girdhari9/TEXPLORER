#include<bits/stdc++.h>
#include<dirent.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include<pwd.h>
#include<grp.h>
#include <stdlib.h>
#include<getopt.h>
#include<fcntl.h>
	
using namespace std;	

#define gotoxy(x,y) cout<<"\033["<<x<<";"<<y<<"H"

void cmd_main(string s);
void copy_file(string s, string t);
void move_file(string s, string t);
void delete_dir(string t);
void search_file(string s, string t,int a);
void search_dir(string t,string s,string file);
void snapshot(string path,string file,string folder);
void tokenized(string s);
void copy_dir(string s, string t);
void print_search_file(vector<string> &v,string);
void cmd_arr_decl();
int set_path(string , int);