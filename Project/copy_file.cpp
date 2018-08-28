#include "cmd_mode.h"

using namespace std;

void copy_file(string file_name, string dir_name){
char block[1024];
    int in, out;
    int nread;
    in = open(file_name.c_str(), O_RDONLY);
    out = open(dir_name.c_str(), O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
    while((nread = read(in,block,sizeof(block))) > 0)
        write(out,block,nread);
    return; 
}


