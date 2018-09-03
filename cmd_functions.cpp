#include "cmd_mode.h"
#include "normal_mode.h"

using namespace std;

int flag = 0;
vector<string> search_v;
vector<string> snap_v;

void copy_file(string file_name, string dir_name){
    int source_file, dest_file, read_size;
    char buffer[1024];
    source_file = open(file_name.c_str(), O_RDONLY);
    dest_file = open(dir_name.c_str(), O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
    while((read_size = read(source_file,buffer,sizeof(buffer))) > 0)
        write(dest_file,buffer,read_size);
    return; 
}

void move_file(string file_name, string dir_name){
    int source_file, dest_file, read_size;
    char buffer[1024];
    source_file = open(file_name.c_str(), O_RDONLY);
    dest_file = open(dir_name.c_str(), O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
    while((read_size = read(source_file,buffer,sizeof(buffer))) > 0)
        write(dest_file,buffer,read_size);
    remove(file_name.c_str());
    return; 
}

void copy_dir(string dir_name, string dir_path){
    flag++;
    if(flag > 100) return;
    struct dirent ** dir_namelist;
    int n = scandir(dir_name.c_str(),&dir_namelist,NULL, alphasort);
        while(n--){
            if(n < 2) break;
            if(dir_namelist[n]->d_type == 4){
                string new_dir_name = dir_name + "/" + dir_namelist[n]->d_name;
                string new_dir_path = dir_path + "/" + dir_namelist[n]->d_name;
                mkdir(new_dir_path.c_str(), S_IRUSR|S_IWUSR|S_IXUSR);
                copy_dir(new_dir_name,new_dir_path);
            }
            else{
                string source_file_name = dir_name + "/" + dir_namelist[n]->d_name;
                string dest_file_name = dir_path + "/" + dir_namelist[n]->d_name;
                copy_file(source_file_name,dest_file_name);
            }
        }
}

void rename_file(string file_old_name, string file_new_name){
    int source_file, dest_file, read_size;
    char buffer[1024];
    source_file = open(file_old_name.c_str(), O_RDONLY);
    dest_file = open(file_new_name.c_str(), O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
    while((read_size = read(source_file,buffer,sizeof(buffer))) > 0)
        write(dest_file,buffer,read_size);
    remove(file_old_name.c_str());
    return; 
}

void delete_dir(string dir_path){
    flag++;
    if(flag > 100) return;
    struct dirent ** dir_namelist;
    int n = scandir(dir_path.c_str(),&dir_namelist,NULL, alphasort);
    while(n--){
        if(n < 2) break;
        if(dir_namelist[n]->d_type == 4){
            string new_dir_path = dir_path + "/" + dir_namelist[n]->d_name;
            // rmdir(new_dir_path.c_str()); //If it will not work then open it
            delete_dir(new_dir_path);
            rmdir(new_dir_path.c_str());
        }
        else{
            string file_name = dir_path + "/" + dir_namelist[n]->d_name;
            remove(file_name.c_str());
        }
    }
}

void search_file(string current_path,string file_name){
    struct dirent ** dir_namelist;
    int n = scandir(current_path.c_str(),&dir_namelist,NULL, alphasort);
    while(n--){
        if(n < 2) break;
        if(dir_namelist[n]->d_type == 4){
            string new_current_path = current_path + "/" + dir_namelist[n]->d_name;
            search_file(new_current_path,file_name);
        }
        else if(dir_namelist[n]->d_name == file_name){
            search_v.push_back(current_path);
        }
    }
}

void snapshot(string current_path,FILE *file_pointer){
    struct dirent ** dir_namelist;
    int n = scandir(current_path.c_str(),&dir_namelist,NULL, alphasort);
    int x = n;
    fprintf(file_pointer,"%s\n\n",current_path.c_str());
    while(n--){
        if(n<2) break;
        fprintf(file_pointer,"%s\t",dir_namelist[n]->d_name);
    }
    fprintf(file_pointer,"\n\n\n");
    while(x--){
        if(x<2) break;
        else if(dir_namelist[x]->d_type == 4){
            string new_current_path = current_path + "/" + dir_namelist[x]->d_name;
            snapshot(new_current_path,file_pointer);
        }
    }
}

void print_search_file(vector<string> &v,string file_name){
    screen_point(0,0,1);
    for(unsigned int i = 0; i < 13 && i < v.size(); i++){
        string new_name = v[i];
        if(file_name.size() > 20)
            file_name = file_name.substr(1,19) + "...";
        cout<<"\033[21;35m "<<file_name<<"\033[0m";
        screen_point(i,30,0);
        cout<<v[i]<<"\n";
    }
    return;
}