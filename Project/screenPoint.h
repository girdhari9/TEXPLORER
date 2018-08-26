#include<bits/stdc++.h>

using namespace std;

// extern stack<string> st;

void screen_point(int x, int y, int flag);
void list_print(string path,int cur_pos);
int pointer_move(stack<string> &forword_st,stack<string> &back_st,string path,int cur_pos);
int item_select(int x,int cur_pos, string path);
void print_file_permission(string path);

