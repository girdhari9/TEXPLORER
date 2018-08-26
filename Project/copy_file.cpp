#include "cmd_mode.h"
#include <termios.h>
using namespace std;

#define gotoxy(x,y) cout<<"\033["<<x<<";"<<y<<"H"

void copy_file(string file_name, string dir_name){
    ifstream fs;
    ofstream ft;
    char ch;
    fs.open(file_name.c_str());
    if(!fs){
        cout<<"Error in opening source file..!!";
        exit(1);
    }
    ft.open("dir_name/" + file_name);
    if(!ft){
        cout<<"Error in opening target file..!!";
        fs.close();
        exit(2);
    }
    while(fs.eof()==0){
        fs>>ch;
        ft<<ch;
    }
    cout<<"File copied successfully..!!";
    fs.close();
    ft.close();
}


