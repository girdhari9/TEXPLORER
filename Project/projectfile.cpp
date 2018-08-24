#include<bits/stdc++.h>
#include "screenPoint.h"

using namespace std;
string path = "/home/gunno/Documents/os";
string pre_path = "/home/gunno/Documents/os";

int main(){
	screen_point(0,0,1);
	// cout<<"\t\t\t\t\t\t\t\"Terminal file explorer\"\n";
	list_print(pre_path,path,1);
	return 0;
}