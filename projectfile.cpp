/* Name: Giridhari Lal Gupta 2018201019 OS1 */
#include<bits/stdc++.h>
#include "normal_mode.h"
#include "cmd_mode.h"

using namespace std;

char root_path[1000];

string home_path;
	
int main(){
	getcwd(root_path,1000);
	home_path = (string)root_path;
	screen_point(0,0,1);
	list_print(home_path,1,0);
	pointer_move();
	return 0;	
}