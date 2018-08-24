#include "screenPoint.h"
#include<dirent.h>

using namespace std;

struct dirent ** namelist;

int list_print(string pre_path,string path,int cur_pos){
	// cout<<cur_pos<<" ";
	int i = 0;
	if(!cur_pos){
		int itemCounter = 0,i=0;
	    int n = scandir(path.c_str(),&namelist,NULL, alphasort);
	    while(i<n){
		    cout<<" "<<namelist[i]->d_name<<"\n";
		    i++;
		    itemCounter++;
	    }
	    return itemCounter;
	}
	screen_point(0,0,1);
	int itemCounter = 0;
	string new_path = path;
	// cout<<namelist[cur_pos-1]->d_name;
	while(1){
		if((int)namelist[cur_pos-1]->d_type == 4){
			string s = namelist[cur_pos-1]->d_name;
			// cout<<s<<" ";
			if(s == ".") break;
			if(s == ".."){
				int pos = path.size()-1;
				while(s[pos] != '/') pos--;
				path[pos] = '\0';
				new_path = path;
				break;
			}
			else{
				new_path = path + '/' + s;
				break;
			}
		}
		else break;
	}
	// cout<<new_path<<" ";
	int n = scandir(new_path.c_str(),&namelist,NULL, alphasort);
	while(i < n){
		cout<<i<<" "<<namelist[i]->d_name<<"\n";
		i++;
		itemCounter++;
	}
	screen_point(itemCounter,0,0);
	pointer_move(pre_path,path,itemCounter);
}