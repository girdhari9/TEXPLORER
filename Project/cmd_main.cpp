#include "cmd_mode.h"
#include "normal_mode.h"

using namespace std;

vector<string> v;
extern vector<string> search_v;
extern string home_path;
extern stack<string>new_back_stk;
extern stack<string> old_back_stk;
extern int up,cmd_mod_screen_start,horizontal;

void tokenized(string s){
    v.erase(v.begin(),v.end());
    for(unsigned int i = 0;i < s.size(); i++){
        vector<char> sub_v;
        vector<char>::iterator it;
        while(s[i] != ' ' && i < s.size()){
            if(s[i] == 92){ 
                sub_v.push_back(32);
                i += 2;
            }
            else{
                sub_v.push_back(s[i]);
                i++;
            }
        }
        string t;
        for(unsigned int j = 0; j < sub_v.size();j++)
            t += sub_v[j];
        v.push_back(t);
    }
}

void cmd_main(string current_path){
    re_init_setting();
    screen_point(cmd_mod_screen_start+3,0,0);
    while(1){    
        // clear_scr(cmd_mod_screen_start+3);
        cout<<">";
        fflush(stdout);
        fflush(stdin);
        string s;
        getline(cin, s);
        tokenized(s);
        if(v[0] == "developer"){
            cout<<"Developer: Giridhari Lal Gupta\n";
        }
        else if(v[0] == "quit"){
            screen_point(0,0,0);
            pointer_move();
        }
        else if(v[0] == "clear"){
            clear_scr(cmd_mod_screen_start+3);
            screen_point(cmd_mod_screen_start+3,0,0);
            fflush(stdout);
        }
        else if(v[0] == "copy"){
            for(unsigned int i = 1; i < v.size()-1; i++){
                string dest_path, source_path; 
                char ch = v[v.size()-1][0], ch1 = v[i][0];
                if(ch == '~') dest_path = home_path + "/" + v[v.size()-1].substr(2) + "/" + v[i];
                else dest_path = current_path + "/" + v[v.size()-1] + "/" + v[i];

                if(ch1 == '~') source_path = home_path + "/" + v[i].substr(2);
                else source_path = current_path + "/" + v[i];
                copy_file(source_path,dest_path);
            }
            cout<<"File copied successfully!\n";
            // getchar();
        }
        else if(v[0] == "move"){
            for(unsigned int i = 1; i < v.size()-1; i++){
                string dest_path, source_path; 
                char ch = v[v.size()-1][0], ch1 = v[i][0];
                if(ch == '~') dest_path = home_path + "/" + v[v.size()-1].substr(2) + "/" + v[i];
                else dest_path = current_path + "/" + v[v.size()-1] + "/" + v[i];

                if(ch1 == '~') source_path = home_path + "/" + v[i].substr(2);
                else source_path = current_path + "/" + v[i];
                move_file(source_path,dest_path);
            }
            cout<<"File moved successfully!\n";
            // getchar();
        }
        else if(v[0] == "copy_dir"){
            for(unsigned int i = 1; i < v.size()-1; i++){   
                string dir_path = home_path + "/" + v[v.size()-1];
                dir_path = dir_path + "/" + v[i];
                mkdir(dir_path.c_str(), S_IRUSR|S_IWUSR|S_IXUSR);
                copy_dir(home_path + "/" + v[i],dir_path);
            }
            cout<<"Dirctory copied successfully!\n";
            // ch = getchar();
        }
        else if(v[0] == "move_dir"){
            for(unsigned int i = 1; i < v.size()-1; i++){   
                string dir_path = home_path + "/" + v[v.size()-1];
                dir_path = dir_path + "/" + v[i];
                mkdir(dir_path.c_str(), S_IRUSR|S_IWUSR|S_IXUSR);
                copy_dir(home_path + "/" + v[i],dir_path);
                delete_dir(home_path + "/" + v[i]);
                rmdir((home_path + "/" + v[i]).c_str());
            }
            cout<<"Directory moved successfully!\n";
            // getchar();
        }
        else if(v[0] == "rename"){
            move_file(home_path + "/" + v[1],home_path + "/" + v[2]);
            cout<<"File rename successfully!";
            // getchar();
        }
        else if(v[0] == "delete_file"){
            string file_path = home_path + "/" + v[1];
            remove(file_path.c_str());
            cout<<"File deleted successfully!\n";
            // getchar();
        } 
        else if(v[0] == "delete_dir"){
            delete_dir(home_path + "/" + v[1]);
            rmdir((home_path + "/" + v[1]).c_str());
            cout<<"Dirctory deleted successfully!\n";
            // getchar();
        }        
        else if(v[0] == "create_file"){
            string file_name = home_path + "/" + v[2] + "/" + v[1];
            open(file_name.c_str(), O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
            cout<<"file created successfully!\n";
            // getchar();
        }
        else if(v[0] == "create_dir"){
            string file_name = home_path + "/" + v[2] + "/" + v[1];
            mkdir(file_name.c_str(), S_IRUSR|S_IWUSR|S_IXUSR);
            cout<<"Directory created successfully!\n";
            // getchar();
        }  
        else if(v[0] == "goto"){
            string path_name = home_path + "/" + v[1];
            up = 0;
            screen_point(0,0,0);
            list_print(path_name,1,0);
            pointer_move();
        } 
        else if(v[0] == "search"){
            search_v.push_back(current_path);
            search_file(current_path,v[1],0);
            cout<<"$";
        } 
        else if(v[0] == "snapshot"){
            search_dir(current_path,v[1],v[2]);
        }
        else{ 
            cout<<"command not found!\n";
            // getchar();  
        }
    }
}