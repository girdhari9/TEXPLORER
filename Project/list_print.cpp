#include "screenPoint.h"
#include<dirent.h>

using namespace std;

struct dirent ** namelist;

string path = "/home/gunno/Documents";
// struct dirlist {
//     unsigned char  d_type;       type of file; not supported
//                                    by all file system types 
//     char           d_name[256]; /* filename */
//     int pos;
// };
vector< pair<string,int> > v;
vector< pair<string,int> >::iterator it;

int list_print(int cur_pos){
	if(cur_pos < 2){
		int itemCounter = 0;
	    int n = scandir(path.c_str(),&namelist,NULL, alphasort);
	    int i = 0;
	    while(i < n){
		    cout<<" "<<namelist[i]->d_name<<"\n";
		    i++;
		    v.push_back(make_pair(namelist[i]->d_name,i));
		    itemCounter++;
		    // free(namelist[n]);
	    }
	    // free(namelist);
	    return itemCounter;
	}
	int itemCounter = 0, i = 0;
	it = v.begin(); string new_path;
	while(it != v.end()){
		pair<string,int> p = *it;
		if(cur_pos == p.second){
			if(namelist[i]->d_type == 'd'){
				string s = namelist[i]->d_name;
				new_path = s + '/' + path;
			}
		}
		else it++;
	}
	int n = scandir(new_path.c_str(),&namelist,NULL, alphasort);
	int j=0;
	while(n--){
		cout<<" "<<namelist[n]->d_name<<"\n";
		j++;
		v.push_back(make_pair(namelist[i]->d_name,i));
		itemCounter++;
		// free(namelist[n]);
	}
	// free(namelist);
	return itemCounter;
}