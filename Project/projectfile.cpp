#include<bits/stdc++.h>
#include "screenPoint.h"

using namespace std;

int main(){
	screen_point(0,0,1);
	cout<<"\t\t\t\t\t\t\t\"Terminal file explorer\"\n";
	int cur_pos = list_print(0);
	screen_point(cur_pos+1,0,0);
	int x = pointer_move(cur_pos);
	cur_pos = list_print(x);
	x = pointer_move(cur_pos);
	getchar();
	return 0;
}