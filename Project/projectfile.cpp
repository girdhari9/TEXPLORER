#include<bits/stdc++.h>
#include "screenPoint.h"

using namespace std;
string path = "/home/gunno/Documents/os";

int main(){
	screen_point(0,0,1);
	// cout<<"\t\t\t\t\t\t\t\"Terminal file explorer\"\n";
	int cur_pos = list_print(path,0);
	screen_point(1,0,0);
	pointer_move(path,cur_pos);

	return 0;
}