#include "cmd_mode.h"
#include "normal_mode.h"

using namespace std;

vector<string> v;
extern vector<string> search_v;
extern string home_path;
extern stack<string>new_back_stk;
extern stack<string> old_back_stk;
extern int up,cmd_mod_screen_start,horizontal,mode;

string cmd_name[16], cmd_work[16];
string dest_path, source_path;

void cmd_main(string current_path){
    mode = 0;
    re_init_setting();
    screen_point(cmd_mod_screen_start+3,0,0);
    cmd_arr_decl();
    while(1){    
        // clear_scr(cmd_mod_screen_start+3);
        cout<<">";
        fflush(stdout);
        fflush(stdin);
        string s;
        getline(cin, s);
        tokenized(s);
        if(v[0] == "help"){
            clear_scr(cmd_mod_screen_start+3);
            screen_point(cmd_mod_screen_start+3,0,0);
            fflush(stdout);
            cout<<"You can perform operation using following commands:\n";
            cout<<"\nAll commands are case sensitive.\n";
            for(int i=0;i<=15;i++){
                cout<<cmd_name[i]<<cmd_work[i]<<"\n";
            }
            cout<<"Press ENTER to go back\n";
            getchar();
            screen_point(0,0,1);
            list_print(current_path,1,0);
            screen_point(cmd_mod_screen_start+3,0,0);
        }
        else if(v[0] == "about"){
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
            int path = 0;
            for(unsigned int i = 1; i < v.size()-1; i++){
                path = set_path(current_path,i);
                if(path)
                    copy_file(source_path,dest_path);
            }
            if(path){ 
                list_print(current_path,1,0);
                screen_point(cmd_mod_screen_start+3,0,0);
                cout<<"File copied successfully!\n";
            }
            else
                cout<<v[0]<<": command syntax is not correct 'help' - to find correct syntax.\n";
        }
        else if(v[0] == "move"){
            int path = 0;
            for(unsigned int i = 1; i < v.size()-1; i++){
                path = set_path(current_path,i);
                if(path)
                    move_file(source_path,dest_path);
            }
            if(path){
                list_print(current_path,1,0);
                screen_point(cmd_mod_screen_start+3,0,0);
                cout<<"File moved successfully!\n";
            }
            else
                cout<<v[0]<<": command syntax is not correct 'help' - to find correct syntax.\n";
        }
        else if(v[0] == "copy_dir"){
            int path = 0;
            for(unsigned int i = 1; i < v.size()-1; i++){   
                path = set_path(current_path,i);
                if(path){
                    mkdir(dest_path.c_str(), S_IRUSR|S_IWUSR|S_IXUSR);
                    copy_dir(source_path,dest_path);
                }
            }
            if(path){
                list_print(current_path,1,0);
                screen_point(cmd_mod_screen_start+3,0,0);
                cout<<"Dirctory copied successfully!\n";
            }
            else
                cout<<v[0]<<": command syntax is not correct 'help' - to find correct syntax.\n";
        }
        else if(v[0] == "move_dir"){
            int path = 0;
            for(unsigned int i = 1; i < v.size()-1; i++){   
                //To set destination & source path
                path = set_path(current_path,i); 
                //To create directory
                if(path){
                    mkdir(dest_path.c_str(), S_IRUSR|S_IWUSR|S_IXUSR);
                    copy_dir(source_path,dest_path);
                    delete_dir(source_path);
                    rmdir(source_path.c_str());
                }
            }
            if(path){
                list_print(current_path,1,0);
                screen_point(cmd_mod_screen_start+3,0,0);
                cout<<"Directory moved successfully!\n";
            }
            else
                cout<<v[0]<<": command syntax is not correct 'help' - to find correct syntax.\n";
        }
        else if(v[0] == "rename"){
            string dest_path, source_path; 
                if(v[1][0] == '~') {
                    size_t found = v[1].find_last_of("/\\");
                    dest_path = home_path + "/" + v[1].substr(2,found-1) + v[2];
                    source_path = home_path + "/" + v[1].substr(2);
                }
                else {
                    size_t found = v[1].find_last_of("/\\");
                    if(found != string::npos)
                    dest_path = current_path + "/" + v[1].substr(0,found) + "/" + v[2];
                    else dest_path = current_path + "/" + v[2];
                    source_path = current_path + "/" + v[1];
                }
            move_file(source_path,dest_path);
            list_print(current_path,1,0);
            screen_point(cmd_mod_screen_start+3,0,0);
            cout<<"File rename successfully!\n";
        }
        else if(v[0] == "delete_file"){
            string file_path; 
            if(v[1][0] == '~') file_path = home_path + "/" + v[1].substr(2);
            else file_path = current_path + "/" + v[1];
            remove(file_path.c_str());
            list_print(current_path,1,0);
            screen_point(cmd_mod_screen_start+3,0,0);
            cout<<"File deleted successfully!\n";
        } 
        else if(v[0] == "delete_dir"){
            string directory_path; 
            if(v[1][0] == '~') directory_path = home_path + "/" + v[1].substr(2);
            else directory_path = current_path + "/" + v[1];
            delete_dir(directory_path);
            rmdir(directory_path.c_str());
            list_print(current_path,1,0);
            screen_point(cmd_mod_screen_start+3,0,0);
            cout<<"Dirctory deleted successfully!\n";
        }        
        else if(v[0] == "create_file"){
            string file_name;
            if(v[1][0] == '~'){
                cout<<v[0]<<": command syntax is not correct 'help' - to find correct syntax.\n";
            }
            else if(v[2][0] == '~') file_name = home_path + "/" + v[2].substr(2) + "/" + v[1];
            else file_name = current_path + "/" + v[2] + "/" + v[1];
            open(file_name.c_str(), O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
            list_print(current_path,1,0);
            screen_point(cmd_mod_screen_start+3,0,0);
            cout<<"file created successfully!\n";
        }
        /*Give first agrument as directory name which wants to create
        second arguments as where wants to create. Give '.' is wants to create 
        directory in current directory.*/
        else if(v[0] == "create_dir"){
            string file_name;
            if(v[1][0] == '~'){
                cout<<v[0]<<": command syntax is not correct 'help' - to find correct syntax.\n";
            }
            if(v[2][0] == '~'){
                file_name = home_path + "/" + v[2].substr(2) + "/" + v[1];
                mkdir(file_name.c_str(), S_IRUSR|S_IWUSR|S_IXUSR);
                cout<<"Directory created successfully!\n";
            }
            else{
                file_name = current_path + "/" + v[2] + "/" + v[1];
                mkdir(file_name.c_str(), S_IRUSR|S_IWUSR|S_IXUSR);
                cout<<"Directory created successfully!\n"; 
            }
        }  
        else if(v[0] == "goto"){
            string path_name;
            if(v[1][0] == '~')
                path_name = home_path + "/" + v[1].substr(2);
            else path_name = home_path + "/" + v[1];
            up = 0;
            screen_point(0,0,0);
            list_print(path_name,1,0);
            pointer_move();
        } 
        else if(v[0] == "search"){
            search_v.push_back(current_path);
            search_file(current_path,v[1],0);
            pointer_move();
        } 
        else if(v[0] == "snapshot"){
            search_dir(current_path,v[1],v[2]);
        }
        else{   
            cout<<v[0]<<": command not found 'help' - to find correct command name.\n";
        }
    }
}

void cmd_arr_decl(){
    cmd_name[0] = "copy"; 
    cmd_name[1] = "move";
    cmd_name[2] = "copy_dir";
    cmd_name[3] = "move_dir";
    cmd_name[4] = "delete_file";
    cmd_name[5] = "delete_dir";
    cmd_name[6] = "create_file";
    cmd_name[7] = "create_dir";
    cmd_name[8] = "goto";
    cmd_name[9] = "search";
    cmd_name[10] = "rename";
    cmd_name[11] = "snapshot";
    cmd_name[12] = "help";
    cmd_name[13] = "clear";
    cmd_name[14] = "quit";
    cmd_name[15] = "about"; 
    
    cmd_work[0] = ": To 'COPY' files only.\n syntax: 'copy' <SOURCE PATH 1> ... <SOURCE PATH n> <DEST PATH>"; 
    cmd_work[1] = ": To 'MOVE' files only.\n syntax: 'move' <SOURCE PATH 1> ... <SOURCE PATH n> <DEST PATH>";
    cmd_work[2] = ": To 'COPY DIRECTORIES'.\n syntax: 'copy_dir' <SOURCE PATH 1> ... <SOURCE PATH n> <DEST PATH>";
    cmd_work[3] = ": To 'MOVE DIRECTORIES'.\n syntax: 'move_dir' <SOURCE PATH 1> ... <SOURCE PATH n> <DEST PATH>";
    cmd_work[4] = ": To 'DELETE FILES'.\n syntax: 'move_dir' <SOURCE PATH 1> ... <SOURCE PATH n> <DEST PATH>";
    cmd_work[5] = ": To 'DELETE DIRECTORIES'.\n syntax: 'move_dir' <SOURCE PATH 1> ... <SOURCE PATH n> <DEST PATH>";
    cmd_work[6] = ": To 'CREATE FILE'.\n syntax: 'create_file' <SOURCE PATH> <DEST PATH>";
    cmd_work[7] = ": To 'CREATE DIRECTORY'.\n syntax: 'create_dir' <SOURCE PATH> <DEST PATH>";
    cmd_work[8] = ": To 'REACH DIRECTORY'.\n syntax: 'goto' <DIRECTORY NAME>/<DIRECTORY PATH>";
    cmd_work[9] = ": To 'SEARCH FILE'.\n syntax: 'search' <FILE NAME>";
    cmd_work[10] = ": To 'RENAME'.\n syntax: 'rename' <SOURCE FILE NAME/PATH> <NEW FILE NAME>";
    cmd_work[11] = ": Take 'SNAPSHOT' of a directory.\n syntax: 'snapshot' <DIRECTORY NAME/PATH>";
    cmd_work[12] = ": To 'HELP' regarding commands/syntax - 'help'";
    cmd_work[13] = ": To 'CLEAR' command mode screen - 'clear'";
    cmd_work[14] = ": To 'QUIT' command mode and swtich to normal mode - 'quit'";
    cmd_work[15] = ": To know about this 'TERMINAL FILE EXPLORER' - 'about'";
}

int set_path(string current_path,int i){
    if(v.size() < 3){
        cout<<v[0]<<": command syntax is not correct 'help' - to find correct syntax.\n";
        return 0;
    }
    if(v[v.size()-1][0] == '~') {
        if(v[i][0] == '~'){
            size_t found = v[i].find_last_of("/\\");
            dest_path = home_path + "/" + v[v.size()-1].substr(2) + "/" + v[i].substr(found+1);
        }
        else{
            size_t found = v[i].find_last_of("/\\");
            if(found != string::npos)
                dest_path = home_path + "/" + v[v.size()-1] + "/" + v[i].substr(found+1);
            else dest_path = home_path + "/" + v[v.size()-1] + "/" + v[i];
        }
    }
    else {
        if(v[i][0] == '~'){
            size_t found = v[i].find_last_of("/\\");
            dest_path = current_path + "/" + v[v.size()-1] + "/" + v[i].substr(found+1);
        }
        size_t found = v[i].find_last_of("/\\");
        if(found != string::npos)
            dest_path = home_path + "/" + v[v.size()-1] + "/" + v[i].substr(found+1);
        else dest_path = home_path + "/" + v[v.size()-1] + "/" + v[i];
    }

    if(v[i][0] == '~') source_path = home_path + "/" + v[i].substr(2);
    else source_path = current_path + "/" + v[i];
    return 1;
}

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