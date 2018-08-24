#include "screenPoint.h"
#include<dirent.h>

using namespace std;

struct dirent ** namelist;

void list_print(string pre_path,string path,int cur_pos){
	string new_path = path;
	int i = 0;
	if(cur_pos < 2){
		screen_point(0,0,1);
		cout<<path<<" ";
		int itemCounter = 0,i=0;
	    int n = scandir(path.c_str(),&namelist,NULL, alphasort);
	    while(i<n){
	    	if(namelist[i]->d_type == 4)
	    		cout << "\033[1;31m "<<namelist[i]->d_name<<"\033[0m\n";
	    	else
		    	cout<<" "<<namelist[i]->d_name<<"\n";
		    i++;	
		    itemCounter++;
		    // free(namelist[i]);
	    }
	    // free(namelist);
	    screen_point(itemCounter,0,0);
	    pointer_move(pre_path,new_path,itemCounter);
	}
	screen_point(0,0,1);
	int itemCounter = 0, flag = 1;
	// cout<<namelist[cur_pos-1]->d_name;
	while(1){
		if((int)namelist[cur_pos-1]->d_type == 4){
			string s = namelist[cur_pos-1]->d_name;
			if(s == ".") {
				flag = 0; break;
			}
			if(s == ".."){
				// flag = 0;
				int pos = new_path.size()-1;
				while(s[pos] != '/') pos--;
				new_path[pos] = NULL;
				cout<<new_path<<" ";
				// break;
			}
			// else{
				new_path = path + '/' + s;
				break;
			// }
		}
		else break;
	}
	if(flag){
		int n = scandir(new_path.c_str(),&namelist,NULL, alphasort);
		while(i<n){
	    	if(namelist[i]->d_type == 4)
	    		cout << "\033[1;31m "<<namelist[i]->d_name<<"\033[0m\n";
	    	else
		    	cout<<" "<<namelist[i]->d_name<<"\n";
		    i++;	
		    itemCounter++;
		    // free(namelist[i]);
	    }
		// free(namelist);
		screen_point(itemCounter,0,0);
		pointer_move(pre_path,new_path,itemCounter);
	}	
	
}