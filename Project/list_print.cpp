#include "screenPoint.h"

using namespace std;

struct dirent ** namelist;
stack<string> back_st;
stack<string> forword_st;
int itemCounter;

int up = 0,n,x = 1, y = 0, screen_limit = 15;

void list_print(string path,int cur_pos, int update_value){
	string new_path = path;
	if(cur_pos < 2){
		screen_point(0,0,1);
		itemCounter = 0;
	    n = scandir(new_path.c_str(),&namelist,NULL, alphasort);
	    for(int i = up; i < up + screen_limit && i < n; i++){
	    	if(namelist[i]->d_type == 4)
	    		cout << "\033[1;31m "<<namelist[i]->d_name<<"\033[0m";
	    	else
		    	cout<<" "<<namelist[i]->d_name;
		    string temp_path = new_path + "/" + namelist[i]->d_name;
		    screen_point(itemCounter+1,40,0);
	        print_file_permission(temp_path);
		    itemCounter++;
	    }
	    if(update_value == 2)
	    	screen_point(itemCounter,0,0);
	    else screen_point(0,0,0);
	    pointer_move(forword_st,back_st,new_path,itemCounter);
	}
	/* After pressing "Enter" this code will run to traverse in new directroy 
	and Display all files of that directory */

	screen_point(0,0,1);
	itemCounter = 0;
	int index = up + cur_pos-1; 
	while(1){
		if((int)namelist[index]->d_type == 4){
			string s = namelist[index]->d_name;
			if(s == ".." && forword_st.empty())
				new_path = path;
			else if(s == ".") new_path = path;
			else new_path = path + '/' + s;	
			break;
		}
		else{
			string opn_file = "xdg-open "+new_path + "/" + namelist[index]->d_name;
			system(opn_file.c_str());
			break;
		}
	}
	forword_st.push(new_path);
	n = scandir(new_path.c_str(),&namelist,NULL, alphasort);
	up = 0, x = 1;
	for(int i = up; i < up + screen_limit && i < n; i++){
	    if(namelist[i]->d_type == 4)
	    	cout << "\033[1;31m "<<namelist[i]->d_name<<"\033[0m";
	    else
		    cout<<" "<<namelist[i]->d_name;
		string temp_path = new_path + "/" + namelist[i]->d_name;
		screen_point(itemCounter+1,40,0);
	    print_file_permission(temp_path);
		itemCounter++;
	} 
	screen_point(0,0,0);
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