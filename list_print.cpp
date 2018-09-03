#include "normal_mode.h"

using namespace std;

struct dirent ** namelist;
stack<string> back_st;
stack<string> forword_st;
int itemCounter;
string new_path;
extern int cmd_mod_screen_start,horizontal;
extern string home_path;
int up = 0,n,x = 1, y = 1, screen_limit;

void list_print(string path,int cur_pos, int update_value){
	screen_limit = cmd_mod_screen_start-1;
	new_path = path;
	if(cur_pos < 2){
		screen_point(0,0,1);
		itemCounter = 0;
	    print_dir(); //To print directory attributes
	    //To print current path location
	    
	    if(update_value == 2)
	    	screen_point(itemCounter,0,0);
	    else screen_point(0,0,0);
	    return;
	}
	/* After pressing "Enter" this code will run to traverse in new directroy 
	and Display all files of that directory */
	screen_point(0,0,1);
	itemCounter = 0;
	int index = up + cur_pos-1, flag = 1; 
	while(1){
		if((int)namelist[index]->d_type == 4){
			string s = namelist[index]->d_name;
			if(s == ".." && new_path == home_path){
				flag = 0;
				new_path = path;
			}
			else if(s == ".."){
				size_t found = new_path.find_last_of("/\\");
				new_path = new_path.substr(0,found);
			}
			else if(s == "."){ 
				new_path = path;
				flag = 0;
			}
			else new_path = path + '/' + s;	
			break;
		}
		else{
			pid_t pid = fork();
			if(pid == 0){
				execl("/usr/bin/xdg-open","xdg-open",(new_path + "/" + namelist[index]->d_name).c_str(),NULL);
			}
		}
		break;
	}
	if(flag)
	forword_st.push(new_path);
	up = 0, x = 1;
	print_dir(); 	//To print directory attributes
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

//To print directory attributes
void print_dir(){
	n = scandir(new_path.c_str(),&namelist,NULL, alphasort);
	for(int i = up; i < up + screen_limit && i < n; i++){
		string new_name = namelist[i]->d_name;
	    if(new_name.size() > 20)	
	    	new_name = trim_name(namelist[i]->d_name,19,1);
	    if(namelist[i]->d_type == 4)
	    	cout<<"\033[21;31m "<<new_name<<"\033[0m";
	    else if(namelist[i]->d_type == 8)
		    cout<<"\033[21;36m "<<new_name<<"\033[0m";
		else cout<<"\033[21;32m "<<new_name<<"\033[0m";
		string temp_path = new_path + "/" + namelist[i]->d_name;
		screen_point(itemCounter+1,30,0);
	    print_file_permission(temp_path);
		itemCounter++;
	}
	screen_point(cmd_mod_screen_start+1,20,0);
	if(new_path.size() > horizontal-10)
		cout <<"\033[21;32mPath:\033[0m./:"<<new_path.substr(home_path.size(),horizontal-10)<<"...";
	else cout <<"\033[21;32mPath:\033[0m./:"<<new_path.substr(home_path.size());
}
