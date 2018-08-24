#include<bits/stdc++.h>
#include "screenPoint.h"

using namespace std;
string path = "/home/gunno/Documents/os";
string pre_path = "/home/gunno/Documents/os";

int main(){
	screen_point(0,0,1);
	// cout<<"\t\t\t\t\t\t\t\"Terminal file explorer\"\n";
	int cur_pos = list_print(pre_path,path,0);
	// cout<<cur_pos<<" ";
	screen_point(cur_pos,0,0);
	pointer_move(pre_path,path,cur_pos);

	return 0;
}