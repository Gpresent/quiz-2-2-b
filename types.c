#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("usage: path1 [path2 ...]\n");
        return 1;
    }

    for (size_t i = 1; i < argc; i++) {
        const char* path = argv[i];
        struct stat path_stat;
        
        if (lstat(path, &path_stat) != -1) {
            if (S_ISBLK(path_stat.st_mode)) printf("%s: block device\n", path);
            else if (S_ISCHR(path_stat.st_mode)) printf("%s: character special file\n", path);
            else if (S_ISDIR(path_stat.st_mode)) printf("%s: directory\n", path);
            else if (S_ISFIFO(path_stat.st_mode)) printf("%s: FIFO/pipe\n", path);
            else if (S_ISLNK(path_stat.st_mode)) printf("%s: symbolic link\n", path);
            else if (S_ISREG(path_stat.st_mode)) printf("%s: regular file\n", path);
            else if (S_ISSOCK(path_stat.st_mode)) printf("%s: socket\n", path);
            else printf("%s: unknown file type\n", path);
        } else {
            printf("%s: path error\n", path);
        }
    }
}