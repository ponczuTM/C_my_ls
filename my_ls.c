#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <limits.h>
#include <grp.h>
#include <pwd.h>
#ifndef PATH 
#define PATH MAX 4096 
#endif /* ifndef PATH MAX */

void list_dir(char *name) {
    DIR * dir;
    struct dirent *dp;
    struct stat statbuf;
    struct group *grp;
    struct passwd *pwd;
    if ((dir = opendir(name)) == NULL) {
      perror("Blad");
    }
      printf("Contents of %s\n", name);
      if (chdir(name) == -1) {
        perror("Blad");
      };
      while ((dp = readdir(dir)) != NULL) {
        if(stat(dp->d_name, &statbuf) == -1) {
          continue;
        }
        printf("%o", (statbuf.st_mode & 07777));
        if ((pwd = getpwuid(statbuf.st_uid)) != NULL)
            printf(" %s", pwd->pw_name);
        else
            printf(" %d", statbuf.st_uid);
        if ((grp = getgrgid(statbuf.st_gid)) != NULL)
        printf(" %s", grp->gr_name);
        else
        printf(" %d", statbuf.st_gid);
        printf(" %s\n", dp->d_name);
        }
        closedir(dir);
}

int main(int argc, char **argv) {
    list_dir(".");
    exit(0);
}