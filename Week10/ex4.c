#include "dirent.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <errno.h>

#define BUFFER_SIZE 512
#define MAX_NAME_SIZE 512

struct unique_file {
    ino_t inode_num;
    int hl_count;
    char * filenames[BUFFER_SIZE];
};

// auxiliary output script
void print_hardlinks(struct unique_file * file) {
    for(int i = 0; i < file->hl_count; i++) {
        printf("%s\t\t", file->filenames[i]);

        for(int j = 0; j < file->hl_count; j++) {
            printf("%s ", file->filenames[j]);
        }
        printf("\n");
    }
}

int main() {
    // Opening the tmp directory
    char * dirname = "./tmp";
    DIR * dirp = opendir (dirname);
    if ( dirp == NULL ) {
        printf("Error while opening tmp directory.");
        return 1;
    }

    // Reading the 1st entry of tmp directory
    struct dirent * de = readdir(dirp);

    int files_count = 0;
    struct unique_file ** unique_files = malloc( BUFFER_SIZE * sizeof(struct unique_file *));

    while (de != NULL) {
        // this is not a file
        if(strcmp(de->d_name, "..") == 0) {
            // read the next entry
            de = readdir(dirp);
            continue;
        }

        // get the absolute filename of the directory entry
        char * filename = malloc(sizeof(char) * MAX_NAME_SIZE);
        strcat(filename, dirname);
        strcat(filename, "/");
        strcat(filename, de->d_name);

        // bool variable to control entries of unique_files array
        bool file_is_new = 1;

        // create a stat pointer to store the info about the file
        struct stat * filebuf = malloc(sizeof (struct stat));

        if(stat(filename, filebuf) == -1) {
            printf("Error while getting info on FILE %s\n", filename);
            printf("ERRNO = %d\n", errno);
            break;
        }

        ino_t  inode_num = filebuf->st_ino;

        for(int i = 0; i < files_count; i++) {
            if(unique_files[i]->inode_num == inode_num) {
                file_is_new = 0;
                unique_files[i]->hl_count++;
                int hl_count = unique_files[i]->hl_count;
                unique_files[i]->filenames[hl_count-1] = de->d_name;
            }
        }

        if (file_is_new) {
            unique_files[files_count] = malloc(sizeof(struct unique_file));
            unique_files[files_count]->inode_num = inode_num;
            unique_files[files_count]->hl_count = 1;
            unique_files[files_count]->filenames[0] = de->d_name;
            files_count++;
        }

        // read the next entry
        de = readdir(dirp);
    }
    (void) closedir(dirp);

    // output
    printf("File\t\tHard Links\n");

    for(int i = 0; i < files_count; i++) {
        if(unique_files[i]->hl_count > 1) {
            print_hardlinks(unique_files[i]);
        }
    }

    return 0;
}