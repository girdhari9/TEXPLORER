#include "screenPoint.h"
#include<dirent.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include<pwd.h>
#include<grp.h>

using namespace std;

struct dirent ** namelist;
stack<string> back_st;
stack<string> forword_st;
int itemCounter;

void list_print(string path,int cur_pos){
	string new_path = path;
	int i = 0;
	if(cur_pos < 2){
		screen_point(0,0,1);
		itemCounter = 0; int i=0;
	    int n = scandir(new_path.c_str(),&namelist,NULL, alphasort);
	    while(i<n){
	    	if(namelist[i]->d_type == 4)
	    		cout << "\033[1;31m "<<namelist[i]->d_name<<"\033[0m";
	    	else
		    	cout<<" "<<namelist[i]->d_name;
		    string temp_path = new_path + "/" + namelist[i]->d_name;
		    screen_point(itemCounter+1,40,0);
	        print_file_permission(temp_path);
		    i++;	
		    itemCounter++;
	    }
	    screen_point(itemCounter,0,0);
	    pointer_move(forword_st,back_st,new_path,itemCounter);
	}
	screen_point(0,0,1);
	itemCounter = 0; 
	while(1){
		if((int)namelist[cur_pos-1]->d_type == 4){
			string s = namelist[cur_pos-1]->d_name;
			new_path = path + '/' + s;
			break;
		}
		else{
			string opn_file = "xdg-open "+new_path + "/" + namelist[cur_pos-1]->d_name;
			system(opn_file.c_str());
			break;
		}
	}
		forword_st.push(new_path);
		int n = scandir(new_path.c_str(),&namelist,NULL, alphasort);
		while(i<n){
	    	if(namelist[i]->d_type == 4)
	    		cout << "\033[1;31m "<<namelist[i]->d_name<<"\033[0m";
	    	else
		    	cout<<" "<<namelist[i]->d_name;
		    string temp_path = new_path + "/" + namelist[i]->d_name;
		    screen_point(itemCounter+1,40,0);
	        print_file_permission(temp_path);
		    i++;	
		    itemCounter++;
	    }
	    screen_point(itemCounter,0,0);
	pointer_move(forword_st,back_st,new_path,itemCounter);
}


void print_file_permission(string path)
{
    struct stat fileStat;
    
    if(stat(path.c_str(),&fileStat) < 0)    
        return ;

    cout<<fileStat.st_size<<"B";

    screen_point(itemCounter+1,60,0);

    cout<<(S_ISDIR(fileStat.st_mode) ? "d" : "-");
    cout<<((fileStat.st_mode & S_IRUSR) ? "r" : "-");
    cout<<((fileStat.st_mode & S_IWUSR) ? "w" : "-");
    cout<<((fileStat.st_mode & S_IXUSR) ? "x" : "-");
    cout<<((fileStat.st_mode & S_IRGRP) ? "r" : "-");
    cout<<((fileStat.st_mode & S_IWGRP) ? "w" : "-");
    cout<<((fileStat.st_mode & S_IXGRP) ? "x" : "-");
    cout<<((fileStat.st_mode & S_IROTH) ? "r" : "-");
    cout<<((fileStat.st_mode & S_IWOTH) ? "w" : "-");
    cout<<((fileStat.st_mode & S_IXOTH) ? "x" : "-");

    struct passwd *pw = getpwuid(fileStat.st_uid);
	struct group  *gr = getgrgid(fileStat.st_gid);


	cout<<"\t\t"<<gr->gr_name<<"\t\t"<<pw->pw_name<<"\t\t";
	cout<<ctime(&fileStat.st_mtime);

    return ;
}