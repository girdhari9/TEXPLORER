#include "normal_mode.h"

using namespace std;

struct dirent ** namelist;
stack<string> back_st;
stack<string> forword_st;
int itemCounter;
string new_path;
extern int cmd_mod_screen_start;
int up = 0,n,x = 1, y = 1, screen_limit = 13;

void list_print(string path,int cur_pos, int update_value){
	new_path = path;
	if(cur_pos < 2){
		screen_point(0,0,1);
		itemCounter = 0;
	    n = scandir(new_path.c_str(),&namelist,NULL, alphasort);
	    for(int i = up; i < up + screen_limit && i < n; i++){
	    	string new_name = namelist[i]->d_name;
	    	if(new_name.size() > 20)
	    		new_name = trim_name(namelist[i]->d_name,19,1);
	    	if(namelist[i]->d_type == 4)
	    		cout << "\033[1;31m "<<new_name<<"\033[0m";
	    	else
		    	cout<<" "<<new_name;
		    string temp_path = new_path + "/" + namelist[i]->d_name;
		    screen_point(itemCounter+1,30,0);
	        print_file_permission(temp_path);
		    itemCounter++;
	    }
	    if(update_value == 2)
	    	screen_point(itemCounter,0,0);
	    // if(update_value == 4) return;
	    else screen_point(0,0,0);
	    return;
	}
	/* After pressing "Enter" this code will run to traverse in new directroy 
	and Display all files of that directory */

	screen_point(0,0,1);
	// cout<<path.substr(18);
	itemCounter = 0;
	int index = up + cur_pos-1, flag = 1; 
	while(1){
		if((int)namelist[index]->d_type == 4){
			string s = namelist[index]->d_name;
			// if(s == ".."){
			// 	flag = 0;
			// 	new_path = path;
			// }
			// else if(s == ".") new_path = path;
			new_path = path + '/' + s;	
			break;
		}
		else{
			string opn_file = "xdg-open "+ new_path + "/" + namelist[index]->d_name;
			system(opn_file.c_str());
			break;
		}
	}
	if(flag)
	forword_st.push(new_path);
	n = scandir(new_path.c_str(),&namelist,NULL, alphasort);
	up = 0, x = 1;
	for(int i = up; i < up + screen_limit && i < n; i++){
		string new_name = namelist[i]->d_name;
	    if(new_name.size() > 20)	
	    	new_name = trim_name(namelist[i]->d_name,19,1);
	    if(namelist[i]->d_type == 4)
	    	cout <<"\033[1;31m "<<new_name<<"\033[0m";
	    else
		    cout<<" "<<new_name;
		string temp_path = new_path + "/" + namelist[i]->d_name;
		screen_point(itemCounter+1,30,0);
	    print_file_permission(temp_path);
		itemCounter++;
	} 
	screen_point(0,0,0);
	return;
}


void print_file_permission(string path)
{
    struct stat fileStat;
    
    if(stat(path.c_str(),&fileStat) < 0)    
        return ;

    cout<<fileStat.st_size<<"B";

    screen_point(itemCounter+1,40,0);

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


	cout<<" "<<gr->gr_name<<" "<<pw->pw_name<<" ";
	string time = ctime(&fileStat.st_mtime);
	cout<<time.substr(4,12)<<"\n";
    return ;
}

string trim_name(string name,int size,int flag){
	string t;
	for(int i=0;i<size;i++){
		t += name[i];
	}
	if(flag)	
		t += "...";
	return t;
}
