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

void copy_file(string s, string t);
void cmd_main();
