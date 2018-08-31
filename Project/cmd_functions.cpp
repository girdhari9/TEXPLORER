#include "cmd_mode.h"
#include "normal_mode.h"

using namespace std;

int flag = 0;

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

void search_file(string current_path,string file_name, int up){
    struct dirent ** dir_namelist;
    int n = scandir(current_path.c_str(),&dir_namelist,NULL, alphasort);
    while(n--){
        if(dir_namelist[n]->d_type == 4){
            current_path = current_path + "/" + dir_namelist[n]->d_name;
            search_file(current_path,file_name,0);
            return;
        }
        else if(dir_namelist[n]->d_name == file_name)
            list_print(current_path,1,0);
    }
}

void search_dir(string current_path,string folder_name,string file_name){
    struct dirent ** dir_namelist;
    int n = scandir(current_path.c_str(),&dir_namelist,NULL, alphasort);
    while(n--){
        if(dir_namelist[n]->d_type == 4 && dir_namelist[n]->d_name != folder_name){
            current_path = current_path + "/" + dir_namelist[n]->d_name;
            snapshot(current_path,file_name,folder_name);
            return;
        }
        else if(dir_namelist[n]->d_type == 4){
            current_path = current_path + "/" + dir_namelist[n]->d_name;
            open((current_path + "/" + file_name).c_str(), O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
            snapshot(current_path,file_name,folder_name);
        }
    }
}

void snapshot(string current_path,string file_name,string folder_name){
    string file_store_path = current_path;
    string write_name = folder_name + ":";
    int dest_file, read_size;
    char buffer[1024];
    string::size_type sz; 
    int i_dec = std::stoi (write_name,&sz);
    dest_file = open((file_store_path + "/" + file_name).c_str(), O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
    while((read_size = read(i_dec,buffer,sizeof(buffer))) > 0)
        write(dest_file,buffer,read_size);
}