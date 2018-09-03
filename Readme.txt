WELCOME TO TEXPLORE!

A terminal based file explorer for linux based operating systems

Instructions:

1. Enter ./file_explorer to start the application

2. When ./file_explorer is given, the directory displayed is the current directory and its contents

3. Use arrow keys to navigate

4. '~/' refers to root directory with respect to the directory where the application started

For example: if application started in /home/user1/myfiles
"~/dir3/dir2" refers to "/home/user1/myfiles/dir3/dir2"

5. File/Directory names given without "~/" in the beginning are considered relative and will be assumed it is from current working directory

The application runs broadly in two modes
1. Normal Mode
2. Command Mode

Normal Mode:

1. User can navigate the directory entries using up/down arrow keys
2. Press enter on any directory to move into that directory or on any file to open the file in default application
3. Press left arrow key to move to previously visited directory
4. Press right arrow key to move to forward directory from which you came to this directory
5. Press back-space to go to previous directory of current directory
6. Press 'h' anytime to go the the home directory (ie the directory from which the application started)
6. Press ":" (colon) key to move to command mode
7. Press "q" to exit the normal mode (and the application)

Command Mode:

1. Type 'quit' + Press ENTER anytime to go out of command mode to normal mode	
2. User can perform any of the following commands in the given format

Command: copy

Syntax: copy <source_file(s)> <destination_directory>

Description: Copies multiple files into the destination directory. The operation is done recursively on directories

Examples:

copy file1.txt file2.txt dest_dir

copy ~/file1.txt ~/dir2/file2.txt  ~/dir5/dest_dir


Command: copy_dir

Syntax: copy_dir <source_file(s)> <destination_directory>

Description: Copies multiple directories into the destination directory. The operation is done recursively on directories

Examples:

copy_dir dir1 dir2 dest_dir

copy_dir ~/dir1 ~/dir2/dir3  ~/dir5/dest_dir


Command: move

Syntax: move <source_file(s)> <destination_directory>

Description: Copies multiple files into the destination directory. The operation is done recursively on directories

Examples:

move file1.txt file2.txt dest_dir

move ~/file1.txt ~/dir2/file2.txt ~/dir5/dest_dir

Command: move_dir

Syntax: move_dir <source_file(s)> <destination_directory>

Description: Copies multiple files into the destination directory. The operation is done recursively on directories

Examples:

move_dir dir1 dir2 dest_dir

move_dir ~/dir1 ~/dir2/dir3 ~/dir5/dest_dir


Command: rename

Syntax: rename <old_name> <new_name>

Examples:

rename dir2 new_dir_name

rename ~/dir1 new_dir_name

rename file1.txt new_file_name

rename ~/file1.txt new_file_name

Description: Renames a file or directory with the new name given in command


Command: create_file

Syntax: create_file <file_name> <destination_directory>

Description: Creates a new file in the directory mentioned in <destination_directory>. Please note that "." in destination directory means current directory

Example:

create_file file1.txt .

create_file file2.txt dir2

create_file file3.txt ~/dir3/dir4


Command: create_dir

Syntax: create_dir <directory_name> <destination_directory>

Description: Creates a new directory in the directory mentioned in <destination_directory>. Please note that "." in destination directory means current directory

Example:

create_file new_dir1 .

create_file new_dir2 dir2

create_file new_dir3 ~/dir3/dir4


Command: delete_file

Syntax: delete_file <file_name>

Description: Deletes the given file

Example:

delete_file file1.txt

delete_file ~/dir3/dir2/file2.txt

delete_file dir2/file3.txt



Command: delete_dir

Syntax: delete_dir <dir_name>

Description: Deletes the given directory

Example:

delete_dir dir1

delete_dir ~/dir3/dir2/dir12

delete_dir dir2/dir13



Command: goto

Syntax: goto <dir_name>

Description: Traverses to the given directory

Example:

goto dir3

goto ~/dir2/dir4

goto dir1/dir2



Command: search

Syntax: search <file/dir_name>

Description: Searches for the given files from the current directory recursively

Example:

search file1.txt


Command: snapshot

Syntax: snapshot <dir_name> <dump_file_name>

Description: Takes the current snapshot of the directory recursively and dumps the output to file mentioned in the file_name

Example:

snapshot dir dump1.txt

snapshot ~/dir2/dir3 /dumps/dump2.txt

