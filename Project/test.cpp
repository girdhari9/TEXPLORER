#include<bits/stdc++.h>
#include "screenPoint.h"

using namespace std;

int coun = 0,a[15],,c = 0;
void pointer(){
	struct termios initialrsettings, newrsettings;
    tcgetattr(0, &initialrsettings);
    
    newrsettings = initialrsettings;
    newrsettings.c_lflag &= ~ECHO;
    newrsettings.c_lflag &= ~ICANON;
    // newrsettings.c_lflag &= ~ISIG;
    tcsetattr(0, TCSANOW, &newrsettings);

	int x = coun,y = 0;
	while(c != 101){
    		switch(c = getchar()){
    		    case 'A': if(x) screen_point(--x,y,0);
                else if(up != 0){ 
                	screen_point(0,0,1);
                	down--; up--;
                    for(int i=up;i<down;i++){
                        cout<<a[i]<<"\n";
                    }
                	screen_point(x,y,0);
                } break;
    		    case 'B': if(x < coun && x < 10) screen_point(++x,y,0); 
                          else if(down != 14){
                          		screen_point(0,0,1);
                          		// cout<<up<<"* ";
                          		down++; up++;
                          		for(int i=up;i<down;i++){
                          			cout<<a[i]<<"\n";
                          		}
                          		screen_point(x,y,0);
                          } break;
    	    }
    }
    tcsetattr(0, TCSANOW, &initialrsettings);
}

void cmd_main(){

	for(int i=1;i<=14;i++) a[i]=i;
	for(int i=0;i<6;i++) {
		cout<<a[i]<<"\n";
		coun++;
	}
	screen_point(coun,0,0);
    pointer();
}