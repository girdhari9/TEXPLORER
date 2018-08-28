#include "cmd_mode.h"

using namespace std;

void copy_file(string file_name, string dir_name){
    // ifstream fs;
    // ofstream ft;
    // char ch;
    // fs.fopen(file_name.c_str());
    // if(!fs){
    //     cout<<"Error in opening source file..!!";
    //     exit(1);
    // }
    // ft.open("dir_name/" + file_name);
    // if(!ft){
    //     cout<<"Error in opening target file..!!";
    //     fs.close();
    //     exit(2);
    // }
    // while(fs.eof()==0){
    //     fs>>ch;
    //     ft<<ch;
    // }
    // cout<<"File copied successfully..!!";
    // fs.close();
    // ft.close();
    char buffer[128];
    int nread;
    nread = read(0, buffer, 128);
    if (nread == -1)
        write(2, "A read error has occurred\n", 26);
    if ((write(1,buffer,nread)) != nread)
        write(2, "A write error has occurred\n",27);
    exit(0);
}


